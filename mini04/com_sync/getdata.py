#!/usr/bin/python3

import os
import sys
import numpy as np

os.system('sudo ./main %d %s000 > saida.txt' % (int(sys.argv[1]), int(sys.argv[2])))
print('sudo ./main %d %d000 > saida.txt' % 
	(int(sys.argv[1]), int(sys.argv[2])))

entrada = open('saida.txt', 'r')
bakery = [[], [], []]
gate = [[], [], []]
esse = [[], [], []]
# alg = [bakery, gate]

for line in entrada.readlines():
	a = line.split(':')
	if len(a) == 2:
		if a[0].split(' ')[0] == 'Elapsed':
			esse[0].append(int(a[1])/1000000)
		if a[0].split(' ')[0] == 'Average':
			esse[1].append(int(float(a[1])))
		if a[0].split(' ')[0] == 'Standard':
			esse[2].append(int(float(a[1])))
	elif len(a) == 3:
		alg = line.split(',')[0].split(':')[1].split(' ')[1]
		if alg == 'bakery':
			esse = bakery
		else:
			esse = gate

print('bakery Elapsed %f' % np.array(bakery[0], float).mean())
print('bakery Average %f' % np.array(bakery[1], float).mean())
print('bakery Standard %f' % np.array(bakery[2], float).mean())
print('gate Elapsed %f' % np.array(gate[0], float).mean())
print('gate Average %f' % np.array(gate[1], float).mean())
print('gate Standard %f' % np.array(gate[2], float).mean())
