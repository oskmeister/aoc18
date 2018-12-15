import sys
seen = set()
lines = sys.stdin.readlines()
s = 0
seen.add(0)
while True:
    for x in lines:
        s = s + int(x)
        if s in seen:
            print s
            exit()
        seen.add(s)
