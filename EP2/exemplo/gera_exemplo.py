#!/usr/bin/python3
import sys
import numpy as np

mat = int(sys.argv[1])
print(mat)
print("***")

for i in range(mat):
  for a in range(3):
    var = np.random.randint(0, 50,size=3)
    print("%d  %d  %d" % (var[0], var[1], var[2]))
  print("***")
