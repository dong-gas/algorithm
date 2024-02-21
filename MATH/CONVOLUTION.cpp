//XOR
//아래 코드를 실행하고 나면 a에 a와 b의 xor convolution이 저장됨.
//a[i]에는 a[j]^b[k]이 i인 (j, k)쌍의 수가 정해짐. (j==k, j>k, j<k 다 세짐)
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

fxht_xor(a,false);
fxht_xor(b,false);
for(int i=0;i<(1ll<<n);i++) a[i]*=b[i];
fxht_xor(a,true);

//AND, OR도 같은 작업 하면 됨. 아래는 검증 필요.
void fwht_and(vector<ll> &a, bool inv) {
    ll n = a.size();
    int dir = inv ? -1 : 1;
    for(int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for(int l = 0; l < n; l += s)
            for(int i = 0; i < h; i++)
                a[l + h] += dir * a[l + h + i];
}
void fwht_or(vector<ll> &a, bool inv) {
    ll n = a.size();
    int dir = inv ? -1 : 1;
    for(int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for(int l = 0; l < n; l += s)
            for(int i = 0; i < h; i++)
                a[l + h + i] += dir * a[l + i];
}
