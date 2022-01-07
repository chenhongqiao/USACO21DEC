#include <iostream>
#include <vector>
#include <set>
using namespace std;
int c[200005];
int mp[200005];
vector<int> ans;
vector<pair<int, int>> h;
vector<pair<int, int>> l;
vector<int> aft[200005];
set<int> s;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
        mp[c[i]] = i;
    }
    for (int i = 0; i < n; i++)
    {
        s.insert(c[i]);
        if (l.empty() || c[i] > l.back().second)
        {
            l.push_back({i, c[i]});
        }
        else
        {
            int p = *s.upper_bound(c[i]);
            aft[p].push_back(i);
        }
    }
    for (int i = n; i >= 0; i--)
    {
        ans.push_back(h.size());
        int p = mp[i];
        l.pop_back();
        if (!h.empty() && (h.back().first > l.back().first || l.empty()))
        {
            h.pop_back();
        }
        for (int j : aft[i])
        {
            l.push_back({j, c[j]});
        }
        if (!aft[i].empty())
        {
            h.push_back({p, i});
        }
    }
    while (!ans.empty())
    {
        cout << ans.back() << endl;
        ans.pop_back();
    }
    return 0;
}