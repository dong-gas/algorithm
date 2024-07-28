Line Container..
Li Chao는 TREES 폴더에

1. Online으로 Convex hull을 construct할 수 있는 구현체
max값 찾을 때 쓰이는 템플릿이므로, min을 원할 때는 m, k부호 반대로 넣고, -query(q)로 사용.
  2.와 다르게 기울기에 단조성 없어도 됨.
/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	//double이면 inf를 전역으로 빼서 const double inf = 1/.0; 하면 됨
	//ll -> double로 바꿔서 쓰면 됨.
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

//최대가 되는 인덱스 출력해야 할 때
//근데, 그 인덱스가 여러 곳일 때 아무거나 출력하는 거면 ㄱㅊ은데, 젤 작은거 or 젤 큰 거처럼 기준 있으면 어케해야 할 지 몰겠다...
struct Line {
	mutable ld k, m, p;
	mutable ll idx;	
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ld x) const { return p < x; }
};

const ld inf = 1/.0;

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	//double이면 inf를 전역으로 빼서 const double inf = 1/.0; 하면 됨
	//ll -> double로 바꿔서 쓰면 됨.
	//static const ll inf = LLONG_MAX;
	ld div(ld a, ld b) { // floored division
		//return a / b - ((a ^ b) < 0 && a % b); 
		return a/b;
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ld k, ld m, ll idx) {
		auto z = insert({k, m, 0, idx}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ld x) {
		assert(!empty());
		auto l = *lower_bound(x);
		//cout<<l.k<<' '<<x<<' '<<l.m<<' '<<l.idx<<' '<<l.k*x+l.m<<endl;
		return l.idx;
	}
} s;

/*----------------------------------------------------------------------------------------------*/    

2. 내가 예전에 쓰던거...
* dp[i] = min(dp[j] + b[j] * a[i]), j < i
* b[j] >= b[j+1] 

struct lin {
    ll a, b; //기울기, y절편
};

ll n, ans;
ll p = 1, sz = 1;
ll a[200020];
lin stk[200020];

double cx(ll a, ll b) {
    if (!a) return -1e18;
    return 1.0 * (double)(stk[a].b - stk[b].b) / (stk[b].a - stk[a].a);
}

void insert(lin v) {
    stk[sz] = v;
    while (sz > 2 && cx(sz - 2, sz - 1) > cx(sz - 1, sz)) {
        stk[sz - 1] = stk[sz];
        sz--;
    }
    sz++;
}

ll get(ll x) {//x값이 증가만 할 때 -> 이분탐색 필요 X
    while (p + 1 < sz && cx(p, p + 1) <= x) p++;
    return stk[p].a * x + stk[p].b;
}

ll getget(ll x) { //x값이 와리가리 들어올 땐 이분탐색으로
    ll low = 1, high = sz - 1, ret = 1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (cx(mid - 1, mid) <= x) {
            ret = max(ret, mid);
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return stk[ret].a * x + stk[ret].b;
}
