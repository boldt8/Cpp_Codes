#include <bits/stdc++.h>
#define DEBUG true
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;


struct DSU {
    vector<int> v;
    int numisl;

    DSU(int n) {
        v = vector<int>(n,-1);
        numisl = n;
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
        numisl--;
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

    int n, m;
    cin>>n>>m;
    DSU thing = DSU(n);
    int maxsize = 1;
    

    for(int i = 0; i < m; i++){
        int a, b;  
        cin>>a>>b;
        a--,b--;
        if(thing.unite(a,b)==false){
            cout<<thing.numisl<<" "<<maxsize<<endl;
        }
        else{
            maxsize= max(maxsize, thing.size(a));
            cout<<thing.numisl<<" "<<maxsize<<endl;
        }

    }
}

