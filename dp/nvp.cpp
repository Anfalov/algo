#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> v(n), dp(n, 1), p(n, -1);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (v[j] < v[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				p[i] = j;
			}
	int mxi = max_element(dp.begin(), dp.end()) - dp.begin();
	cout << dp[mxi] << endl;
	vector<int> res;
	while (mxi != -1)
	{
		res.push_back(v[mxi]);
		mxi = p[mxi];
	}
	reverse(res.begin(), res.end());
	//for (int e : res)
	//	cout << e << " ";
}
