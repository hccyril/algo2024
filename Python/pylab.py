from collections import Counter
from heapq import heappop, heappush, heapreplace
import time
import tracemalloc

print_stat = 0 # 是否输出优先队列长度等信息

# 朴素算法 - 用于比较
def simpleSum(p: list[int]):
    hs = set()
    hp = [(0.0, "")]
    while hp:
        sm, s = heappop(hp)
        cnt = Counter()
        if s:
            a = list(map(int, s.split()))
            for i in range(0, len(a), 2):
                k, c = a[i], a[i + 1]
                cnt[k] = c
        for i, x in enumerate(p):
            sm += x
            cnt[i] += 1
            a = []
            for k in sorted(cnt):
                a.append(str(k))
                a.append(str(cnt[k]))
            sk = ' '.join(a)
            if not sk in hs:
                hs.add(sk)
                heappush(hp, (sm, sk))
            cnt[i] -= 1
            if cnt[i] == 0:
                del cnt[i]
            sm -= x

# 论文提出的最小增量枚举算法
def orderedSum(p: list[int]):
    if not p or p.count(0) > 0:
        raise ValueError("list empty or list contains 0")
    # p.sort() # 直接给定排序的向量，无需自己排序
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

def run():
    global print_stat
    # print_stat = 1

    # 测试数据：长度为三百万的权值向量
    p = [i * 0.0031 for i in range(1, 3001)]

    run_my_algorithm = 0

    k = 300
    # return k

    if run_my_algorithm:
        i = 0
        for sm in orderedSum(p):
            i += 1
            if i == k:
                return sm
    else:
        i = 0
        for sm in simpleSum(p):
            i += 1
            if i == k:
                return sm

def test():
    # 开始追踪内存分配
    tracemalloc.start()
    # 开始时间
    start_time = time.time()
    # 调用 run 方法
    result = run()
    # 结束时间
    end_time = time.time()
    # 结束追踪内存分配
    current, peak = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    # 计算运行时间

    t0, m0 = 0, 0

    # 初始化消耗5.87秒以及91.92MB，对应的实验结果要减去这个数字
    # test 1
    # t0, m0 = 0.06, 0.92
    # t0, m0 = 0.86, 9.35

    # test 2
    #t0, m0 = 5.87, 91.92 
    #  
    elapsed_time = end_time - start_time
    elapsed_time -= t0
    print(f"程序运行结果: {result}")
    print(f"程序运行时间: {elapsed_time:.2f} 秒")
    mb = peak / 1024 / 1024
    mb -= m0
    print(f"程序使用内存峰值: {mb:.2f} MB")

if __name__ == "__main__":
    test()