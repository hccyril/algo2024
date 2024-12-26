#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <tuple>
using namespace std;

// �Զ���ȽϽṹ�壬�������ȶ��а��յ�һ��Ԫ�����򣨽��򣩣��������tuple���бȽ�
struct CompareTuples {
    bool operator()(const tuple<uint64_t, int, int>& a, const tuple<uint64_t, int, int>& b) {
        return get<0>(a) > get<0>(b);
    }
};

// ������������C#�ж��б����չ������������Ϊ��ͨ��������һ���޷�����������
vector<uint64_t> orderedSumOfList(vector<uint32_t>& a, int k) {
    // �������Ϸ��ԣ����б�Ϊ�ջ��߰���0���׳��쳣���������assertģ���쳣����жϣ�
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

    // ����
    sort(a.begin(), a.end());

    vector<uint64_t> result;
    result.push_back(0);

    // �������ȶ��У��洢��Ԫ���Լ���Ӧ�ĺͣ����ڰ��պ�������ʹ���Զ���Ƚ���ʵ�ִ󶥶ѣ�������ʹ��tuple����
    priority_queue<tuple<uint64_t, int, int>, vector<tuple<uint64_t, int, int>>, CompareTuples> pq;
    // ��ʼԪ����ӣ���һ��Ԫ�صĺ͡���ʼ����������������ʹ��make_tuple����tupleԪ��
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