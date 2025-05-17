#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int MAX_PRICE = 200;
    vector<int> prefix(MAX_PRICE + 2, 0);

    long long total = 0;

    for (int i = 0; i < n; ++i) 
    {
        int price;
        cin >> price;

        total += prefix[price];
        for (int i = price + 1; i <= MAX_PRICE + 1; ++i)
            prefix[i]++;
    }

    cout << total << endl;

    return 0;
}