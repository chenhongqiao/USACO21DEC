#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
vector<pair<int, int>> c;
int dp1[100005][2] = {{0}};
int dp2[100005][2] = {{0}};
int dep[100005];
int min_pair(vector<pair<int, int>> lc, int k)
{
    for (int i = 0; i < lc.size(); i++)
    {
        dp2[i][0] = 0;
        dp2[i][1] = 0;
    }

    if (lc.size() == 1)
    {
        return lc[0].second;
    }
    queue<pair<int, int>> q;
    q.push({lc[0].first, 0});
    dp2[0][1] = lc[0].second;
    for (int i = 1; i < lc.size(); i++)
    {
        dp2[i][0] = dp2[i - 1][0];
        dp2[i][1] = dp2[i - 1][1];
        q.push({lc[i].first, i});
        while (!q.empty() && lc[i].first - q.front().first > k)
        {
            q.pop();
        }
        int p = q.front().second - 1;
        if (p < 0)
        {
            if (i == lc.size() - 1 || lc[i + 1].first - lc[i - 1].first <= k || i % 2 == 0)
            {
                dp2[i][1] = max(dp2[i][1], lc[i].second);
            }
        }
        else
        {
            if (i == lc.size() - 1 || lc[i + 1].first - lc[i - 1].first <= k || i % 2 == 0)
            {
                dp2[i][1] = max(dp2[i][1], dp2[p][0] + lc[i].second);
            }
            if (i == lc.size() - 1 || lc[i + 1].first - lc[i - 1].first <= k || i % 2 == 1)
            {
                dp2[i][0] = max(dp2[i][0], dp2[p][1] + lc[i].second);
            }
        }
    }
    if (lc.size() % 2 == 1)
    {
        return dp2[lc.size() - 1][1];
    }
    else if (lc.size() % 2 == 0)
    {
        return dp2[lc.size() - 1][0];
    }
}
int main()
{
    int t, n, k;
    int tw = 0;
    cin >> t >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int l, w;
        cin >> l >> w;
        c.push_back({l, w});
        tw += w;
    }
    sort(c.begin(), c.end());
    if (t == 1)
    {
        priority_queue<pair<int, int>> q;
        q.push({c[0].second, c[0].first});
        for (int i = 1; i < n; i++)
        {
            dp1[i][0] = max(dp1[i - 1][0], dp1[i - 1][1]);
            while (!q.empty() && c[i].first - q.top().second > k)
            {
                q.pop();
            }
            if (!q.empty())
            {
                dp1[i][1] = q.top().first + c[i].second;
            }
            q.push({dp1[i][0] + c[i].second, c[i].first});
        }
        cout << tw - max(dp1[n - 1][0], dp1[n - 1][1]) << endl;
    }
    else if (t == 2)
    {
        int ans = 0;
        vector<pair<int, int>> tmp;
        for (int i = 0; i < n; i++)
        {
            tmp.push_back(c[i]);
            if (i != n - 1 && c[i + 1].first - c[i].first > k)
            {
                ans += min_pair(tmp, k);
                tmp.clear();
            }
        }
        if (tmp.size())
        {
            ans += min_pair(tmp, k);
        }
        cout << ans << endl;
    }
    return 0;
}