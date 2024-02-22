void fwht_and(vector<ll> &a, bool inv) {
    ll n = a.size();
    ll dir = inv ? -1 : 1;
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for(ll l = 0; l < n; l += s)
            for(ll i = 0; i < h; i++)
                a[l + i] += dir * a[l + h + i];
}

void fwht_or(vector<ll> &a, bool inv) {
    ll n = a.size();
    ll dir = inv ? -1 : 1;
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for(ll l = 0; l < n; l += s)
            for(ll i = 0; i < h; i++)
                a[l + h + i] += dir * a[l + i];
}

void fwht_xor(vector<ll> &a, bool inv) {
    ll n = a.size();
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                ll t = a[l + h + i];
                a[l + h + i] = a[l + i] - t;
                a[l + i] += t;
                if(inv) a[l + h + i] /= 2, a[l + i] /= 2;
            }
        }
    }
}

vector<ll> convolution(vector<ll> a, vector<ll> b) {
    fwht_xor(a, false); //and or xor만 수정
    fwht_xor(b, false); //and or xor만 수정
    for(ll i=0;i<(1ll<<n);i++) a[i]*=b[i];
    fwht_xor(a, true);  //and or xor만 수정
    return a;
}
