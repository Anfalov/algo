#include <iostream>
#include<deque>
#include<vector>
#include<map>
using namespace std;

#define INF 2009000999

struct edge {
    int flow;
    int capacity;
	int cost;
};


int n, m;
vector<map<int, edge>> g;
vector<int> dist, par, used;

bool levit(int s, int t)
{
	used.resize(n, 0);
	dist.assign(n, INF);
	par.assign(n, -1);
    deque<int> q;
    q.push_front(s);
    dist[s] = 0;
    while (q.size())
    {
        int v = q.front();
        used[v] = 2;
        q.pop_front();
        for (pair<int, edge> to : g[v])
            if (to.second.capacity - to.second.flow > 0 &&
				(dist[to.first] == INF || dist[to.first] > dist[v] + to.second.cost))
            {
                dist[to.first] = dist[v] + to.second.cost;
                par[to.first] = v;
                if (used[to.first] == 0)
                    q.push_back(to.first);
                else if (used[to.first] == 2)
                    q.push_front(to.first);
                used[to.first] = 1;
            }
    }
	return dist[t] != INF;
}

void findPath(int t, vector<int>& path)
{
	path.clear();
	while (t != -1)
	{
		path.push_back(t);
		t = par[t];
	}
	reverse(path.begin(), path.end());
}

void edmondsKarp(int s, int t)
{
	while (levit(s, t))
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
		g[a][b] = { 0, capacity };
		g[b].insert({ a, { 0, 0 } });
	}
	int s = 0, t = n - 1;

	edmondsKarp(s, t);
	int flow = 0;
	for (auto& e : g[s])
		flow += e.second.flow;
	cout << flow;
}
