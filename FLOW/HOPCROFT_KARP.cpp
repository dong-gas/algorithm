//O(min(ESqrt(V),fE))
//reference: https://github.com/koosaga/DeobureoMinkyuParty

const int MAXN = 1010, MAXM = 1010;
int dis[MAXN],l[MAXN],r[MAXM],vis[MAXN];
vector<int> adj[MAXN];
void add_edge(int l,int r) {adj[l].push_back(r);}
//add_edge(i, n+j) X
//add_edge(i,j)    O

bool bfs(int n){
    queue<int> q;
    bool ok=0;
    memset(dis,0,sizeof(dis));
    for(int i=1;i<=n;i++) {
        if(l[i]==-1 && !dis[i]) q.push(i),dis[i]=1;
    }
    while(!q.empty()) {
        int x=q.front(); q.pop();
        for(auto &i: adj[x]) {
            if(r[i]==-1) ok=1;
            else if(!dis[r[i]]) {
                dis[r[i]]=dis[x]+1;
                q.push(r[i]);
            }
        }
    }
    return ok;
}

bool dfs(int x) {
    if(vis[x]) return 0;
    vis[x]=1;
    for(auto &i: adj[x]) {
        if(r[i]==-1 || (!vis[r[i]] && dis[r[i]] == dis[x]+1 && dfs(r[i]))) {
            l[x]=i,r[i]=x;
            return 1;
        }
    }
    return 0;
}

int match(int n){
    memset(l,-1,sizeof(l));
    memset(r,-1,sizeof(r));
    int ret=0;
    while(bfs(n)) {
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++) if(l[i]==-1 && dfs(i)) ret++;
    }
    return ret;
}

//find minimum vertex cover (=이분매칭)
//match함수로 이분매칭 돌리고 getcover 호출하면 됨.
bool chk[MAXN + MAXM];
void rdfs(int x, int n){
	if(chk[x]) return;
	chk[x] = 1;
	for(auto &i : gph[x]){
		chk[i + n] = 1;
		rdfs(r[i], n);
	}
}
vector<int> getcover(int n, int m){
	match(n);
	memset(chk, 0, sizeof(chk));
	for(int i=1; i<=n; i++) if(l[i] == -1) rdfs(i, n);
	vector<int> v;
	for(int i=1; i<=n; i++) if(!chk[i]) v.push_back(i);    //A
	for(int i=n+1; i<=n+m; i++) if(chk[i]) v.push_back(i); //B
	return v;
}
