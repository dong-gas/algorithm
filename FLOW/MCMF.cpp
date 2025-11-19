//https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.tex
struct mincostflow {
    struct edg {
        int pos, cap, rev, cost;
    };

    vector<edg> gph[MAXN];

    void clear() {
        for (int i = 0; i < MAXN; i++) gph[i].clear();
    }

    void add_edge(int s, int e, int x, int c) {
        gph[s].push_back({e, x, (int) gph[e].size(), c});
        gph[e].push_back({s, 0, (int) gph[s].size() - 1, -c});
    }

    int phi[MAXN], inque[MAXN], dist[MAXN];

    void prep(int src, int sink) {
        memset(phi, 0x3f, sizeof(phi));
        memset(dist, 0x3f, sizeof(dist));
        queue<int> que;
        que.push(src);
        inque[src] = 1;
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            inque[x] = 0;
            for (auto& i: gph[x]) {
                if (i.cap > 0 && phi[i.pos] > phi[x] + i.cost) {
                    phi[i.pos] = phi[x] + i.cost;
                    if (!inque[i.pos]) {
                        inque[i.pos] = 1;
                        que.push(i.pos);
                    }
                }
            }
        }
        for (int i = 0; i < MAXN; i++) {
            for (auto& j: gph[i]) {
                if (j.cap > 0) j.cost += phi[i] - phi[j.pos];
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        pq.push({0, src});
        dist[src] = 0;
        while (!pq.empty()) {
            auto l = pq.top();
            pq.pop();
            if (dist[l.second] != l.first) continue;
            for (auto& i: gph[l.second]) {
                if (i.cap > 0 && dist[i.pos] > l.first + i.cost) {
                    dist[i.pos] = l.first + i.cost;
                    pq.push({dist[i.pos], i.pos});
                }
            }
        }
    }

    bool vis[MAXN];
    int ptr[MAXN];

    int dfs(int pos, int sink, int flow) {
        vis[pos] = 1;
        if (pos == sink) return flow;
        for (; ptr[pos] < gph[pos].size(); ptr[pos]++) {
            auto& i = gph[pos][ptr[pos]];
            if (!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0) {
                int ret = dfs(i.pos, sink, min(i.cap, flow));
                if (ret != 0) {
                    i.cap -= ret;
                    gph[i.pos][i.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    int match(int src, int sink, int sz) { // sz: 노드 값 중 가장 큰 거 + 1. 즉 [0, sz)를 사용
        prep(src, sink);
        for (int i = 0; i < sz; i++) dist[i] += phi[sink] - phi[src];
        int ret = 0;
        while (dist[sink] < 0) {
            memset(ptr, 0, sizeof(ptr));
            memset(vis, 0, sizeof(vis));
            int tmp = 0;
            while ((tmp = dfs(src, sink, 1e9))) {
                ret += dist[sink] * tmp;
                memset(vis, 0, sizeof(vis));
            }
            tmp = 1e9;
            for (int i = 0; i < sz; i++) {
                if (!vis[i]) continue;
                for (auto& j: gph[i]) {
                    if (j.cap > 0 && !vis[j.pos]) {
                        tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
                    }
                }
            }
            if (tmp > 1e9 - 200) break;
            for (int i = 0; i < sz; i++) {
                if (!vis[i]) dist[i] += tmp;
            }
        }
        return ret;
    }
} mcmf;

// ----------------------------------------------------------------------------------------------------------------------------------

//O(Ef)
//reference: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.pdf

//to do: https://justicehui.github.io/hard-algorithm/2020/03/24/effective-mcmf/

using pint = pair<int, int>;

const int N = 606, INF = 1e9;

struct edge {
    int to, cap, rev, cost;
};
vector<edge> adj[N];

int dist[N], p[N], pe[N];
bool inQ[N];

void add_edge(int u, int v, int c, int cost) {
    adj[u].push_back({v, c, (int) adj[v].size(), cost});
    adj[v].push_back({u, 0, (int) adj[u].size() - 1, -cost});
}

bool spfa(int s, int t) {
    fill(dist, dist + N, INF);
    memset(inQ, 0, sizeof(inQ));

    queue<int> q;
    q.emplace(s);
    dist[s] = 0;
    inQ[s] = 1;
    bool ok = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x == t) ok = 1;
        inQ[x] = 0;

        for (int i = 0; i < adj[x].size(); i++) {
            auto e = adj[x][i];
            if (e.cap > 0 && dist[x] + e.cost < dist[e.to]) {
                dist[e.to] = dist[x] + e.cost;
                p[e.to] = x;
                pe[e.to] = i;
                if (!inQ[e.to]) {
                    inQ[e.to] = 1;
                    q.emplace(e.to);
                }
            }
        }
    }
    return ok;
}

pint mcmf(int s, int t) {
    int min_cost = 0, max_flow = 0, flow, rev;
    while (spfa(s, t)) {
        flow = INF;
        for (int i = t; i != s; i = p[i]) flow = min(flow, adj[p[i]][pe[i]].cap);
        min_cost += flow * dist[t];
        for (int i = t; i != s; i = p[i]) {
            rev = adj[p[i]][pe[i]].rev;
            adj[p[i]][pe[i]].cap -= flow;
            adj[i][rev].cap += flow;
        }
        max_flow += flow;
    }
    return {min_cost, max_flow};
}
