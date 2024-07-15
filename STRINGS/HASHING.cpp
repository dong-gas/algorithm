//해싱
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Hashing {
	const ll M=998244353;
	ll P;
    vector<ll> H, B;
    void Build(const string& S, ll cnt) { //cnt: 서로다른 문자의 개수
		//cnt+1보다 sqrt(M)이 충분히 크면 범위를 [cnt+1 , sqrt(M)]으로 하면 더 좋음.
		static uniform_int_distribution<int> f(cnt+1, M - 1);
		P=f(rng);
        H.resize(S.size() + 1);
        B.resize(S.size() + 1);
        B[0] = 1;
        for (ll i = 1; i <= S.size(); i++) H[i] = (H[i - 1] * P + S[i - 1]) % M;
        for (ll i = 1; i <= S.size(); i++) B[i] = B[i-1] * P % M;
    }
    ll sub(ll s, ll e) { //0-based로 호출
        s++; e++;
		ll ret = (H[e] - H[s - 1] * B[e - s + 1]) % M;
		return ret < 0 ? ret + M : ret;
    }
};

//2중해싱
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Hashing {
	const ll M0=998244353, M1=1'000'000'007;
	ll P0, P1;
    vector<vector<ll>> H, B;
    void Build(const string& S, ll cnt) { //cnt: 서로다른 문자의 개수
		//cnt+1보다 sqrt(M)이 충분히 크면 범위를 [cnt+1 , sqrt(M)]으로 하면 더 좋음.
		static uniform_int_distribution<int> f(cnt+1, M0 - 1);
		static uniform_int_distribution<int> g(cnt+1, M1 - 1);
		P0=f(rng), P1=g(rng);
        H.resize(S.size() + 1,vector<ll>(2));
        B.resize(S.size() + 1,vector<ll>(2));
        B[0][0] = B[0][1]= 1;
        for (ll i = 1; i <= S.size(); i++) {
			H[i][0] = (H[i - 1][0] * P0 + S[i - 1]) % M0;
			H[i][1] = (H[i - 1][1] * P1 + S[i - 1]) % M1;
		}
        for (ll i = 1; i <= S.size(); i++) {
			B[i][0] = B[i-1][0] * P0 % M0;
			B[i][1] = B[i-1][1] * P1 % M1;
		}
    }
    pll sub(ll s, ll e) { //0-based로 호출
        s++; e++;
		ll ret0 = (H[e][0] - H[s - 1][0] * B[e - s + 1][0]) % M0;
		ll ret1 = (H[e][1] - H[s - 1][1] * B[e - s + 1][1]) % M1;
		if(ret0 < 0) ret0 += M0;
		if(ret1 < 0) ret1 += M1;
        return {ret0, ret1};
    }
};
