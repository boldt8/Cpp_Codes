#include <bits/stdc++.h>
#define DEBUG true
#define int int
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;
int T;

struct Edge {
    int to;
    int z;
};

void solve(){
    int N, M;
        cin>>N>>M;

        vector<int> L(N), R(N);
        for (int i = 0; i < N; i++) {
            cin>>L[i];
        }
        for (int i = 0; i < N; i++) {
            cin>>R[i];
        }
        vector<vector<Edge>> adj(N);
        for (int i = 0; i < M; i++) {
            int x, y;
            int z;
            cin>>x>>y>>z;
            --x; --y;
            adj[x].push_back({y, z});
            adj[y].push_back({x, z});
        }

        vector<char> vis(N, 0);
        vector<int> sgn(N, 0);   
        vector<int> off(N, 0);    

        bool ok = true;
        int totalBest = 0;

        auto process_component = [&](int start) -> int {
            queue<int> q;
            vector<int> comp;

            bool hasT = false;
            int tFixed = 0;

            vis[start] = 1;
            sgn[start] = +1;
            off[start] = 0;
            q.push(start);

            while (!q.empty() && ok) {
                int u = q.front();
                q.pop();
                comp.push_back(u);

                for (const auto& e : adj[u]) {
                    int v = e.to;
                    int z = e.z;

                    if (!vis[v]) {
                        vis[v] = 1;
                        sgn[v] = -sgn[u];
                        off[v] = z - off[u];
                        q.push(v);
                    } else {
                      
                        int sumS = sgn[u] + sgn[v]; 
                        int sumC = off[u] + off[v];

                        if (sumS == 0) {
                           
                            if (sumC != z) {
                                ok = false;
                                break;
                            }
                        } else {
                            int num = z - sumC;
                            if (num % sumS != 0) {
                                ok = false;
                                break;
                            }
                            int cand = num / sumS;
                            if (!hasT) {
                                hasT = true;
                                tFixed = cand;
                            } else if (tFixed != cand) {
                                ok = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (!ok) return 0;

            if (hasT) {
                int cnt = 0;
                for (int v : comp) {
                    int val = (int)sgn[v] * tFixed + off[v];
                    if (L[v] <= val && val <= R[v]) cnt++;
                }
                return cnt;
            } else {
                vector<pair<int,int>> events;
                for (int v : comp) {
                    int a, b;
                    if (sgn[v] == +1) {
                        a = L[v] - off[v];
                        b = R[v] - off[v];
                    } else {
                        a = off[v] - R[v];
                        b = off[v] - L[v];
                    }
                    events.push_back({a, +1});
                    events.push_back({b + 1, -1});
                }

                sort(events.begin(), events.end());

                int cur = 0, best = 0;
                size_t i = 0;
                while (i < events.size()) {
                    int x = events[i].first;
                    int delta = 0;
                    while (i < events.size() && events[i].first == x) {
                        delta += events[i].second;
                        i++;
                    }
                    cur += delta;
                    best = max(best, cur);
                }
                return best;
            }
        };

        for (int i = 0; i < N && ok; i++) {
            if (!vis[i]) totalBest += process_component(i);
        }

        if (!ok) cout<<-1<<"\n";
        else cout<<totalBest<<"\n";
}


signed main() {
    if(!DEBUG){
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    }
    else{
        (void)freopen("test.in", "r", stdin);
        (void)freopen("test.out", "w", stdout); 
    }
    cin>>T;
    while(T--){
        solve();
    }
}