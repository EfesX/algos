#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


int main(){
    int n; cin >> n;

    vector<int> vec;

    while(n--)
    {
        int m; cin >> m;
        vec.resize(m);
        
        copy_n(istream_iterator<int>(cin), m, begin(vec));

        int ans = INT_MAX;
        sort(begin(vec), end(vec), [&](int a, int b){
            ans = min(ans, a ^ b);
            return a < b;
        });
        
        cout << ans << endl;
    }

    return 0;
}