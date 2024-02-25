int sz[101010], dep[101010], par[101010], top[101010], in[101010], out[101010];
vector<int> g[101010];   //inp를 단방향 그래프로 변환한 그래프
vector<int> inp[101010]; //입력 / 양방향 그래프

void dfs(int u, int p){
  for(auto& v: inp[u]) {
    if(v==p) continue;
    dfs(v,u);
    g[u].emplace_back(v);
  }
}

void dfs1(int u){
	sz[u] = 1;
	for(auto &v : g[u]){
		dep[v] = dep[u] + 1; par[v] = u;
		dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
	}
}

int pv;
void dfs2(int u){
	in[u] = ++pv;
	for(auto v : g[u]){
		top[v] = (v == g[u][0]) ? top[u] : v;
		dfs2(v);
	}
	out[u] = pv;
}

int query(int a, int b){
    int ret = 0;
    while(top[a] ^ top[b]){ //같은 체인이 아니면 진행
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret += seg.query(in[st], in[a]);
        a = par[st];
    }
    if(dep[a] > dep[b]) swap(a, b);
    ret += seg.query(in[a], in[b]);
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q; //정점 개수, 쿼리 개수
    for(int i=1; i<n; i++){
        int s, e; cin >> s >> e;
        inp[s].push_back(e);
        inp[e].push_back(s);
    }
    dfs();    //양방향 그래프를 단방향 그래프로 변경
    dfs1();   //깊이, 부모, 크기 저장 + 맨 앞을 heavy로 수정
    dfs2();   //오일러투어 + 각 체인의 top 원소 저장
    while(q--){
        //1 v w : update v w
        //2 s e : query s e
        int op, a, b; cin >> op >> a >> b;
        if(op == 1) update(a, b);
        else cout << query(a, b) << "\n";
    }
}
