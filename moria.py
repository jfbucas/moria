#!/usr/bin/python3

#import os
#os.environ['UNICORN_LOG_LEVEL'] = "0xFFFFFFFF" # verbose - print anything 
#os.environ['UNICORN_LOG_DETAIL_LEVEL'] = "1" # full filename with line info

from unicorn import * #Uc, UC_ARCH_X86, UC_MODE_16, UC_HOOK_CODE, UC_HOOK_INTR, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_HOOK_INSN
from unicorn.x86_const import *
from capstone import Cs, CS_ARCH_X86, CS_MODE_16
import struct
import random
#import curses
import time
from datetime import datetime
import threading

import sys
import tty
import termios


from exe_loader import exe_load
from cp437 import CP437
#import screen


DEBUG_BIOS=False
DEBUG_DOS=False
DEBUG_VIDEO=False

# Initialize Unicorn & Capstone
emu = Uc(UC_ARCH_X86, UC_MODE_16)
md = Cs(CS_ARCH_X86, CS_MODE_16)

# Screen
#SCREEN = screen.Screen()

# Memory Mapping
BASE_ADDR = 0x0000
MEM_SIZE = 0xB8000 # 1024 * 1024 * 4 #0x100000

emu.mem_map(BASE_ADDR, MEM_SIZE)

VIDEO_MEMORY_ADDR = 0xB8000
VIDEO_MEMORY_SIZE = 1024*8 # 80x25 characters, 2 bytes each

# Initialize a Python bytearray for text mode
TEXT_MODE_MEMORY = TEXT_MODE_MEMORY = bytearray(VIDEO_MEMORY_SIZE)
TEXT_MODE_SEQ = 0
TEXT_MODE_CURSOR_OFFSET = 0

for row in range(25):
	for col in range(80):
		idx = (row * 80 + col)*2  # Memory index
		TEXT_MODE_MEMORY[idx] = 0x20  # Space char
		TEXT_MODE_MEMORY[idx+1] = 7


# Map video memory in Unicorn
emu.mem_map(VIDEO_MEMORY_ADDR, VIDEO_MEMORY_SIZE)

# Write empty screen to Unicorn (spaces with white-on-black)
emu.mem_write(VIDEO_MEMORY_ADDR, bytes(TEXT_MODE_MEMORY))



# Load EXE
starting_point = exe_load(emu, "MORIA.EXE")

# Loop detection
executed_ips = {}

# FileHandle
files_handles = {}

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

# Monitor refresh
class Monitor(threading.Thread):
	def __init__(self, uc): #, screen):
		threading.Thread.__init__(self)
		self.uc = uc
		self.finish = False
		self.do_refresh = True
		self.pos_x = 80

	def refresh(self):
		self.do_refresh = True

	def run(self):
		global TEXT_MODE_MEMORY
		while not self.finish:
			if self.do_refresh:
				#self.do_refresh = False
				o="\033[s"
				o+=f"\033[2;{self.pos_x}H"+"x"+"-"*80+"x"
				for y in range(25):
					o+=f"\033[{y+3};{self.pos_x}H"
					o+="|"
					for x in range(80):
						c = TEXT_MODE_MEMORY[(x+y*80)*2]
						o+=CP437[c]
						#o+=chr(c)
					#print(f"\033[{0y};{0}H{o}",end="")
					o+="|"
				o+=f"\033[{25+3};{self.pos_x}H"+"x"+"-"*80+"x"
				o+="\033[u"
				print(o, end="")
			time.sleep(1/24)
			#time.sleep(0.5)
	def done(self):
		self.finish = True

# Read a key
def get_key():

    #for c in range(256):
    #	print(chr(c), CP437[c])

    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        key = sys.stdin.read(1)  # Read a single character
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ord(key)

# Finish
def done():
	ticker.done()
	monitor.done()
	emu.emu_stop()


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
#exit()

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

# Hook Interrupts
def hook_interrupt(uc, intno, user_data):
	global TEXT_MODE_MEMORY, TEXT_MODE_CURSOR_OFFSET
	ax = uc.reg_read(UC_X86_REG_AX)
	ah = uc.reg_read(UC_X86_REG_AH)
	al = uc.reg_read(UC_X86_REG_AL)
	if intno == 0x21:
			
		if ah == 0x25:
			# https://www.gladir.com/LEXIQUE/INTR/int21f25.htm
			ds = uc.reg_read(UC_X86_REG_DS)
			dx = uc.reg_read(UC_X86_REG_DX)
			if DEBUG_DOS: print(f"DOS Interrupt 21h Function 25h - Set interrupt vector for INT {hex(al)} -> {hex(ds)}:{hex(dx)}")
		elif ah == 0x2c:
			# https://www.gladir.com/LEXIQUE/INTR/int21f2c00.htm
			if DEBUG_DOS: print("DOS Interrupt 21h Function 2ch - Get system time", hex(al))
			t = datetime.now()
			uc.reg_write(UC_X86_REG_CH, t.hour)
			uc.reg_write(UC_X86_REG_CL, t.minute)
			uc.reg_write(UC_X86_REG_DH, t.second)
			uc.reg_write(UC_X86_REG_DL, t.microsecond//10000)
			
		elif ah == 0x35:
			# https://www.gladir.com/LEXIQUE/INTR/int21f35.htm
			if DEBUG_DOS: print("DOS Interrupt 21h Function 35h - Get interrupt vector")
		elif ah == 0x3d:
			# https://www.gladir.com/LEXIQUE/INTR/int21f3d.htm
			ds = uc.reg_read(UC_X86_REG_DS)
			dx = uc.reg_read(UC_X86_REG_DX)
			filename = uc.mem_read(ds*16+dx, 20)
			filename = filename[:filename.find(0)].decode("ascii")
			handle = len(files_handles)
			if filename not in files_handles:
				files_handles[handle] = { "filename": filename, "position":0 }
				with open(filename, "rb") as f:
					files_handles[handle]["data"] = f.read()
			uc.reg_write(UC_X86_REG_AX, handle)
			#flags = uc.reg_read(UC_X86_REG_FLAGS)  # Read current EFLAGS
			#flags |= (1 << 0)  # Set bit 0 (CF)
			#uc.reg_write(UC_X86_REG_FLAGS, flags)  # Write back modified flags
			flags = uc.reg_read(UC_X86_REG_FLAGS)  # Read current EFLAGS
			flags &= ~(1 << 0)  # Clear bit 0 (CF)
			uc.reg_write(UC_X86_REG_FLAGS, flags)  # Write back modified flags			
			if DEBUG_DOS: print("DOS Interrupt 21h Function 3dh - Open file", filename)

		elif ah == 0x3f:
			# https://www.gladir.com/LEXIQUE/INTR/int21f3d.htm
			handle = uc.reg_read(UC_X86_REG_BX)
			count = uc.reg_read(UC_X86_REG_CX)
			ds = uc.reg_read(UC_X86_REG_DS)
			dx = uc.reg_read(UC_X86_REG_DX)
			if handle not in files_handles:
				print("Handle not found", handle)

			p = files_handles[handle]["position"]
			uc.mem_write(ds*16+dx, files_handles[handle]["data"][p:p+count] )
			files_handles[handle]["position"] += count

			uc.reg_write(UC_X86_REG_AX, count)
			flags = uc.reg_read(UC_X86_REG_FLAGS)  # Read current FLAGS
			flags &= ~(1 << 0)                     # Clear bit 0 (CF)
			uc.reg_write(UC_X86_REG_FLAGS, flags)  # Write back modified flags			
			if DEBUG_DOS: print("DOS Interrupt 21h Function 3Fh - Read file", files_handles[handle]["filename"], count)
		elif ah == 0x44:
			# https://www.gladir.com/LEXIQUE/INTR/int21f4400.htm
			handle = uc.reg_read(UC_X86_REG_BX)
			flags = uc.reg_read(UC_X86_REG_FLAGS)  # Read current FLAGS
			flags &= ~(1 << 0)                     # Clear bit 0 (CF)
			uc.reg_write(UC_X86_REG_FLAGS, flags)  # Write back modified flags			
			dx = (1 << 15)
			uc.reg_write(UC_X86_REG_DX, dx)
			if DEBUG_DOS: print(f"DOS Interrupt 21h Function 44h - IOCTL subfunction {hex(al)} {hex(handle)}")

		elif ah == 0x4c:
			# https://www.gladir.com/LEXIQUE/INTR/int21f4c.htm
			if DEBUG_DOS: print("DOS Interrupt 21h Function 4Ch - End Program", hex(al))
			done()
		else:
			print("DOS Interrupt 21h Unknown Function", f"{hex(ah)}:{hex(al)}")
			done()

	elif intno == 0x10:
		if ah == 0x02:  # Set Cursor Position
			dh = uc.reg_read(UC_X86_REG_DH)  # Row
			dl = uc.reg_read(UC_X86_REG_DL)  # Column
			bh = uc.reg_read(UC_X86_REG_BH)  # Page
			TEXT_MODE_CURSOR_OFFSET = dl+dh*80
			if DEBUG_BIOS: print(f"BIOS Interrupt 10h (Video) - Set cursor position to ({dl},{dh}) for page {bh} {TEXT_MODE_CURSOR_OFFSET}")
		elif ah == 0x03:  # Get Cursor Position
			bh = uc.reg_read(UC_X86_REG_BH)  # Page
			x = TEXT_MODE_CURSOR_OFFSET % 80
			y = TEXT_MODE_CURSOR_OFFSET // 80
			uc.reg_write(UC_X86_REG_CL, 0)
			uc.reg_write(UC_X86_REG_CH, 0)
			uc.reg_write(UC_X86_REG_DL, x)
			uc.reg_write(UC_X86_REG_DH, y)
			if DEBUG_BIOS: print(f"BIOS Interrupt 10h (Video) - Get cursor position page {bh} {TEXT_MODE_CURSOR_OFFSET}")

		elif ah == 0x09:  # Write Char to Screen
			bl = uc.reg_read(UC_X86_REG_BL)
			TEXT_MODE_MEMORY[TEXT_MODE_CURSOR_OFFSET*2+0] = al & 0xFF  # Store only 1 byte
			TEXT_MODE_MEMORY[TEXT_MODE_CURSOR_OFFSET*2+1] = bl & 0xFF  # Store only 1 byte
			TEXT_MODE_CURSOR_OFFSET+=1
			if DEBUG_BIOS: print(f"BIOS Interrupt 10h (Video) - Write char {chr(al)} {TEXT_MODE_CURSOR_OFFSET}")
		elif ah == 0x0E:  # Teletype Output
			al = uc.reg_read(UC_X86_REG_AL)
			print(f"BIOS Interrupt 10h (Video) - Print TTY char {chr(al)} {TEXT_MODE_CURSOR_OFFSET}")

		elif ah == 0x6:
			#if al == 0:
			#	print("BIOS Interrupt 10h (Video) - Clear window with", hex(bl), "(", hex(cx), hex(dx), ")")
			#else:
			#	print("BIOS Interrupt 10h (Video) - Scroll up window by", hex(al), "lines", "(", hex(bl), hex(cx), hex(dx), ")")
			#pass

			al = uc.reg_read(UC_X86_REG_AL)  # Number of lines to scroll
			bh = uc.reg_read(UC_X86_REG_BH)  # Attribute (color)
			ch = uc.reg_read(UC_X86_REG_CH)  # Upper-left row
			cl = uc.reg_read(UC_X86_REG_CL)  # Upper-left col
			dh = uc.reg_read(UC_X86_REG_DH)  # Lower-right row
			dl = uc.reg_read(UC_X86_REG_DL)  # Lower-right col

			if DEBUG_BIOS: print(f"[BIOS] INT 10h, AH=06h: Scroll {al} lines from ({ch},{cl}) to ({dh},{dl}) with attribute {bh:02X}")

			# Simulate clearing the screen (if AL == 0)
			if al == 0:
				for row in range(ch, dh + 1):
					for col in range(cl, dl + 1):
						idx = (row * 80 + col) * 2  # Memory index
						TEXT_MODE_MEMORY[idx] = 0x20  # Space char
						TEXT_MODE_MEMORY[idx + 1] = bh  # Attribute

			# Simulate a screen scroll (if AL > 0)
			else:
				return
				for row in range(ch, dh + 1 - al):
					for col in range(cl, dl + 1):
						src_idx = ((row + al) * 80 + col) * 2
						dest_idx = (row * 80 + col) * 2
						TEXT_MODE_MEMORY[dest_idx] = TEXT_MODE_MEMORY[src_idx]
						TEXT_MODE_MEMORY[dest_idx + 1] = TEXT_MODE_MEMORY[src_idx + 1]

				# Clear bottom rows
				for row in range(dh - al + 1, dh + 1):
					for col in range(cl, dl + 1):
						idx = (row * 80 + col) * 2
						TEXT_MODE_MEMORY[idx] = 0x20  # Space char
						TEXT_MODE_MEMORY[idx + 1] = bh  # Attribute


		elif ah == 0xf:
			# https://www.gladir.com/LEXIQUE/INTR/int10f0f.htm
			if DEBUG_BIOS: print("BIOS Interrupt 10h (Video) - Video Mode", hex(al))
			uc.reg_write(UC_X86_REG_AX, 0x5002)
		elif ah == 0x8:
			# https://www.gladir.com/LEXIQUE/INTR/int10f08.htm
			if DEBUG_BIOS: print("BIOS Interrupt 10h (Video) - Read character and attribute at cursor position")
			#uc.reg_write(UC_X86_REG_AH, SCREEN.get_curs_color())
			#uc.reg_write(UC_X86_REG_AL, SCREEN.get_curs_char())
		elif ah == 0x11:
			# https://www.gladir.com/LEXIQUE/INTR/int10f1130.htm
			if DEBUG_BIOS: print("BIOS Interrupt 10h (Video) - Change text mode character set", hex(al))
		else:
			print("BIOS Interrupt 10h (Video) Unknown Function", f"{hex(ah)}:{hex(al)}")
			done()
	elif intno == 0x16:
		if ah == 0x0:
			# https://www.gladir.com/LEXIQUE/INTR/int10f1130.htm
			if DEBUG_BIOS: print("BIOS Interrupt 16h (Keyboard) - Read key press", hex(al))
			uc.reg_write(UC_X86_REG_AL, get_key())
		else:
			print("BIOS Interrupt 16h (Keyboard) Unknown Function", f"{hex(ah)}:{hex(al)}")
			done()
	else:
		print(f"Unhandled Interrupt {hex(intno)} - Stopping!")
		done()


def hook_mem_access(uc, access, address, size, value, user_data):
	if address > 0xb8000:
		print("[*] Memory access: {} at 0x{}, data size = {}, data value = 0x{}".format(access, address, size, value))

def hook_call(self, uc, address, size, user_data):
	print('>>> Call instruction at 0x%x, instruction size = 0x%x' % (address, size))

# Emulate I/O port reads for `IN AL, DX`.
def hook_ioport(uc, port, size, user_data):
	print(f"[I/O] IN AL, DX | Read {hex(value)} from port {hex(port)}")
	#value = 0xFF  # Default unknown port value
	#if port == 0x6:  
	#	value = 0x1
	#elif port == 0x60:  # Example: Keyboard data port
	#	value = 0x1C  # Simulating Enter key scan code
	#elif port == 0x3DA:  # VGA Status Register
	#	value = 0x08  # Simulating VGA Vertical Retrace


	# Store the read value into AL
	#uc.reg_write(UC_X86_REG_AL, value)

def hook_mem_video_write(uc, access, address, size, value, user_data):
	"""Intercept writes to video memory and update TEXT_MODE_MEMORY."""
	global TEXT_MODE_MEMORY, TEXT_MODE_CURSOR_OFFSET, TEXT_MODE_SEQ
	if VIDEO_MEMORY_ADDR <= address < VIDEO_MEMORY_ADDR + VIDEO_MEMORY_SIZE:
		offset = address - VIDEO_MEMORY_ADDR  # Convert to index
		if offset == 0:
			TEXT_MODE_SEQ = 0
		elif offset == TEXT_MODE_SEQ+2:
			TEXT_MODE_SEQ = offset
			TEXT_MODE_CURSOR_OFFSET+=1
		TEXT_MODE_MEMORY[TEXT_MODE_CURSOR_OFFSET*2] = value & 0xFF  # Store only 1 byte
		if DEBUG_VIDEO: print(f"[VIDEO] Write {hex(value)} {chr(value & 0xFF)} to 0x{address:X} (offset {offset}) (cursor {TEXT_MODE_CURSOR_OFFSET})")
		#monitor.refresh()

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
#emu.hook_add(UC_HOOK_MEM_READ, hook_mem_access)
#emu.hook_add(UC_HOOK_MEM_READ | UC_HOOK_MEM_WRITE, hook_mem_access)
#emu.hook_add(UC_HOOK_INSN, hook_call, None, 1, 0, UC_X86_INS_CALL)
# Hook I/O Reads (IN instruction)
#emu.hook_add(UC_HOOK_INSN, hook_ioport, None, 1, 0, UC_X86_INS_IN)

# Patches
nop=0x90
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


# Start Execution
try:
    emu.emu_start(starting_point, 0)
except Exception as e:
    print(f"Emulation stopped: {e}")
