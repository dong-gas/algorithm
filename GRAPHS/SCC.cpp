#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007
#define INF 1000000000000000000
#define all(v) v.begin(), v.end()
#define zip(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll n, m, id, SN = 1;
ll d[200020];
ll sn[200020];
ll ans[200020];
bool finished[200020];
vector<ll> adj[200020];
vector<vector<ll>> SCC;
stack<ll> s;

//찾은 SCC 순서 뒤집으면 위상정렬된 상태.

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

ll rev(ll x) { //2-sat에서 not 구하기
	if (x <= n) return x + n;
	return x - n;
}

void solve() {
    cin >> n >> m;
    while (m--) {
        ll u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (ll i = 1; i <= 2 * n; i++) if (!d[i]) dfs(i);
    
    //여기서부터는 2-sat
    //(a or b)면 !a->b, !b->a 추가해야 함.
    for (ll i = 1; i <= n; i++) {
		if (sn[i] == sn[i + n]) {//같은 SCC면 모순
			cout << 0 << endl;
			return;
		}
	}
	cout << 1 << endl;
	reverse(SCC.begin(), SCC.end()); //위상정렬
	for (auto vec : SCC) {
		for (auto now : vec) {//앞쪽부터 0을 먼저 채우면서 감.
			if (ans[now]) continue;
			ans[now] = 0;
			ans[rev(now)] = 1;
		}
	}
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int tc = 1; //cin >> tc; 
    while (tc--) solve();
}
