vector<ll> SA(string& s) {
    ll n = s.size(), m = max(256LL, n) + 1;
    vector<ll> sa(n), r(n + n), nr(n + n), idx(n), cnt(m);
    for (ll i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for (ll d = 1; d < n; d <<= 1) {
        auto cmp = [&](ll i, ll j) {
            return r[i] < r[j] || (r[i] == r[j] && r[i + d] < r[j + d]);
        };

        for (ll i = 0; i < m; i++) cnt[i] = 0;
        for (ll i = 0; i < n; i++) cnt[r[i + d]]++;
        for (ll i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (ll i = n - 1; i >= 0; i--) idx[--cnt[r[i + d]]] = i;

        for (ll i = 0; i < m; i++) cnt[i] = 0;
        for (ll i = 0; i < n; i++) cnt[r[i]]++;
        for (ll i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (ll i = n - 1; i >= 0; i--) sa[--cnt[r[idx[i]]]] = idx[i];

        nr[sa[0]] = 1;
        for (ll i = 1; i < n; ++i) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        r = nr;

        if (r[sa[n - 1]] == n) break;
    }
    return sa;
}


vector<ll> LCP(vector<ll>& sa, string& s) {
    ll n = s.size();
    vector<ll> lcp(n,0), isa(n);
    for (ll i = 0; i < n; i++) isa[sa[i]] = i;
    for (ll k = 0, i = 0; i < n; i++) {
        if (isa[i]) {
            for (ll j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
            lcp[isa[i]] = (k ? k-- : 0);
        }
    }
    return lcp;
}
