#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;


int main(){

    vector<int> keys;
    unordered_map<int,int> um;

    int n; cin >> n;
    keys.resize(n);

    copy_n(istream_iterator<int>(cin), n, begin(keys));

    cin >> n;
    for(int i = 0; i < n; i++){
        int val; cin >> val;
        um[val - 1]++;
    }

    for(size_t i = 0; i < keys.size(); i++)
        if(um[i] <= keys[i]) cout << "NO" << endl;
        else cout << "YES" << endl;

    return 0;
}