#include <iostream>
#include <unordered_map>
#include <iterator>

using namespace std;


int main(){
    int n; cin >> n;
    int ans = 0;

    unordered_map<int,int> um;
    
    for(int i = 0; i < n; ++i)
    {
        int val; cin >> val;
        um[val]++;
    }

    for(auto [k,v] : um)
        if(v == 1)
            ans++;

    cout << ans << endl;

    return 0;
}