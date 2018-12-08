import sys

lines = sys.stdin.readlines()
for line in sorted(lines):
    l = line.split()
    time = l[1][:-1]
    hh, mm = time.split(':')
    if l[2] == 'falls':
        print 'fall', mm
    elif l[2] == 'wakes':
        print 'wake', mm
    else:
        print 'guard', l[3][1:], mm
