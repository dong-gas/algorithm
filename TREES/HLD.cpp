//https://justicehui.github.io/hard-algorithm/2020/01/24/hld/
struct Heavy_Light_Decomposition {
    ll sz[NMAX], dep[NMAX], papa[NMAX], top[NMAX], in[NMAX], out[NMAX], pv;
    vector<ll> inp[NMAX], g[NMAX];
    //inp: 입력(양방향), g: inp를 단방향 그래프로 변환한 그래프
    void init() {
        dfs(1,0), dfs1(1), dfs2(1);
    }
    void dfs(int u, int p) {
        for(auto& v: inp[u]) if(v!=p) {
            dfs(v,u);
            g[u].emplace_back(v);
        }
    }
    void dfs1(int u) {
        sz[u]=1;
        for(auto &v: g[u]) {
            dep[v]=dep[u]+1, papa[v]=u;
            dfs1(v), sz[u]+=sz[v];
            if(sz[v]>sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs2(int u) {
        in[u]=++pv;
        for(auto v:g[u]) {
            top[v]=(v==g[u][0])?top[u]:v;
            dfs2(v);
        }
        out[u]=pv;
    }
    void update(int u, int val) {
        seg.update(in[u], val);                      //세그 호출 인자는 비재귀면 바꾸기.
    }
    ll query(int u, int v) {
        ll ret=0;
        while(top[u] ^ top[v]) {
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            int st=top[u];
            ret+=seg.query(in[st], in[u]);           //세그 호출 인자는 비재귀면 바꾸기.
            u=papa[st];
        }
        if(dep[u]>dep[v]) swap(u,v);
        ret+=seg.query(in[u], in[v]);                //세그 호출 인자는 비재귀면 바꾸기.
        return ret;
    }
} hld;

/*
입력 그래프는 g가 아닌 inp에 받기.
hld.init();
hld.update(u, val);
hld.query(u, v);
in신경 안 써도 됨. hld 템플릿에서 변환해서 함.
*/
