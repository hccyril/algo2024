#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
using namespace std;

#define inf 0x3f3f3f3f
bool gender[501]; // ά���Ա� false-�У�true-Ů
int g[501][501]; // ά��ͼ�����·��,�ڽӾ����ʾ

// version 2 - ���Խ���һЩ�Ż� - AC (���ۣ�bitset��vector�Ƚ���= =)
int pta_l2_044() {
	memset(g, 0x3f, sizeof(g)); // ����ʼֵ=1061109567��Լ1e9
	int n; cin >> n;

	int i, j, k, t; // ��ʱ��������ǰͳһ����

	// �������ݹ���ͼ
	for (i = 1; i <= n; i++) {
		char c; cin >> c;
		gender[i] = c == 'F';
		cin >> k;
		while (k--) {
			cin >> j >> c >> t;
			g[i][j] = t;
		}
	}

	// floyd��Դ���· (#��������Ϊ�̶�д����Ҫ���Σ�
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				g[i][j] = min((g[i][k] + g[k][j]), g[i][j]);

	// ���������ҵ��𰸲����
	// ���㼰���Ů���Ĵ�������
	vector<int> ans;
	int minmax_d = inf;
	for (i = 1; i <= n; i++)
		if (gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (!gender[j])
					maxd = max(maxd, g[j][i]); // ע����j��i�ľ���
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
	// ���㼰��������Ĵ������ˣ�ʵ�ʱ���ʱ��������������޸ļ��ɣ�
	ans.clear();
	minmax_d = inf;
	for (i = 1; i <= n; i++)
		if (!gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (gender[j])
					maxd = max(maxd, g[j][i]); // ע����j��i�ľ���
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

// ��ʱ��ԭ����
int pta_l2_044_TLE() {
	int n; cin >> n;
	bitset<501> gender; // �Ա�0-�У�1-Ů
	vector<vector<int>> g(n + 1, vector<int>(n + 1, 1e9)); // �ڽӾ����ʾͼ

	int i, j, k, t; // ��ʱ��������ǰͳһ����

	// �������ݹ���ͼ
	for (i = 1; i <= n; i++) {
		char c; cin >> c;
		gender[i] = c == 'F';
		cin >> k;
		while (k--) {
			cin >> j >> c >> t;
			g[i][j] = t;
		}
	}

	// floyd��Դ���· (#��������Ϊ�̶�д����Ҫ���Σ�
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				g[i][j] = min((g[i][k] + g[k][j]), g[i][j]);

	// ���������ҵ��𰸲����
	// ���㼰���Ů���Ĵ�������
	vector<int> ans;
	int minmax_d = 1e9;
	for (i = 1; i <= n; i++)
		if (gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (!gender[j])
					maxd = max(maxd, g[j][i]); // ע����j��i�ľ���
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
	// ���㼰��������Ĵ������ˣ�ʵ�ʱ���ʱ��������������޸ļ��ɣ�
	ans.clear(); 
	minmax_d = 1e9;
	for (i = 1; i <= n; i++)
		if (!gender[i]) {
			int maxd = 0;
			for (j = 1; j <= n; j++)
				if (gender[j])
					maxd = max(maxd, g[j][i]); // ע����j��i�ľ���
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
����������
6
F 1 4:1
F 2 1:3 4:10
F 2 4:2 2:2
M 2 5:1 3:2
M 2 2:2 6:2
M 2 3:1 2:5

���������
2 3
4
*/