import random

for i in range(3):
    print(random.randint(0, 255), end=" ")
print()

nums = []
for i in range(256):
    nums.append(i+1)

random.shuffle(nums)

for i in nums:
    print(i, end=" ")

print()
