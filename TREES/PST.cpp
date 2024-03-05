// 포인터 구현. 느리고 메모리 많이 먹음.
// 하단에 배열 구현 있음.
// https://justicehui.github.io/medium-algorithm/2020/02/29/PST/

struct Node {
    Node* l, * r;
    ll val;
    Node() { l = r = NULL; val = 0; }
};

Node* root[100002];
vector<ll> x;
ll a[100002];
ll n, m, r, i, j, k;

void init(Node* node, ll s, ll e) {
    if (s == e) {
        node->val = 0;
        return;
    }
    ll mid = (s + e) / 2;
    node->l = new Node();
    node->r = new Node();
    init(node->l, s, mid);
    init(node->r, mid + 1, e);
    node->val = node->l->val + node->r->val;
}

void update(Node* prv, Node* now, ll s, ll e, ll x, ll v) {
    if (s == e) {
        now->val = prv->val + v;
        return;
    }
    ll mid = (s + e) / 2;
    if (x <= mid) {
        now->l = new Node();
        now->r = prv->r;
        update(prv->l, now->l, s, mid, x, v);
    }
    else {
        now->r = new Node();
        now->l = prv->l;
        update(prv->r, now->r, mid + 1, e, x, v);
    }
    now->val = now->l->val + now->r->val;
}

ll query(Node* right, Node* left, ll s, ll e, ll k) {
    if (s == e) return s;
    ll d = right->l->val - left->l->val;
    ll mid = (s + e) / 2;
    if (d >= k) return query(right->l, left->l, s, mid, k);
    else return query(right->r, left->r, mid + 1, e, k - d);
}

void solve() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        x.push_back(a[i]);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    map<ll, ll> ma;
    for (ll i = 1; i <= n; i++) {
        ll tmp = a[i];
        a[i] = 1 + (lower_bound(x.begin(), x.end(), a[i]) - x.begin());
        ma[a[i]] = tmp;
    }
    ll p = x.size();
    for (ll i = 0; i <= n; i++) root[i] = new Node();
    init(root[r], 1, p);
    for (ll i = 1; i <= n; i++, r++) update(root[r], root[r + 1], 1, p, a[i], 1);  
    while (m--) {
        cin >> i >> j >> k;
        cout << ma[query(root[j], root[i - 1], 1, p, k)] << endl;
    }
}

******************************************************************************************

//배열 구현
//포인터에 비해 메모리, 속도 good
//포인터 구현 남겨둔 이유: 저게 더 쉽고 직관적인 듯...
//https://blog.naver.com/PostView.nhn?blogId=ingu9981&logNo=221605411695&parentCategoryNo=&categoryNo=19&viewDate=&isShowPopularPosts=true&from=search

struct PST {
    int l, r, v;
    PST() : l(0), r(0), v(0) {}
};

PST tree[300030]; //최악의 경우 생성 될 세그트리 노드의 개수만큼 넉넉히 만들기.
int tn; //새로 노드 만들 때, 인덱스임.

void update(int prv, int now, int s, int e, int idx, int v) {
    if(s==e) {
        tree[now].v=tree[prv].v+v;
        return;
    }
    int mid=s+e>>1;
    if(idx<=mid) {//왼쪽 자식 업데이트
        if(tree[now].l==0 || tree[now].l==tree[prv].l) tree[now].l=tn++;
        //왼쪽 자식이 없거나, 이전꺼랑 같으면 새로 만들어 줘야 함. tree[tn]이 그것
        
        if(tree[now].r==0) tree[now].r=tree[prv].r;
        //오른쪽 자식이 빈 노드면 이전 거 그대로 사용
        
        update(tree[prv].l,tree[now].l,s,mid,idx,v);
    }
    else {
        if(tree[now].r==0 || tree[now].r==tree[prv].r) tree[now].r=tn++;
        if(tree[now].l==0) tree[now].l=tree[prv].l;
        update(tree[prv].r,tree[now].r,mid+1,e,idx,v);
    }
    tree[now].v=tree[tree[now].l].v+tree[tree[now].r].v;
}

int query(int node, int s, int e, int l, int r) {
    if(l<=s && e<=r) return tree[node].v;
    if(s>r || e<l) return 0;
    int mid=s+e>>1;
    return query(tree[node].l,s,mid,l,r) + query(tree[node].r,mid+1,e,l,r);
}
