#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long;

struct Trie {
    Trie* ch[26];
    int key;
    Trie() {
        fill(ch, ch + 26, nullptr);
        key = 0;
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (ch[i]) delete ch[i];
    }
    void insert(string& s, int idx) {
        if (s.size() == idx) {
            key = 1;
            return;
        }
        if (!ch[s[idx] - 'a']) ch[s[idx] - 'a'] = new Trie();
        ch[s[idx] - 'a']->insert(s, idx + 1);
    }
};

ll n, ans;
string s;

void dfs(Trie* u, ll cnt) {
    bool chk = false;
    if (u->key) {
        ans += cnt;
        chk = true;
    }
    int nxtcnt = 0;
    for (int i = 0; i < 26; i++)
        if (u->ch[i]) nxtcnt++;
    if (nxtcnt > 1) chk = true;
    for (int i = 0; i < 26; i++)
        if (u->ch[i]) dfs(u->ch[i], cnt + chk);
}

void solve() {
    Trie* T = new Trie();
    ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> s;
        T->insert(s, 0);
    }
    for (int i = 0; i < 26; i++)
        if (T->ch[i]) dfs(T->ch[i], 1);
    cout << fixed << setprecision(2) << 1.0 * ans / n << '\n';
    delete T;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // cin >> tc;
    while (cin >> n) solve();
}
