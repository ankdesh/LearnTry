import random

with open('100000randInts.txt','w') as f:
   for i in [random.randint(-10000,10000) for x in range(100000)]:
       f.write(str(i) + ' ')
