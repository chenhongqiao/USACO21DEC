#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;
int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        vector<int> s[55];
        pair<int, int> ap[55][55];
        bool ok = true;
        for (int j = 0; j < m; j++)
        {
            int kl;
            cin >> kl;
            for (int l = 0; l < kl; l++)
            {
                int in;
                cin >> in;
                s[j].push_back(in);
                if (!ap[j][in].first)
                {
                    ap[j][in].first = l + 1;
                }
                else
                {
                    ap[j][in].second = l + 1;
                }
            }
        }
        for (int j = 1; j <= n; j++)
        {
            bool oc = false;
            for (int l = 0; l < m; l++)
            {
                if (l != 0 && ap[l][j].first && !ap[l - 1][j].first && oc)
                {
                    ok = false;
                    break;
                }
                if (ap[l][j].first)
                {
                    oc = true;
                }
            }
            if (!ok)
            {
                break;
            }
        }
        if (!ok)
        {
            cout << "NO" << endl;
            continue;
        }
        int f[55] = {0};
        for (int j = 0; j < m; j++)
        {
            stack<int> st;
            for (int k = 0; k < s[j].size(); k++)
            {
                if (!st.empty() && st.top() == s[j][k])
                {
                    st.pop();
                }
                else
                {
                    int kv = s[j][k];
                    if (k == ap[j][kv].second - 1)
                    {
                        ok = false;
                        break;
                    }
                    if (f[kv] && !st.empty() && f[kv] != st.top())
                    {
                        ok = false;
                        break;
                    }
                    if (f[kv] && st.empty() && f[kv] != kv)
                    {
                        ok = false;
                        break;
                    }
                    f[kv] = st.empty() ? kv : st.top();
                    st.push(kv);
                }
            }
            if (!ok || !st.empty())
            {
                break;
            }
        }
        if (!ok)
        {
            cout << "NO" << endl;
            continue;
        }
        set<int> prv[55];
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < s[j].size(); k++)
            {
                int kv = s[j][k];
                if (k == ap[j][kv].second - 1)
                {
                    continue;
                }
                for (int l = 0; l < k; l++)
                {
                    if (l == ap[j][s[j][l]].first - 1 || s[j][l] == kv)
                    {
                        continue;
                    }
                    if (prv[s[j][l]].find(kv) != prv[s[j][l]].end())
                    {
                        ok = false;
                        break;
                    }
                    prv[kv].insert(s[j][l]);
                }
            }
            if (!ok)
            {
                break;
            }
        }
        if (!ok)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}