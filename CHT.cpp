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
