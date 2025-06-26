#include <bits/stdc++.h>
using namespace std;

bool binary_search_suffix_array(const string &s, const vector<int> &p, const string &key) {
    int n = p.size();
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int pos = p[mid];

        int len = min((int)key.length(), (int)(s.length() - pos));
        string cmp = s.substr(pos, len);

        if (cmp == key) return true;
        if (cmp < key) left = mid + 1;
        else right = mid - 1;
    }

    return false;
}

int main() {
    string s;
    cin >> s;
    s += '$';
    int n = s.length();

    vector<int> p(n), c(n);
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
    }

    int k = 0;
    while ((1 << k) < n) {
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = (a[i].first == a[i - 1].first) ? c[p[i - 1]] : c[p[i - 1]] + 1;
        }
        k++;
    }

    // Optional: print suffix array
    // for (int i = 0; i < n; i++) {
    //     cout << p[i] << " " << s.substr(p[i], n - p[i]) << endl;
    // }

    int t;
    cin >> t;
    while (t--) {
        string d;
        cin >> d;
        bool res = binary_search_suffix_array(s, p, d);
        cout << (res ? "YES" : "NO") << endl;
    }

    return 0;
}
