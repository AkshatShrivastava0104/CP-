#include <bits/stdc++.h>

using namespace std;

int getMax(vector < int > & nums) {
    auto it = * max_element(nums.begin(), nums.end());
    return it;
}

void countingSort(vector < int > & nums, int exp) {
    int n = nums.size();

    vector < int > count(10, 0);

    vector < int > output(n);

    for (int i = 0; i < n; i++) {
        count[(nums[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {

        int digit = (nums[i] / exp) % 10;
        output[count[digit] - 1] = nums[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        nums[i] = output[i];
    }

}


void radixSort(vector < int > & nums) {
    int mx = getMax(nums);
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingSort(nums, exp);
    }
}


int main() {
    // your code goes here

    int n;
    cin>>n;
    vector < int > nums(n);

    for (int i = 0; i < nums.size(); i++) {
        cin >> nums[i];
    }

    radixSort(nums);

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
}


