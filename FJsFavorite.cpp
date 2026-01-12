#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        ll M;
        cin >> N >> M;
        vector<ll> d(N);
        for (int i = 0; i < N; i++) {
            ll a;
            cin >> a;
            d[i] = (M == 1 ? 0 : a % M);
        }

        if (M == 1) {
            cout << 0 << "\n";
            continue;
        }

        sort(d.begin(), d.end());
        ll half = M / 2; // floor(M/2)

        // Build doubled array p2: [d..., d+M...]
        vector<ll> p2(2 * N);
        for (int i = 0; i < N; i++) {
            p2[i] = d[i];
            p2[i + N] = d[i] + M;
        }

        // Prefix sums of p2
        vector<ll> pref(2 * N + 1, 0);
        for (int i = 0; i < 2 * N; i++) pref[i + 1] = pref[i] + p2[i];

        auto eval_r = [&](ll r) -> ll {
            // r is in [0, M)
            // Find first point >= r (can be in first N or at index N if r > max(d))
            int idx = (int)(lower_bound(p2.begin(), p2.end(), r) - p2.begin());
            // idx will be in [0, N] because r < M and p2[N] = d[0]+M >= M > r.

            // In [idx, idx+N) are the N points in [r, r+M)
            ll limit = r + half;
            int t = (int)(upper_bound(p2.begin() + idx, p2.begin() + idx + N, limit) - p2.begin());
            int k = t - idx; // direct-count in [r, r+half]

            ll sum_direct_points = pref[t] - pref[idx];
            ll sum_wrap_points   = pref[idx + N] - pref[t];

            ll direct_cost = sum_direct_points - (ll)k * r;
            ll wrap_cost   = (ll)(N - k) * (r + M) - sum_wrap_points;

            return direct_cost + wrap_cost;
        };

        // Candidate r values
        vector<ll> cand;
        cand.reserve(3 * N);
        for (int i = 0; i < N; i++) {
            ll x = d[i];
            cand.push_back(x);
            cand.push_back((x + 1) % M);
            ll y = x - half;
            y %= M;
            if (y < 0) y += M;
            cand.push_back(y);
        }
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());

        ll ans = (1LL << 62);
        for (ll r : cand) {
            ans = min(ans, eval_r(r));
        }

        cout << ans << "\n";
    }
    return 0;
}
