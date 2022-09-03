#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007
#define INF 9876542310
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const ll N = 450;

ll n, f, d, x, y, k;
ll cap[N][N];
ll flow[N][N];
ll level[N];
ll work[N];
vector<ll> adj[N];

void add_edge(ll from, ll to, ll c) {
    adj[from].push_back(to);
    adj[to].push_back(from);
    cap[from][to] = c;
}

bool bfs(ll src, ll sink) {
    fill(level, level + N, -1);
    fill(work, work + N, 0);
    level[src] = 0;

    queue<ll> q;
    q.push(src);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (ll nxt : adj[now]) {
            if (level[nxt] == -1 && cap[now][nxt] > flow[now][nxt]) {
                level[nxt] = level[now] + 1;
                q.push(nxt);
            }
        }
    }
    return level[sink] != -1;
}

ll dfs(ll now, ll sink, ll amount) {
    if (now == sink) return amount;
    for (ll& i = work[now]; i < adj[now].size(); i++) {
        ll nxt = adj[now][i];
        if (level[nxt] == level[now] + 1 && cap[now][nxt] - flow[now][nxt] > 0) {
            ll df = dfs(nxt, sink, min(cap[now][nxt] - flow[now][nxt], amount));
            if (df > 0) {
                flow[now][nxt] += df;
                flow[nxt][now] -= df;
                return df;
            }
        }
    }
    return 0;
}

ll dinic(ll src, ll sink) {
    ll max_flow = 0;
    while (bfs(src, sink)) {
        while (1) {
            ll df = dfs(src, sink, INF);
            if (!df) break;
            max_flow += df;
        }
    }
    return max_flow;
}

void solve() {
    cin >> n >> f >> d;
    for (ll i = 1; i <= n; i++) {
        cin >> x >> y;//f d
        for (ll j = 1; j <= x; j++) {
            cin >> k;
            add_edge(2 * n + k, i, 1);
        }
        for (ll j = 1; j <= y; j++) {
            cin >> k;
            add_edge(n + i, 2 * n + f + k, 1);
        }
    }
    for (ll i = 1; i <= n; i++) add_edge(i, i + n, 1);
    for (ll i = 1; i <= f; i++) add_edge(0, 2 * n + i, 1);
    for (ll i = 1; i <= d; i++) add_edge(2 * n + f + i, 2 * n + f + d + 1, 1);
    cout << dinic(0, 2 * n + f + d + 1) << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1; //cin >> tc;
    while (tc--) solve();
}
