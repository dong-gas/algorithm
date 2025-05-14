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
