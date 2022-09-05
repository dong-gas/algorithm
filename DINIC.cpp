//O(V^2E)
const ll MAXN = 555;
struct edge {
    ll to, cap, rev;
};
ll level[MAXN];
ll work[MAXN];
vector<edge> adj[MAXN];

void add_edge(ll from, ll to, ll c) {
    adj[from].push_back({ to, c, (ll)adj[to].size() });
    adj[to].push_back({ from, 0, (ll)adj[from].size() - 1 });
}

bool bfs(ll src, ll sink) {
    fill(level, level + MAXN, -1);
    fill(work, work + MAXN, 0);
    level[src] = 0;

    queue<ll> q;
    q.push(src);
    while (!q.empty()) {
        ll now = q.front(); q.pop();
        for (auto& e : adj[now]) {
            if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[now] + 1;
                q.push(e.to);
            }
        }
    }
    return level[sink] != -1;
}

ll dfs(ll now, ll sink, ll amount) {
    if (now == sink) return amount;
    for (ll& i = work[now]; i < adj[now].size(); i++) {
        auto e = adj[now][i];
        if (e.cap > 0 && level[e.to] == level[now] + 1) {
            ll df = dfs(e.to, sink, min(amount, e.cap));
            if (df > 0) {
                adj[now][i].cap -= df;
                adj[e.to][e.rev].cap += df;
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
