import sys

raw = ""

for line in sys.stdin:
    raw += line

stuff = raw.split("M")

parsed = []
for thing in stuff:
    num = 0
    if len(thing) < 6:
        parsed.append(" ")
        continue
    for i in range(5):
        if thing[5-i] == 'O': num += 2**i
    # print(thing, "=>", num, "=>", chr(ord('a')+num-1))
    if thing[0] == 'o': parsed.append(chr(ord('A') + num - 1) + thing[6:])
    else: parsed.append(chr(ord('a') + num - 1) + thing[6:])

print("".join(parsed).strip())
