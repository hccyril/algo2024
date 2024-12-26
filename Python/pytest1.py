from heapq import heappop, heappush, heappushpop

counter = 0
count_pushpop = 0
count_push = 0

class Node(object):
    def __init__(self, val: int):
        self.val = val

    def __repr__(self):
        return str(self.val)

    def __lt__(self, other):
        global counter, count_pushpop
        counter += 1
        if count_pushpop == 1:
            print('comp', self.val, other.val)
        return self.val < other.val
    
hp = []
x = 1
for _ in range(1000000):
    x = (x << 1) % 1000000007
    if len(hp) == 100000:
        # heappushpop(hp, Node(x))
        # count_pushpop += 1
        counter += 1 # 下面那句if算一次比较
        if x > hp[0].val:
            heappop(hp)
            if count_pushpop == 1:
                print('pop done now push', x)
            heappush(hp, Node(x))
            count_pushpop += 1
    else:
        heappush(hp, Node(x))
        count_push += 1

print('ans =', hp[0], hp[-1])
print('count =', counter)
print('count_pushpop =', count_pushpop)
print('count_push =', count_push)
print('pq size =', len(hp))
       
