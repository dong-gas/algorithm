//FFT
//TLE 나면 double로 gogo
typedef complex<double> base;
#define double long double 
void fft(vector <base>& a, bool invert)
{
	int n = sz(a);
	vector<base>roots(n / 2);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 2; i <= n; i <<= 1) {
		vector<base> w(i / 2);
		for (int j = 0; j < i / 2; ++j) {
			double th = 2 * acos(-1.L)*j / i * (invert ? -1 : 1);
			w[j] = base(cos(th), sin(th));
		}
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; ++k) {
				base u = a[j + k], v = a[j + k + i / 2] * w[k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (invert)	for (int i = 0; i < n; i++)a[i] /= n;
}

void multiply(const vector<ll>& a, const vector<ll >& b, vector<ll>& res)
{
	vector <base> fa(all(a)), fb(all(b));
	ll n = 1;
	while (n < max(sz(a), sz(b))) n <<= 1;
	n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i < n; i++) res[i] = ll(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}
