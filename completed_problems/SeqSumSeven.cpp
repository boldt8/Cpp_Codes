#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> first(7, -1);
    int pref = 0;
    first[0] = 0;                // prefix sum 0 at position 0

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        pref = (pref + x) % 7;

        if (first[pref] == -1) first[pref] = i;
        else ans = max(ans, i - first[pref]);
    }

    cout << ans << '\n';
    return 0;
}
