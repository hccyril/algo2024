from heapq import heappush, heapreplace

def orderedSum(a: list[int]):
    if not a or a.count(0) > 0:
        raise ValueError("list empty or list contains 0")
    a.sort()
    yield 0
    hp = [(a[0], 0, len(a) - 1)] # heap<sum, index, limit>
    while hp:
        sm, i, limit = hp[0] # 放到后面一起调heapreplace，提高效率
        yield sm

        # op1: add a[0]
        nx = sm + a[0]
        heapreplace(hp, (nx, 0, i))

        # op2: move a[i] to a[i + 1] (limit: a[i] only taken 1)
        if i + 1 <= limit:
            nx = sm - a[i] + a[i + 1]
            heappush(hp, (nx, i + 1, limit))

if __name__ == '__main__':
    i = 0
    for x in orderedSum([2, 31]):
        print(x)
        i += 1
        if i == 50:
            break
    