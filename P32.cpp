#include <bits/stdc++.h>
using namespace std;

int T;

void solve(){
    
}

int main() {

    
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<int> L(N), R(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        for (int i = 0; i < N; i++) cin >> R[i];

        
        vector<char> hasEdge(max(0, N - 1), 0);
        vector<int> edgeZ(max(0, N - 1), 0);

        
        vector<char> hasSelf(N, 0);
        vector<int> selfVal(N, 0);

        bool ok = true;

        for (int j = 0; j < M; j++) {
            int x, y;
            int z;
            cin >> x >> y >> z;
            --x; --y;

            if (abs(x - y) > 1) {
                ok = false; 
                continue;
            }

            if (x == y) {
                if (z % 2 != 0) {
                    ok = false;
                    continue;
                }
                int val = z / 2;
                if (!hasSelf[x]) {
                    hasSelf[x] = 1;
                    selfVal[x] = val;
                } else if (selfVal[x] != val) {
                    ok = false;
                }
            } else {
                int i = min(x, y); 
                if (!hasEdge[i]) {
                    hasEdge[i] = 1;
                    edgeZ[i] = z;
                } else if (edgeZ[i] != z) {
                    ok = false;
                }
            }
        }

        if (!ok) {
            cout << -1 << "\n";
            continue;
        }

        long long answer = 0;

        int i = 0;
        while (i < N && ok) {
            int start = i;
            int end = i;

          
            while (end < N - 1 && hasEdge[end]) end++;

            int len = end - start + 1;

        
            vector<int> s(len);
            vector<int> c(len);

            s[0] = +1;
            c[0] = 0;

            for (int k = 0; k < len - 1; k++) {
                int z = edgeZ[start + k];   
                s[k + 1] = -s[k];
                c[k + 1] = z - c[k];
            }

      
            bool hasT = false;
            int tFixed = 0;

            for (int k = 0; k < len; k++) {
                int idx = start + k;
                if (!hasSelf[idx]) continue;

            
                int cand = (selfVal[idx] - c[k]) * (int)s[k]; 
                if (!hasT) {
                    hasT = true;
                    tFixed = cand;
                } else if (tFixed != cand) {
                    ok = false;
                    break;
                }
            }

            if (!ok) break;

            if (hasT) {
                int cnt = 0;
                for (int k = 0; k < len; k++) {
                    int idx = start + k;
                    int val = (int)s[k] * tFixed + c[k];
                    if (L[idx] <= val && val <= R[idx]) cnt++;
                }
                answer += cnt;
            } else {
            
                vector<pair<int,int>> events;

                for (int k = 0; k < len; k++) {
                    int idx = start + k;

                    int a, b;
                    if (s[k] == +1) {
                        a = L[idx] - c[k];
                        b = R[idx] - c[k];
                    } else {
                        a = c[k] - R[idx];
                        b = c[k] - L[idx];
                    }

                    events.push_back({a, +1});
                    events.push_back({b + 1, -1}); 
                }

                sort(events.begin(), events.end());

                int cur = 0, best = 0;
                size_t p = 0;
                while (p < events.size()) {
                    int x = events[p].first;
                    int delta = 0;
                    while (p < events.size() && events[p].first == x) {
                        delta += events[p].second;
                        p++;
                    }
                    cur += delta;
                    best = max(best, cur);
                }

                answer += best;
            }

            i = end + 1;
        }

        if (!ok) cout << -1 << "\n";
        else cout << answer << "\n";
    }

    return 0;
}
