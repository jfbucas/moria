DEBUG_BIOS=False
DEBUG_DOS=False

# FileHandle
files_handles = {}

# Hook Interrupts
def hook_interrupt(uc, intno, user_data):
	global DEBUG_DOS, DEBUG_BIOS, TEXT_MODE_MEMORY, TEXT_MODE_CURSOR_OFFSET
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

