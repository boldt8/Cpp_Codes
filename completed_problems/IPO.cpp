#include <bits/stdc++.h>
#define DEBUG true
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;

int n,w,k;
vector<pair<int,int>> nums;
priority_queue<pair<int,int>> que;
int capital = 0;
int jobs = 0;


void solve(){
    sort(nums.begin(),nums.end());
    for(int i = 0; i < n; ++i){
        while(que.size()){
            if(que.top().first > capital){
                que.pop();
                break;
            }
            else{
                jobs++;
                capital += que.top().second;
                que.pop();
                break;
            }
        }
        
    }
    cout<<jobs;


}


signed main() {
    if(!DEBUG){
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    }
    else{
        (void)freopen("test.in", "r", stdin);
        (void)freopen("test.out", "w", stdout); 
    }
    cin>>n>>w>>k;
    nums.assign(n,pair<int,int>());
    for(int i = 0; i < n; ++i){
        cin>>nums[i].first;
        
    }
    for(int i = 0; i < n; ++i){
        cin>>nums[i].second;
        
    }
    for(int i = 0; i < n; ++i){
        que.push({nums[i].first,nums[i].second});
    }
    solve();

}