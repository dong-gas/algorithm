string s, t;
ll fail[1000010];
vector<ll> ans;

void solve() {
	getline(cin, s);
	getline(cin, t);
	for (ll i = 1, j = 0; i < t.size(); i++) {
		while (j > 0 && t[i] != t[j]) j = fail[j - 1];
		if (t[i] == t[j]) fail[i] = ++j;
	}
	for (ll i = 0, j = 0; i < s.size(); i++) {
		while (j > 0 && s[i] != t[j]) j = fail[j - 1];
		if (s[i] == t[j]) {
			if (j == t.size() - 1) {
				ans.push_back(i - t.size() + 2);
				j = fail[j];
			}
			else j++;
		}
	}
	cout << ans.size() << endl;
	for (ll i = 0; i < ans.size(); i++) cout << ans[i] << endl;
}
