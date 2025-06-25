#include <bits/stdc++.h>
using namespace std;

// Radix sort for vector<pair<char, int>>
void radixSort(vector<pair<char, int>>& a) {
    int n = a.size();
    vector<int> count(256, 0); // ASCII range

    for (auto& x : a)
        count[x.first]++;

    vector<int> pos(256, 0);
    for (int i = 1; i < 256; i++)
        pos[i] = pos[i - 1] + count[i - 1];

    vector<pair<char, int>> sorted(n);
    for (auto& x : a)
        sorted[pos[x.first]++] = x;

    a = sorted;
}

// Radix sort for vector<pair<pair<int, int>, int>>
void radixSort(vector<pair<pair<int, int>, int>>& a) {
    int n = a.size();

    // Sort by second element (less significant)
    {
        vector<int> count(n, 0);
        for (auto& x : a)
            count[x.first.second]++;

        vector<int> pos(n, 0);
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + count[i - 1];

        vector<pair<pair<int, int>, int>> sorted(n);
        for (auto& x : a)
            sorted[pos[x.first.second]++] = x;

        a = sorted;
    }

    // Sort by first element (more significant)
    {
        vector<int> count(n, 0);
        for (auto& x : a)
            count[x.first.first]++;

        vector<int> pos(n, 0);
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + count[i - 1];

        vector<pair<pair<int, int>, int>> sorted(n);
        for (auto& x : a)
            sorted[pos[x.first.first]++] = x;

        a = sorted;
    }
}

int main() {
    string s;
    cin >> s;
    s += '$';
    int n = s.length();

    vector<int> p(n), c(n);
    vector<pair<char, int>> a(n);

    for (int i = 0; i < n; i++)
        a[i] = {s[i], i};

    radixSort(a);

    for (int i = 0; i < n; i++)
        p[i] = a[i].second;

    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].first == a[i - 1].first)
            c[p[i]] = c[p[i - 1]];
        else
            c[p[i]] = c[p[i - 1]] + 1;
    }

    int k = 0;
    while ((1 << k) < n) {
        vector<pair<pair<int, int>, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {
                {c[i], c[(i + (1 << k)) % n]},
                i
            };
        }

        radixSort(a);

        for (int i = 0; i < n; i++)
            p[i] = a[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }
        k++;
    }

    // Output the suffix array
    for (int i = 0; i < n; i++)
        cout << p[i] << " " << s.substr(p[i], n - p[i]) << endl;

    return 0;
}
