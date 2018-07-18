#!/usr/bin/env python3

tot = 0
for line in open("ToDo.md"):
	if "[ ]" in line:
		n = line.split("[ ]")[1][1:3]
		if n.isdigit():
			tot += int(n)

print(tot)
