from heapq import heappush, heapreplace

def orderedSum(p: list[int]):
    if not p or p.count(0) > 0:
        raise ValueError("list empty or list contains 0")
    p.sort()
    yield 0
    hp = [(p[0], 0, len(p) - 1)] # heap<sum, index, limit>
    while hp:
        sm, i, limit = hp[0] # 放到后面一起调heapreplace，提高效率
        yield sm

        # op1: add a[0]
        nx = sm + p[0]
        heapreplace(hp, (nx, 0, i))

        # op2: move a[i] to a[i + 1] (limit: a[i] only taken 1)
        if i + 1 <= limit:
            nx = sm - p[i] + p[i + 1]
            heappush(hp, (nx, i + 1, limit))

if __name__ == '__main__':
    i = 0
    for x in orderedSum([2, 31]):
        print(x)
        i += 1
        if i == 50:
            break
    