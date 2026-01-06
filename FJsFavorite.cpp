#include <bits/stdc++.h>
#define DEBUG true
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;

vector<int> nums;
vector<int> modded;
vector<int> disted;
int T, n, m;

int get_sign(int number) {
    if (number > 0) {
        return 1;
    } else if (number < 0) {
        return -1;
    } else {
        return 0;
    }
}

void getDist(vector<int>& dist){
    for(int i = 0; i < n; ++i){
        if (abs(m - modded[i]) < abs(modded[i])){
            dist[i] = m - modded[i];
        }
        else{
            dist[i] = -modded[i];
        }
    }
}

void solve(){
    for(int i = 0; i < n; ++i){
        modded[i] = nums[i] % m;
    }
    getDist(disted);
    for(int i = 0; i< n; ++i){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i< n; ++i){
        cout<<modded[i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i< n; ++i){
        cout<<disted[i]<<" ";
    }
    cout<<endl;
    

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
        cin>>n>>m;
        nums.assign(n,0);
        modded.assign(n,0);
        disted.assign(n,0);
        for(int i =0; i< n; ++i) cin>>nums[i];
        solve();
    }
}