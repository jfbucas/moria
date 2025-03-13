#!/usr/bin/python3

#import os
#os.environ['UNICORN_LOG_LEVEL'] = "0xFFFFFFFF" # verbose - print anything 
#os.environ['UNICORN_LOG_DETAIL_LEVEL'] = "1" # full filename with line info

from unicorn import *
from unicorn.x86_const import *
from capstone import Cs, CS_ARCH_X86, CS_MODE_16
import struct
import random
import threading
import signal
from datetime import *
import time
import sys
import tty
import termios
import os

# Includes
exec(open('cp437.py').read())
exec(open('screen.py').read())
exec(open('interrupts.py').read())
exec(open('exe_loader.py').read())

# Initialize Unicorn & Capstone
emu = Uc(UC_ARCH_X86, UC_MODE_16)
md = Cs(CS_ARCH_X86, CS_MODE_16)

# Memory Mapping
BASE_ADDR = 0x0000
MEM_SIZE = 0xB8000 # 1024 * 1024 * 4 #0x100000
emu.mem_map(BASE_ADDR, MEM_SIZE)

# Map video memory in Unicorn
emu.mem_map(VIDEO_MEMORY_ADDR, VIDEO_MEMORY_SIZE)

# Write empty screen to Unicorn (spaces with white-on-black)
emu.mem_write(VIDEO_MEMORY_ADDR, bytes(TEXT_MODE_MEMORY))

# Load EXE
starting_point = exe_load(emu, "MORIA.EXE")

# Loop detection
executed_ips = {}

# Handle Terminal resize
def handle_resize(signum, frame):
	cols, rows = os.get_terminal_size()
	print("\033[2J"+"\033[0;0H")
	if DEBUG_TERM: print(f"Terminal resized to {cols}x{rows}")
	monitor.pos_x = cols-84
	if monitor.pos_x < 0:
		monitor.pos_x = 0



# Small Tick Thread
class Ticker(threading.Thread):
	def __init__(self, uc):
		threading.Thread.__init__(self)
		self.uc = uc
		self.finish = False
	def run(self):
		while not self.finish:
			# Tick count from 0x046C
			tick = int.from_bytes(self.uc.mem_read(0x046C, 2), "little")  
			tick = (tick+1)%32768  
			self.uc.mem_write(0x046C, tick.to_bytes(2, "little")) 

			time.sleep(1/18)
	def done(self):
		self.finish = True

# Read a key
def get_key():
	fd = sys.stdin.fileno()
	old_settings = termios.tcgetattr(fd)
	try:
		tty.setraw(fd)
		key = sys.stdin.read(1)  # Read a single character
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

	# Special Keys
	if key == "Q":
		done()
	elif key == "H":
		print("Installing Hook")
		emu.emu_stop()
		emu.hook_add(UC_HOOK_CODE, hook_code)
		emu.emu_start()
		
	return ord(key)

# Finish
def done():
	ticker.done()
	monitor.done()
	emu.emu_stop()

# Dissassemble a bunch of memory
def print_next_instructions(emu, cs, ip, count=10):
    """Disassemble and print the next few instructions"""
    addr = (cs * 16) + ip  # Convert segment:offset to linear address
    code = emu.mem_read(addr, count*10)
    for insn in md.disasm(code, addr):
        print(f"CS:IP={hex(cs)}:{hex(insn.address % 0x10000)} | {insn.mnemonic}  {insn.op_str}")
        count -= 1
        if count == 0:
            break

#print_next_instructions(emu, 0x214C, 0x0000, count=10)

# Hook Execution
def hook_code(uc, address, size, user_data):
	cs = uc.reg_read(UC_X86_REG_CS)
	es = uc.reg_read(UC_X86_REG_ES)
	ds = uc.reg_read(UC_X86_REG_DS)
	ip = uc.reg_read(UC_X86_REG_IP)

	code = uc.mem_read(address, size)
	if es == 0xb800 or ds == 0xb800:
		di = uc.reg_read(UC_X86_REG_DI)
		al = uc.reg_read(UC_X86_REG_AL)
		ah = uc.reg_read(UC_X86_REG_AH)
		for insn in md.disasm(code, address):
			#print(f"CS:IP={hex(cs)}:{hex(insn.address % 0x10000)} | {insn.mnemonic} {insn.op_str}")
			"""if insn.mnemonic == "stosw":
				print(f"CS:IP={hex(cs)}:{hex(ip)} | {insn.mnemonic} {insn.op_str} {chr(ah)} {chr(al)} {hex(di)}")
				#contents = uc.mem_read( 0, 1024*1024*4 )
				for x in range(80):
					contents = int.from_bytes(uc.mem_read(0xB8000+x*2+0, 1), "little") 
					print(chr(contents),end="")
				print()"""

	for insn in md.disasm(code, address):
		if insn.mnemonic+" "+insn.op_str == "in al, dx":
			#print(code)
			dx = uc.reg_read(UC_X86_REG_DX)
			ax = uc.reg_read(UC_X86_REG_AX)
			print(f"CS:IP={hex(cs)}:{hex(insn.address % 0x10000)} | {insn.mnemonic} {insn.op_str} - {hex(ax)} {hex(dx)}")
			#print(hex(insn.address), )
			#uc.reg_write(UC_X86_REG_AL, 1)
			#previous_insn = "in al, dx"
		elif insn.mnemonic+" "+insn.op_str == "test al, 1":
			ax = uc.reg_read(UC_X86_REG_AX)
			print(f"CS:IP={hex(cs)}:{hex(insn.address % 0x10000)} | {insn.mnemonic} {insn.op_str} - {hex(ax)}")
			#print(code)
			#ax = uc.reg_read(UC_X86_REG_AX)
			#uc.reg_write(UC_X86_REG_AX, 0xb801)
			#print(insn)

	# No infinity
	#executed_ips[ip] = executed_ips.get(ip, 0) + 1
	#if executed_ips[ip] > 10000:
	#	print(f"Infinite loop detected at {hex(ip)}")
	#	uc.emu_stop()



def hook_mem_video_read(uc, access, address, size, value, user_data):
	"""Intercept reads from video memory and return the correct value."""
	global TEXT_MODE_MEMORY
	if VIDEO_MEMORY_ADDR <= address < VIDEO_MEMORY_ADDR + VIDEO_MEMORY_SIZE:
		offset = address - VIDEO_MEMORY_ADDR  # Convert to index
		value = TEXT_MODE_MEMORY[offset*2]
		print(f"[VIDEO] Read {hex(value)} from 0x{address:X} (offset {offset})")
		uc.reg_write(UC_X86_REG_AL, value)  # Store result in AL

#emu.hook_add(UC_HOOK_CODE, hook_code)
emu.hook_add(UC_HOOK_INTR, hook_interrupt)
#https://github.com/unicorn-engine/unicorn/issues/1933
emu.hook_add(UC_HOOK_MEM_WRITE, hook_mem_video_write)
#emu.hook_add(UC_HOOK_MEM_READ,  hook_mem_video_read)

# --- Patches ---
nop=0x90
# The "in" opcode actually gets ignored by unicorn-engine
#emu.mem_write(0x21494, nop.to_bytes(1, "little")) # in al, dx
#emu.mem_write(0x21495, nop.to_bytes(1, "little")) # test al, 1
#emu.mem_write(0x21496, nop.to_bytes(1, "little")) # test al, 1
emu.mem_write(0x21497, nop.to_bytes(1, "little")) # jne 
#emu.mem_write(0x2149b, nop.to_bytes(1, "little")) # test al, 1
#emu.mem_write(0x2149c, nop.to_bytes(1, "little")) # test al, 1
emu.mem_write(0x2149d, nop.to_bytes(1, "little")) # jne

# Clock is Ticking
ticker = Ticker(emu)
ticker.start()

# Monitor is Monitoring
monitor = Monitor(emu)
monitor.start()

# Register the signal handler
signal.signal(signal.SIGWINCH, handle_resize)
handle_resize(None, None)
monitor.refresh()

# Start Execution
try:
    emu.emu_start(starting_point, 0)
except Exception as e:
    print(f"Emulation stopped: {e}")
