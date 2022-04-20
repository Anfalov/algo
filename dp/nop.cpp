#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n, m;
	cin >> n;
	vector<int> v1(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> v1[i];
	cin >> m;
	vector<int> v2(m + 1);
	for (int i = 1; i <= m; i++)
		cin >> v2[i];
	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (v1[i] == v2[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
	cout << dp[n][m] << endl;
	
	int i = n, j = m;
	vector<int> res;
	while (i != 0 && j != 0)
		if (v1[i] == v2[j])
		{
			res.push_back(v1[i]);
			i--;
			j--;
		}
		else
			if (dp[i - 1][j] == dp[i][j])
				i--;
			else
				j--;
	reverse(res.begin(), res.end());
	for (int e : res)
		cout << e << " ";
}
