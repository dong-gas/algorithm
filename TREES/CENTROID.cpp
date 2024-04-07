int sz[NMAX], use[NMAX], cent_papa[NMAX];

int get_size(int u, int p=0) {
    sz[u]=1;
    for(int v:adj[u]) {
        if(use[v] || p==v) continue;
        sz[u]+=get_size(v,u);
    }
    return sz[u];
}

int get_cent(int u, int p, int cnt) {
    for(int v:adj[u]) {
        if(use[v] || v==p) continue;
        if(sz[v]>cnt/2) return get_cent(v,u,cnt);
    }
    return u;
}

void dnc(int u, int p=0) {//p는 이전 cent
    int cent=get_cent(u,p,get_size(u,p));
    cent_papa[cent]=p;
    use[cent]=1;
    for(int v:adj[cent]) if(!use[v]) dnc(v,cent);
}

/*
아래는 정점 업데이트, 쿼리 있을 때... (트리와 쿼리5)
센트로이드 상의 모든 조상들에 대해 update해야 함.
u-v경로는 무조건 u의 센트로이드 상의 조상을 지나는 것을 이용할 때....
*/

void update(int u) {
    color[u]^=1;
    int now=u;
    do {
        int dist=get_dist(now,u);
        if(color[u]) s[now].insert(dist);
        else s[now].erase(s[now].find(dist));
        now=cent_papa[now];
    } while(now!=0);    
}

int query(int u) {
    int now=u, ret=1e9;
    do {        
        if(!s[now].empty()) ret=min(ret, get_dist(u,now) + *s[now].begin());
        now=cent_papa[now];        
    } while(now!=0);
    return (ret<1e9) ? ret : -1;
}

/*
dnc 내에서 아래와 같이 O(N) 탐색도 가능. 전체 O(NlogN)
Confuzzle
*/
void dnc(int u, int p=0) {
    int cent=get_cent(u,p,get_size(u,p));
    cent_papa[cent]=p;
    use[cent]=1;
    map<int,int> d;
    d[color[cent]]=0;
    for(int v:adj[cent]) {
        if(use[v]) continue;
        map<int,int> nd;
        dfs(v,cent,1,nd);
        for(auto [c, dist]:nd) {
            if(d.find(c)==d.end()) continue;
            ans=min(ans,dist+d[c]);
        }
        for(auto [c, dist]:nd) {
            if(d.find(c)==d.end()) d[c]=dist;
            else d[c]=min(d[c],dist);
        }
    }
    for(int v:adj[cent]) if(!use[v]) dnc(v,cent);
}
