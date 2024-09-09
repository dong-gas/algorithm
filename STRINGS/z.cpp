void Z(string& s, vector<int>& z) {
    // z[i]: s[i..n)와 s의 가장 긴 공통 접두사
    int N = s.size(), l = 0, r = 0;
    z.resize(N, 0);
    z[0] = N;
    for (int i = 1; i < N; i++) {
        if (i <= r) z[i] = min(r - i, z[i - l]);
        for (; s[i + z[i]] == s[z[i]];) z[i]++;
        if (i > r) l = i;
        r = max(r, i + z[i] - 1);
    }
}
