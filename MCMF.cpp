//O(Ef)
const ll N = 2020;

struct edge {
	ll to, cap, rev, cost;
};
vector<edge> adj[N];

ll n;
ll a[N];
ll dist[N], p[N], pe[N];
bool inQ[N];

void add_edge(ll u, ll v, ll c, ll cost) {
	adj[u].push_back({ v, c, (ll)adj[v].size(), cost });
	adj[v].push_back({ u, 0, (ll)adj[u].size() - 1, -cost });
}

bool spfa(ll s, ll t) {
    fill(dist, dist + N, INF);
    memset(inQ, 0, sizeof(inQ));

    queue<ll> q;
    q.emplace(s); dist[s] = 0; inQ[s] = 1;
    while (q.size()) {
        ll x = q.front(); q.pop();
        inQ[x] = 0;

        for (ll i = 0; i < adj[x].size(); i++) {
            auto& e = adj[x][i];
            if (e.cap && dist[x] + e.cost < dist[e.to]) {
                dist[e.to] = dist[x] + e.cost;
                p[e.to] = x; pe[e.to] = i;
                if (!inQ[e.to]) {
                    inQ[e.to] = 1;
                    q.emplace(e.to);
                }
            }
        }

    }
    return dist[t] != INF;
}

pll mcmf(ll s, ll t) {
    ll min_cost = 0, max_flow = 0, flow, rev;
    while (spfa(s, t)) {
        flow = INF;
        for (ll i = t; i != s; i = p[i])
            flow = min(flow, adj[p[i]][pe[i]].cap);
        min_cost += flow * dist[t];
        for (ll i = t; i != s; i = p[i]) {
            rev = adj[p[i]][pe[i]].rev;
            adj[p[i]][pe[i]].cap -= flow;
            adj[i][rev].cap += flow;
        }
    }
    max_flow += flow;
    return { min_cost,max_flow };
}
