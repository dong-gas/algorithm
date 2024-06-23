#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/extc++.h>
#define all(v) v.begin(), v.end()
#define zip(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define sz(v) (int)(v).size()
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef pair<int, int> pint;

using namespace __gnu_pbds;
template<class T> using PBDS = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc=1; //cin>>tc;
    while(tc--) solve();
}
