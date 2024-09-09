void Z(string& s, vector<int>& z) {
    // z[i]: s[i..n)와 s의 가장 긴 공통 접두사
    int N = s.size(), l = 0, r = 0;
    z.resize(N, 0);
    z[0] = N;
    for (int i = 1; i < N; i++) {
        if (i > r) {
            l = r = i;
            while (r < N && s[r - l] == s[r]) r++;
            z[i] = r - l;
            r--;
        }
        else {
            int k = i - l;
            if (z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while (r < N && s[r - l] == s[r]) r++;
                z[i] = r - l;
                r--;
            }
        }
    }
}
