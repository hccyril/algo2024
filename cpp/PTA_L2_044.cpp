#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
using namespace std;

#define inf 0x3f3f3f3f
bool gender[501]; // 维护性别 false-男，true-女
int g[501][501]; // 维护图的最短路径,邻接矩阵表示

// version 2 - 尝试进行一些优化 - AC (结论：bitset和vector比较慢= =)
int pta_l2_044() {
	memset(g, 0x3f, sizeof(g)); // 即初始值=1061109567，约1e9
	int n; cin >> n;

	int i, j, k, t; // 临时变量，提前统一定义

	// 读入数据构建图
	for (i = 1; i <= n; i++) {
		char c; cin >> c;
		gender[i] = c == 'F';
		cin >> k;
		while (k--) {
			cin >> j >> c >> t;
			g[i][j] = t;
		}
	}

	// floyd多源最短路 (#以下四行为固定写法，要记牢）
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				g[i][j] = min((g[i][k] + g[k][j]), g[i][j]);

	// 根据题意找到答案并输出
	// 计算及输出女生的大众情人
	vector<int> ans;
	int minmax_d = inf;
	for (i = 1; i <= n; i++)
		if (gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (!gender[j])
					maxd = max(maxd, g[j][i]); // 注意是j到i的距离
			if (maxd < minmax_d) {
				minmax_d = maxd;
				ans.clear();
				ans.push_back(i);
			}
			else if (maxd == minmax_d) {
				ans.push_back(i);
			}
		}
	cout << ans[0];
	for (i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	cout << endl;
	// 计算及输出男生的大众情人（实际编码时复制上面代码再修改即可）
	ans.clear();
	minmax_d = inf;
	for (i = 1; i <= n; i++)
		if (!gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (gender[j])
					maxd = max(maxd, g[j][i]); // 注意是j到i的距离
			if (maxd < minmax_d) {
				minmax_d = maxd;
				ans.clear();
				ans.push_back(i);
			}
			else if (maxd == minmax_d) {
				ans.push_back(i);
			}
		}
	cout << ans[0];
	for (i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	cout << endl;

	return 0;
}

// 超时，原因不明
int pta_l2_044_TLE() {
	int n; cin >> n;
	bitset<501> gender; // 性别，0-男，1-女
	vector<vector<int>> g(n + 1, vector<int>(n + 1, 1e9)); // 邻接矩阵表示图

	int i, j, k, t; // 临时变量，提前统一定义

	// 读入数据构建图
	for (i = 1; i <= n; i++) {
		char c; cin >> c;
		gender[i] = c == 'F';
		cin >> k;
		while (k--) {
			cin >> j >> c >> t;
			g[i][j] = t;
		}
	}

	// floyd多源最短路 (#以下四行为固定写法，要记牢）
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				g[i][j] = min((g[i][k] + g[k][j]), g[i][j]);

	// 根据题意找到答案并输出
	// 计算及输出女生的大众情人
	vector<int> ans;
	int minmax_d = 1e9;
	for (i = 1; i <= n; i++)
		if (gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (!gender[j])
					maxd = max(maxd, g[j][i]); // 注意是j到i的距离
			if (maxd < minmax_d) {
				minmax_d = maxd;
				ans.clear();
				ans.push_back(i);
			}
			else if (maxd == minmax_d) {
				ans.push_back(i);
			}
		}
	cout << ans[0];
	for (i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	cout << endl;
	// 计算及输出男生的大众情人（实际编码时复制上面代码再修改即可）
	ans.clear(); 
	minmax_d = 1e9;
	for (i = 1; i <= n; i++)
		if (!gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (gender[j])
					maxd = max(maxd, g[j][i]); // 注意是j到i的距离
			if (maxd < minmax_d) {
				minmax_d = maxd;
				ans.clear();
				ans.push_back(i);
			}
			else if (maxd == minmax_d) {
				ans.push_back(i);
			}
		}
	cout << ans[0];
	for (i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	cout << endl;

	return 0;
}

/*
输入样例：
6
F 1 4:1
F 2 1:3 4:10
F 2 4:2 2:2
M 2 5:1 3:2
M 2 2:2 6:2
M 2 3:1 2:5

输出样例：
2 3
4
*/