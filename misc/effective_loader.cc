#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int max_len = 0;
    int l,r;

    for (int i = 0; i < n; ++i) {
        l = i; r = i;
        while(l >= 0 && r < n && arr[l] == arr[r]){
            max_len = max(max_len, r - l + 1);
            l--;
            r++;
        }

        l = i; r = i + 1;
        while(l >= 0 && r < n && arr[l] == arr[r]){
            max_len = max(max_len, r - l + 1);
            l--;
            r++;
        }
    }

    cout << (max_len == 1 ? 0 : max_len)  << endl;

    return 0;
}