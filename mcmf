#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007
#define INF 9876543210
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const ll N = 808;

ll n, m, x, y;
ll cap[N][N];   //용량
ll cost[N][N];  //비용
ll flow[N][N];  //유량
ll cache[N];    //이전 노드 저장하는 용도
ll dis[N];      //거리
bool inQ[N];    //큐 안에 있는지 확인하는 용도s
vector<ll> adj[N];


void add_edge(ll from, ll to, ll ca, ll co) {//용량, 비용
	adj[from].push_back(to);
	adj[to].push_back(from);
	cap[from][to] = ca;
	cap[to][from] = 0;
	cost[to][from] = -co;
	cost[from][to] = co;
}

pll mcmf(ll src, ll sink) {
	ll min_cost = 0;
	ll max_flow = 0;
	while (1) {
		queue<ll> q;
		memset(cache, -1, sizeof(cache));
		memset(inQ, false, sizeof(inQ));
		fill(dis, dis + N, 9876543210);
		dis[src] = 0;
		inQ[src] = true;
		q.push(src);
		while (!q.empty()) {
			ll now = q.front();
			q.pop();
			inQ[now] = false;
			for (ll nxt : adj[now]) {
				if (cap[now][nxt] - flow[now][nxt] > 0 && dis[nxt] > dis[now] + cost[now][nxt]) {
					dis[nxt] = dis[now] + cost[now][nxt];
					cache[nxt] = now;
					if (!inQ[nxt]) {
						q.push(nxt);
						inQ[nxt] = true;
					}
				}
			}
		}
		if (cache[sink] == -1) break;
		ll fl = INF;
		for (ll i = sink; i != src; i = cache[i]) fl = min(fl, cap[cache[i]][i] - flow[cache[i]][i]);
		for (ll i = sink; i != src; i = cache[i]) {
			min_cost += fl * cost[cache[i]][i];
			flow[cache[i]][i] += fl;
			flow[i][cache[i]] -= fl;
		}
		max_flow += fl;
	}
	return { min_cost,max_flow };
}

void solve() {
	cin >> n >> m;
	for (ll i = 1; i <= n; i++) {
		ll cnt;
		cin >> cnt;
		for (ll j = 1; j <= cnt; j++) {
			cin >> x >> y;
			add_edge(i, n + x, 1, y);
		}
	}
	for (ll i = 1; i <= n; i++) add_edge(0, i, 1, 0);
	for (ll i = 1; i <= m; i++) add_edge(n + i, m + n + 1, 1, 0);
	pll ans = mcmf(0, m + n + 1);
	cout << ans.second << endl << ans.first << endl;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1; //cin >> tc;
	while (tc--) solve();
}
