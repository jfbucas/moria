from unicorn.x86_const import *
import struct

def exe_load(uc, exe="TEST.EXE"):
	LOAD_SEG = 0x1000  # Typical DOS EXE load segment

	# Load EXE
	with open(exe, "rb") as f:
		exe_data = f.read()

	# Ensure file is large enough
	if len(exe_data) < 28:
		print("File too small to be a valid MZ executable!")
		exit()

	# Correct unpacking of 28 bytes
	mz_header = struct.unpack("<2s13H", exe_data[:28])  

	"""
	0    self.magic = (self._io.read_bytes(2)).decode(u"ASCII")
	1    self.last_page_extra_bytes = self._io.read_u2le()
	2    self.num_pages = self._io.read_u2le()
	3    self.num_relocations = self._io.read_u2le()
	4    self.header_size = self._io.read_u2le()
	5    self.min_allocation = self._io.read_u2le()
	6    self.max_allocation = self._io.read_u2le()
	7    self.initial_ss = self._io.read_u2le()
	8    self.initial_sp = self._io.read_u2le()
	9    self.checksum = self._io.read_u2le()
	0    self.initial_ip = self._io.read_u2le()
	1    self.initial_cs = self._io.read_u2le()
	2    self.ofs_relocations = self._io.read_u2le()
	3    self.overlay_id = self._io.read_u2le()
	"""

	e_magic = mz_header[0]  # Signature (should be b'MZ')
	e_crlc = mz_header[3]  # Number of relocations
	e_cparhdr = mz_header[4]  # Header size (paragraphs, *16 = bytes)
	init_ss = mz_header[7]  # Stack segment (relative)
	init_sp = mz_header[8]  # Stack pointer
	init_ip = mz_header[10]  # Entry point (offset)
	init_cs = mz_header[11]  # Entry segment (relative)
	e_lfarlc = mz_header[12]  # Relocation table offset

	if e_magic != b"MZ":
		print("Not a valid DOS MZ executable!")
		exit()

	header_size = e_cparhdr * 16  # Convert paragraphs to bytes

	print(f"EXE Header Parsed:")
	print(f"  Entry Point: CS:IP = {hex(init_cs)}:{hex(init_ip)}")
	print(f"  Stack: SS:SP = {hex(init_ss)}:{hex(init_sp)}")
	print(f"  Header Size: {header_size} bytes")
	print(f"  Relocation Table: Offset = {hex(e_lfarlc)}, Entries = {e_crlc}")

	# Apply Relocations
	for i in range(e_crlc):
		entry_offset = e_lfarlc + i * 4
		offset, segment = struct.unpack("<HH", exe_data[entry_offset:entry_offset+4])

		# Compute absolute address to patch
		address = (segment * 16) + offset + (e_cparhdr * 16)

		# Read old value (16-bit pointer)
		old_value = struct.unpack("<H", exe_data[address:address+2])[0]

		# Apply relocation fix-up by adding the load segment
		new_value = old_value + LOAD_SEG

		# Patch the memory
		exe_data = exe_data[:address] + struct.pack("<H", new_value) + exe_data[address + 2:]

		#print(f"Patched {hex(address)}: {hex(old_value)} -> {hex(new_value)}")

	# Load EXE code & data
	uc.mem_write(LOAD_SEG * 16, exe_data[header_size:])

	# Set CPU Registers
	uc.reg_write(UC_X86_REG_CS, LOAD_SEG + init_cs)
	uc.reg_write(UC_X86_REG_IP, init_ip)
	uc.reg_write(UC_X86_REG_SS, LOAD_SEG + init_ss)
	uc.reg_write(UC_X86_REG_SP, init_sp)

	return LOAD_SEG * 16 + init_ip


