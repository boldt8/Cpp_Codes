#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    int to;
    ll z;
};

// Globals to keep the DFS header simple
static vector<vector<Edge>> adj;
static vector<char> vis;
static vector<int> sgn;     // +1 or -1
static vector<ll> off;      // c_i
static bool ok;

void dfs(int u, vector<int>& comp, bool& hasT, ll& tFixed) {
    comp.push_back(u);

    for (const auto& e : adj[u]) {
        int v = e.to;
        ll z = e.z;

        if (!vis[v]) {
            vis[v] = 1;
            sgn[v] = -sgn[u];
            off[v] = z - off[u];
            dfs(v, comp, hasT, tFixed);
            if (!ok) return;
        } else {
            int sumS = sgn[u] + sgn[v]; // 0, +2, -2
            ll sumC = off[u] + off[v];

            if (sumS == 0) {
                // t cancels out, must match exactly
                if (sumC != z) {
                    ok = false;
                    return;
                }
            } else {
                // pins t: (sumS)*t + sumC = z
                ll num = z - sumC;
                if (num % sumS != 0) {
                    ok = false;
                    return;
                }
                ll cand = num / sumS;
                if (!hasT) {
                    hasT = true;
                    tFixed = cand;
                } else if (tFixed != cand) {
                    ok = false;
                    return;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<ll> L(N), R(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        for (int i = 0; i < N; i++) cin >> R[i];

        adj.assign(N, {});
        for (int i = 0; i < M; i++) {
            int x, y;
            ll z;
            cin >> x >> y >> z;
            --x; --y;
            adj[x].push_back({y, z});
            adj[y].push_back({x, z});
        }

        vis.assign(N, 0);
        sgn.assign(N, 0);
        off.assign(N, 0);
        ok = true;

        long long totalBest = 0;

        for (int start = 0; start < N && ok; start++) {
            if (vis[start]) continue;

            vector<int> comp;
            bool hasT = false;
            ll tFixed = 0;

            vis[start] = 1;
            sgn[start] = +1;
            off[start] = 0;

            dfs(start, comp, hasT, tFixed);
            if (!ok) break;

            if (hasT) {
                int cnt = 0;
                for (int v : comp) {
                    ll val = (ll)sgn[v] * tFixed + off[v];
                    if (L[v] <= val && val <= R[v]) cnt++;
                }
                totalBest += cnt;
            } else {
                vector<pair<ll,int>> events;
                for (int v : comp) {
                    ll a, b;
                    if (sgn[v] == +1) {
                        a = L[v] - off[v];
                        b = R[v] - off[v];
                    } else {
                        a = off[v] - R[v];
                        b = off[v] - L[v];
                    }
                    // interval [a,b] contributes +1 at a, and -1 at (b+1)
                    events.push_back({a, +1});
                    events.push_back({b + 1, -1});
                }

                sort(events.begin(), events.end());

                int cur = 0, best = 0;
                for (int i = 0; i < (int)events.size();) {
                    ll x = events[i].first;
                    int delta = 0;
                    while (i < (int)events.size() && events[i].first == x) {
                        delta += events[i].second;
                        i++;
                    }
                    cur += delta;
                    best = max(best, cur);
                }

                totalBest += best;
            }
        }

        if (!ok) cout << -1 << "\n";
        else cout << totalBest << "\n";
    }

    return 0;
}
