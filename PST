#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = int;
using pll = pair<ll, ll>;

struct Node {
    Node* l, * r;
    ll val;
    Node() { l = r = NULL; val = 0; }
};

Node* root[100002];
vector<ll> x;
ll a[100002];
ll n, m, r, i, j, k;

void init(Node* node, ll s, ll e) {
    if (s == e) {
        node->val = 0;
        return;
    }
    ll mid = (s + e) / 2;
    node->l = new Node();
    node->r = new Node();
    init(node->l, s, mid);
    init(node->r, mid + 1, e);
    node->val = node->l->val + node->r->val;
}

void update(Node* prv, Node* now, ll s, ll e, ll x, ll v) {
    if (s == e) {
        now->val = prv->val + v;
        return;
    }
    ll mid = (s + e) / 2;
    if (x <= mid) {
        now->l = new Node();
        now->r = prv->r;
        update(prv->l, now->l, s, mid, x, v);
    }
    else {
        now->r = new Node();
        now->l = prv->l;
        update(prv->r, now->r, mid + 1, e, x, v);
    }
    now->val = now->l->val + now->r->val;
}

ll query(Node* right, Node* left, ll s, ll e, ll k) {
    if (s == e) return s;
    ll d = right->l->val - left->l->val;
    ll mid = (s + e) / 2;
    if (d >= k) return query(right->l, left->l, s, mid, k);
    else return query(right->r, left->r, mid + 1, e, k - d);
}

void solve() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        x.push_back(a[i]);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    map<ll, ll> ma;
    for (ll i = 1; i <= n; i++) {
        ll tmp = a[i];
        a[i] = 1 + (lower_bound(x.begin(), x.end(), a[i]) - x.begin());
        ma[a[i]] = tmp;
    }
    ll p = x.size();
    for (ll i = 0; i <= n; i++) root[i] = new Node();
    init(root[r], 1, p);
    for (ll i = 1; i <= n; i++, r++) update(root[r], root[r + 1], 1, p, a[i], 1);  
    while (m--) {
        cin >> i >> j >> k;
        cout << ma[query(root[j], root[i - 1], 1, p, k)] << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1; //cin >> tc;
    while (tc--) solve();
}
