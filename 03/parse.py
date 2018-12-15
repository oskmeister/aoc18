import sys
lines = sys.stdin.readlines()
for line in lines:
    s = line.strip().split(' ')
    coords = s[2][:-1].split(',')
    size = s[3].split('x')
    print coords[0], coords[1], size[0], size[1]
