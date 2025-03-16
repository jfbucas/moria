import time
import threading

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


