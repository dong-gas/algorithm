ll n, m, id, SN = 1;
ll d[200020];
ll sn[200020];
ll ans[200020];
bool finished[200020];
vector<ll> adj[200020];
vector<vector<ll>> SCC;
stack<ll> s;

ll dfs(ll x) {
    d[x] = ++id;
    s.push(x);
    ll parent = d[x];
    for (ll i = 0; i < adj[x].size(); i++) {
        ll y = adj[x][i];
        if (d[y] == 0) parent = min(parent, dfs(y));
        else if (!finished[y]) parent = min(parent, d[y]);
    }
    if (parent == d[x]) {
        vector<ll> scc;
        while (1) {
            ll t = s.top();
            s.pop();
            scc.push_back(t);
            finished[t] = true;
            sn[t] = SN;
            if (t == x) break;
        }
        SCC.push_back(scc);
        SN++;
    }
    return parent;
}

void solve() {
    cin >> n >> m;
    while (m--) {
        ll u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (ll i = 1; i <= n; i++) if (!d[i]) dfs(i);
}
