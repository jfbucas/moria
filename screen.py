from cp437 import cp437_unicode_map
#import curses

class Screen():
	def __init__(self):
		self.cursor_x = 0
		self.cursor_y = 0
		self.width    = 80
		self.height   = 25
		self.chars    = [ ord(" ") ] * (self.width*self.height)
		self.colors   = [  0  ] * (self.width*self.height)

	def get_char(self, x, y):
		return self.chars[x + y*self.width]
	def get_color(self, x, y):
		return self.colors[x + y*self.width]
	def set_char(self, x, y, c):
		self.chars[x + y*self.width] = ord(c)
	def set_color(self, x, y, c):
		self.colors[x + y*self.width] = c

	def get_curs_char(self):
		return self.chars[self.cursor_x + self.cursor_y*self.width]
	def get_curs_color(self):
		return self.colors[self.cursor_x + self.cursor_y*self.width]
	def set_curs_char(self, c):
		self.chars[self.cursor_x + self.cursor_y*self.width] = ord(c)
	def set_curs_color(self, c):
		self.colors[self.cursor_x + self.cursor_y*self.width] = c

	def clear(self):
		for y in range(self.height):
			for x in range(self.width):
				self.chars[x+y*self.width] = ord(" ")
				self.colors[x+y*self.width] = 0

	def print(self):
		for y in range(self.height):
			for x in range(self.width):
				c = chr(self.chars[x+y*self.width])
				print(f"\033[{y};{x}H{c}")
				
	def refresh(self, uc):
		contents = self.uc.mem_read( 0xB800*16+0, self.width*self.height*2 )
		for y in range(self.height):
			for x in range(self.width):
				c = contents[(x+y*self.width)*2]
				#c = chr(self.chars[x+y*self.width])
				print(f"\033[{y};{x}H{c}")
		


"""
import curses

def main(stdscr):
    stdscr.clear()
    stdscr.addch(10, 20, 'X')  # Print 'X' at (10,20)
    stdscr.refresh()
    stdscr.getch()  # Wait for key press

curses.wrapper(main)
"""
