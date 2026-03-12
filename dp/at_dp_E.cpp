#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 500010
#define inf 0x7f7f7f7f
int n, m;
int v[N], w[N];
int dp[N];
signed main()
{
	int W;
	cin >> n>>W;
	int V = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i] >> v[i];
		V +=v[i];
	}
	for (int i = 1; i <= V; i++)dp[i] = inf;
	for (int i = 1; i <= n; i++)
	{
		for (int j = V; j >=v[i]; j--)
		{	
			dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
			//cout << dp[j] << endl;
		}
	}
	for (int i = V; i; i--)									
	{
		if (dp[i] <= W)
		{
			cout << i; return 0;
		}
	}
	pair<int, int> p;
	
	return 0;
	//dp时一个维度太大可以用反函数的思想，用另一个维度为索引，大维度为dp值
	//前缀和优化dp时一定不要忘了减法取模需要先加mod再取
}