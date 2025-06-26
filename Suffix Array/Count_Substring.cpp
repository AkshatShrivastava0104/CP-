#include <bits/stdc++.h>
using namespace std;

int lower_bound_suffix(const string &s, const vector<int> &p, const string &q) {
    int l = 0, r = p.size();
    while (l < r) {
        int m = (l + r) / 2;
        string sub = s.substr(p[m], min(q.size(), s.size() - p[m]));
        if (sub < q) l = m + 1;
        else r = m;
    }
    return l;
}

int upper_bound_suffix(const string &s, const vector<int> &p, const string &q) {
    int l = 0, r = p.size();
    while (l < r) {
        int m = (l + r) / 2;
        string sub = s.substr(p[m], min(q.size(), s.size() - p[m]));
        if (sub <= q) l = m + 1;
        else r = m;
    }
    return l;
}

int main() {
    string s;
    cin >> s;
    s += '$';
    int n = s.size();

    // Build suffix array
    vector<int> p(n), c(n);
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;

        int k = 0;
        while ((1 << k) < n) {
            vector<pair<pair<int, int>, int>> a(n);
            for (int i = 0; i < n; i++)
                a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
            sort(a.begin(), a.end());
            for (int i = 0; i < n; i++) p[i] = a[i].second;
            c[p[0]] = 0;
            for (int i = 1; i < n; i++)
                c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
            k++;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        string q;
        cin >> q;

        int lb = lower_bound_suffix(s, p, q);
        int ub = upper_bound_suffix(s, p, q);

        int count = ub - lb;
        cout << count << '\n';
    }

    return 0;
}
