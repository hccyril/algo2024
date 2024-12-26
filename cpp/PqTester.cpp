#include "PqTester.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

unsigned int counter = 0;
unsigned int count_pushpop = 0;
struct mycomp {
	constexpr bool operator()(const int& a, const int& b) const {
		++counter;
		if (count_pushpop == 1) {
			cout << "comp " << a << " " << b << endl;
		}
		return a > b;
	}
};

int runPriorityQueueTest() {
	priority_queue<int, vector<int>, mycomp> pq;
	int rep = 1000000;
	int x = 1;
	while (rep--) {
		x = (x << 1) % 1000000007;
		if (pq.size() == 100000) {
			++counter;
			if (x > pq.top()) {
				pq.pop();
				if (count_pushpop == 1)
					cout << "pq.pop done. now emplace " << x << endl;
				pq.emplace(x);
				++count_pushpop;
			}
		}
		else pq.emplace(x);
	}
	cout << "ans=" << pq.top() << endl;
	cout << "count=" << counter << endl;
	cout << "pushpop=" << count_pushpop << endl;
	cout << "pq size=" << pq.size() << endl;
	return 0;
}


