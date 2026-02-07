import os
import json

# Read the previous mapping
mapping = {}
if os.path.exists('mapping.json'):
	mapping = json.load(open( 'mapping.json', 'r'))

lines = open("reverse/MORIA.C").readlines()


out = open("reverse/MORIA_commented.C", "w+")

for l in lines:
	
