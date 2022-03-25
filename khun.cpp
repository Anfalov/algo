#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n1, n2;
vector<vector<int>> g;
vector<char> used;
vector<int> mt;

bool try_khun(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (auto to: g[v])
        if (mt[to] == -1 || try_khun(mt[to]))
        {
            mt[to] = v;
            return true;
        }
    return false;
}

int main()
{
    int m;
    cin >> n1 >> n2 >> m;
    g.resize(n1);
    used.resize(n1);
    mt.resize(n2, -1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        ;
    }
    vector<int> used2(n1);
    for (int i = 0; i < n1; i++)
    {
        for (auto to: g[i])
            if (!mt[to])
            {
                mt[to] = i;
                used2[i] = 1;
                break;
            }
    }
    for (int i = 0; i < n1; i++)
        if (!used2[i])
            if (try_khun(i))
                used.assign(n1, 0);
    
    for (int i = 0; i < n2; i++)
        if (mt[i] != -1)
            cout << mt[i] + 1 << " " << i + 1 << endl;
}
