#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <tuple>
using namespace std;

// 自定义比较结构体，用于优先队列按照第一个元素排序（降序），这里针对tuple进行比较
struct CompareTuples {
    bool operator()(const tuple<uint64_t, int, int>& a, const tuple<uint64_t, int, int>& b) {
        return get<0>(a) > get<0>(b);
    }
};

// 函数功能类似C#中对列表的扩展方法，这里作为普通函数接受一个无符号整数向量
vector<uint64_t> orderedSumOfList(vector<uint32_t>& a, int k) {
    // 检查输入合法性，若列表为空或者包含0则抛出异常（这里简单用assert模拟异常情况判断）
    if (a.size() == 0) {
        cerr << "list empty" << endl;
        assert(false);
    }
    for (auto &num : a) {
        if (num == 0) {
            cerr << "list contains 0" << endl;
            assert(false);
        }
    }

    // 排序
    sort(a.begin(), a.end());

    vector<uint64_t> result;
    result.push_back(0);

    // 定义优先队列，存储三元组以及对应的和，用于按照和来排序（使用自定义比较器实现大顶堆），这里使用tuple类型
    priority_queue<tuple<uint64_t, int, int>, vector<tuple<uint64_t, int, int>>, CompareTuples> pq;
    // 初始元素入队，第一个元素的和、起始索引、结束索引，使用make_tuple构造tuple元素
    pq.push(make_tuple(a[0], 0, a.size() - 1));
    while (result.size() < k) {
        uint64_t sm = get<0>(pq.top());
        int i = get<1>(pq.top()), limit = get<2>(pq.top());
        pq.pop();

        result.push_back(sm);

        // op1: add a[0]
        uint64_t nx = sm + a[0];
        pq.push(make_tuple(nx, 0, i));

        // op2: move a[i] to a[i + 1] (limit: a[i] only taken 1)
        if (i + 1 <= limit) {
            nx = sm - a[i] + a[i + 1];
            pq.push(make_tuple(nx, i + 1, limit));
        }
    }

    return move(result);
}

void runGeneratorTest() {
    vector<uint32_t> a;
    a.push_back(2);
    a.push_back(31);
    auto result = orderedSumOfList(a, 50);
    for (auto &x : result)
        cout << x << " ";
    cout << endl;
}