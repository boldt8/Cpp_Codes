#include <bits/stdc++.h>
#define DEBUG false
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;


struct DSU {
    vector<int> v;

    DSU(int n) {
        v = vector<int>(n,-1);
    }

    int get(int x) {
        return v[x] < 0 ? x : v[x] = get(v[x]);
    }

    bool same_set(int a, int b) {
        return get(a) == get(b);
    }

    int size(int x) {
        return -v[get(x)];
    }

    bool unite (int x, int y){
        x = get(x), y = get(y);
        if (x == y) return false;
        if (v[x] > v[y]) swap(x,y);
        v[x] += v[y];
        v[y] = x;
        return true;
    }

};

signed main() {
    if(!DEBUG){
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    }
    else{
        (void)freopen("test.in", "r", stdin);
        (void)freopen("test.out", "w", stdout); 
    }
}

