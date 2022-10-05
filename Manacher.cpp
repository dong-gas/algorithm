ll n, ans;
ll a[N]; //N=2*문자열
string s, t;

void solve() {
    cin >> s;
    n = s.size();
    for (ll i = 0; i < n; i++) t += '#', t += s[i];
    t += '#';
    n = t.size();
    ll r = 0, p = 0;
    for (ll i = 0; i < n; i++) {
        if (i <= r) a[i] = min(a[2 * p - i], r - i);
        else a[i] = 0;
        while (i - a[i] - 1 >= 0 && i + a[i] + 1 < n && t[i - a[i] - 1] == t[i + a[i] + 1]) a[i]++;
        if (r < i + a[i]) r = i + a[i], p = i;
    }
}
