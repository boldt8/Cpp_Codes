#include <bits/stdc++.h>
#define DEBUG true
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;

int n, x;
vector<pair<int,int>> nums;

void solve(){
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        int p3 = i;
        int p1=i+1, p2=n-1;
        while(p1 < p2){
            int sum = nums[p1].first + nums[p2].first + nums[p3].first;
            if(sum == x){
                cout<<(nums[p1].second +1)<<" "<<(nums[p2].second + 1)<<" "<<(nums[p3].second + 1);
                return;
            }
            if(sum < x)p1++;
            if(sum > x)p2--;
        }
    }
    
    cout<<"IMPOSSIBLE";
    return;
}


signed main() {
    if(!DEBUG){
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    }
    else{
        (void)freopen("test.in", "r", stdin);
        (void)freopen("test.out", "w", stdout); 
    }
    cin>>n>>x;
    nums.assign(n,pair<int,int>());
    for(int i = 0; i < n; ++i){
        cin>>nums[i].first;
        nums[i].second = i;
    }
    solve();

}