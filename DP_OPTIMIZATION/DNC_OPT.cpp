void f(int i,int s, int e, int optl, int optr) {
	if(s>e) return;
	int m=s+e>>1;
	ll ret=1e18, opt=optl;
	for(ll j=optl;j<=optr;j++) {
		ll now=dp[i-1][j]+(a[m]-a[j])*(m-j);
		if(now<ret) {
			ret=now;
			opt=j;
		}
	}
	dp[i][m]=ret;
	f(i,s,m-1,optl,opt), f(i,m+1,e,opt,optr);
}
