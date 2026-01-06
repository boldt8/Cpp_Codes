#include <bits/stdc++.h>
#define DEBUG false
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
using namespace std;

vector<int> nums;
vector<int> preL, preR;
int T, N;

void solve() {
    long long ans = LLONG_MIN;

    for (int m = 1; m <= N - 2; ++m) {
        ans = max(ans, preL[m - 1] + nums[m] + preR[m + 1]);
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    if (DEBUG) {
        (void)freopen("test.in", "r", stdin);
        (void)freopen("test.out", "w", stdout);
    }
#endif

    cin >> T;
    while (T--) {
        cin >> N;
        nums.assign(N, 0);
        preL.assign(N, 0);
        preR.assign(N, 0);

        for (int i = 0; i < N; ++i) cin >> nums[i];

        // preL[i] = max_{0..i} (nums[x] + x)
        preL[0] = nums[0] + 0;
        for (int i = 1; i < N; ++i) {
            preL[i] = max(preL[i - 1], nums[i] + i);
        }

        // preR[i] = max_{i..N-1} (nums[x] - x)
        preR[N - 1] = nums[N - 1] - (N - 1);
        for (int i = N - 2; i >= 0; --i) {
            preR[i] = max(preR[i + 1], nums[i] - i);
        }

        solve();
    }
    return 0;
}
