#include <bits/stdc++.h>
#define DEBUG false
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;

int T;


static int val_in_B(int k, int p) {
    while (true) {
        if (k == 0) return 0;                 
        if (k == 1) {                         
            return (p == 0 ? 1 : 0);
        }

        if (p == k - 1){
            return k;
        }              
        if (p == k - 2) {                    
            k -= 1;
            p = 0;
            continue;
        }
        if (p == k) {                         
            k -= 1;
            p = 1;
            continue;
        }

        int r = (k - p - 3) / 3;
        if (r > 0) {
            k -= r;
            p += 2 * r;
        } else {
            k -= 1;
            p += 2;
        }
    }
}

static int pos_in_B(int K, int v) {
    if (K == 0) return 0; 

    int k, p;
    if (v == 0) { 
        k = 1; p = 1; 
    }
    else if (v == 1) { 
        k = 1; p = 0; 
    }
    else { 
        k = v; p = v - 1; 
    } 

    while (k < K) {
        if (p >= 2) {
            int steps = min(p / 2, K - k);
            p -= 2 * steps;
            k += steps;
            if (k == K) break;
        }
        
        if (p == 0) {
            k += 1;
            p = k - 2;
        } else { 
            k += 1;
            p = k;
        }
    }
    return p;
}

void solve(){
        int type;
        int a, t;
        cin >> type >> a >> t;

        int K = t / 2;
        int m = K + 1;

        if (type == 2) {
            int x = a;
            if (x >= m) {
                cout<<x<<"\n";
            } else {
                if (t % 2 == 0) {
                    cout<<val_in_B(K, x)<<"\n";
                } else {
                    int idx = (x + 1) % m;
                    cout<<val_in_B(K, idx)<<"\n";
                }
            }
        } else {
            int c = a;
            if (c >= m) {
                cout<<c<<"\n";
            } else {
                int p = pos_in_B(K, c);
                if (t % 2 == 0) {
                    cout<<p<<"\n";
                } else {
                    int ans = (p - 1) % m;
                    if (ans < 0) ans += m;
                    cout<<ans<<"\n";
                }
            }
        }
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