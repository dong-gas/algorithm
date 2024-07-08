//ax+by=c
//ax+by=gcd(a,b)를 만족하는 x와 y를 s와 t에 저장.
//c가 gcd(a,b)의 배수일 때만 가능 (이게 아니라면 x,y는 존재 안 함)
//gcd(a,b)가 return됨.
//log 시간

ll ex_gcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll ret = ex_gcd(b, a % b, x, y);
    ll tmp = y;
    y = x - (a / b) * y;
    x = tmp;
    /*x가 양수여야 하면
    if (x <= 0) {
        x += b;
        y -= a;
    }*/
    return ret;
}

===
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
};
