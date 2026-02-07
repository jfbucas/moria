
DEBUG_VIDEO=False
#DEBUG_VIDEO=True
DEBUG_TERM=False

VIDEO_MEMORY_ADDR = 0xB8000
VIDEO_MEMORY_SIZE = 1024*8 # 80x25 characters, 2 bytes each

# Initialize a Python bytearray for text mode
TEXT_MODE_MEMORY = TEXT_MODE_MEMORY = bytearray(VIDEO_MEMORY_SIZE)
TEXT_MODE_CURSOR_OFFSET = 0

for row in range(25):
	for col in range(80):
		idx = (row * 80 + col)*2  # Memory index
		TEXT_MODE_MEMORY[idx] = 0x20  # Space char
		TEXT_MODE_MEMORY[idx+1] = 7

def hook_mem_video_write(uc, access, address, size, value, user_data):
	"""Intercept writes to video memory and update TEXT_MODE_MEMORY."""
	global TEXT_MODE_MEMORY, TEXT_MODE_CURSOR_OFFSET, monitor
	if VIDEO_MEMORY_ADDR <= address < VIDEO_MEMORY_ADDR + VIDEO_MEMORY_SIZE:
		char = value & 0xFF
		if DEBUG_VIDEO: print(f"[VIDEO] Write {chr(char)} {hex(value)} to 0x{address:X} (cursor {TEXT_MODE_CURSOR_OFFSET % 80},{TEXT_MODE_CURSOR_OFFSET // 80})")
		if char == 0x0d:
			print("End-line")
			TEXT_MODE_CURSOR_OFFSET -= TEXT_MODE_CURSOR_OFFSET % 80
			TEXT_MODE_CURSOR_OFFSET += 80
		else:
			#offset = address - VIDEO_MEMORY_ADDR  # Convert to index
			TEXT_MODE_MEMORY[TEXT_MODE_CURSOR_OFFSET*2] = char # Store only 1 byte
			TEXT_MODE_CURSOR_OFFSET+=1
		monitor.refresh()

def hook_mem_video_read(uc, access, address, size, value, user_data):
	"""Intercept reads from video memory and return the correct value."""
	global TEXT_MODE_MEMORY
	if VIDEO_MEMORY_ADDR <= address < VIDEO_MEMORY_ADDR + VIDEO_MEMORY_SIZE:
		offset = address - VIDEO_MEMORY_ADDR  # Convert to index
		value = TEXT_MODE_MEMORY[offset*2]
		print(f"[VIDEO] Read {hex(value)} from 0x{address:X} (offset {offset})")
		uc.reg_write(UC_X86_REG_AL, value)  # Store result in AL


# Monitor refresh
class Monitor(threading.Thread):
	def __init__(self, uc): #, screen):
		threading.Thread.__init__(self)
		self.uc = uc
		self.finish = False
		self.do_refresh = False
		self.pos_x = 0

	def refresh(self):
		self.do_refresh = True

	def run(self):
		global TEXT_MODE_MEMORY, hook_block_count, what_happening
		while not self.finish:
			if self.do_refresh:
				#self.do_refresh = False
				o="\033[s" # Save cursor
				# Screen
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

				# Debug info
				o+=f"\033[{25+4};{self.pos_x}HBlock Count: {hook_block_count} Now:{what_happening}"

				o+="\033[u" # Restore cursor
				print(o, end="")
			time.sleep(1/24)
			#time.sleep(0.5)
	def done(self):
		self.finish = True



