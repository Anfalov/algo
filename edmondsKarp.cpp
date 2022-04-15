#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>

using namespace std;

#define INF 1000000000

struct edge {
	int flow;
	int capacity;
};

int n, m;

vector<map<int, edge>> g;
vector<int> d, p;

bool bfs(int s, int t)
{
	d.assign(n, INF);
	p.assign(n, -1);
	queue<int> q;
	d[s] = 0;
	q.push(s);
	while (q.size())
	{
		int v = q.front();
		q.pop();
		for (auto to : g[v])
			if (d[to.first] == INF && to.second.capacity - to.second.flow > 0)
			{
				d[to.first] = d[v] + 1;
				p[to.first] = v;
				q.push(to.first);
			}
	}
	return d[t] < INF;
}

void findPath(int t, vector<int>& path)
{
	path.clear();
	while (t != -1)
	{
		path.push_back(t);
		t = p[t];
	}
	reverse(path.begin(), path.end());
}

void edmondsKarp(int s, int t)
{
	while (bfs(s, t))
	{
		vector<int> path;
		findPath(t, path);
		int minFlow = INF;
		for (int i = 0; i < path.size() - 1; i++)
		{
			auto cur = g[path[i]][path[i + 1]];
			if (cur.capacity - cur.flow < minFlow)
				minFlow = cur.capacity - cur.flow;
		}
		for (int i = 0; i < path.size() - 1; i++)
		{
			g[path[i]][path[i + 1]].flow += minFlow;
			g[path[i + 1]][path[i]].flow -= minFlow;
		}
	}
}

int main()
{
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b, capacity;
		cin >> a >> b >> capacity;
		a--; b--;
		g[a][b] = {0, capacity};
		g[b].insert({ a, { 0, 0 } });
	}
	int s = 0, t = n - 1;

	edmondsKarp(s, t);
	int flow = 0;
	for (auto& e : g[s])
		flow += e.second.flow;
	cout << flow;
}
