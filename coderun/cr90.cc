#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <climits>

using namespace std;

int main(){
    int n,m;
    vector<int> v1;
    vector<int> v2;

    cin >> n;
    copy_n(istream_iterator<int>(cin), n, back_inserter(v1));

    cin >> m;
    copy_n(istream_iterator<int>(cin), m, back_inserter(v2));

    size_t p1 = 0;
    size_t p2 = 0;

    int minval = INT_MAX;

    pair<int,int> ans;

    while(p1 < v1.size() && p2 < v2.size())
    {
        const int& num1 = v1[p1];
        const int& num2 = v2[p2];

        if(num1 == num2){
            ans = {num1, num2};
            break;
        }

        if(abs(num1 - num2) < minval){
            minval = abs(num1 - num2);
            ans = {num1, num2};
        }

        if(num2 < num1)
            p2++;
        else p1++;   
    }

    cout << ans.first << " " << ans.second << endl;

    return 0;
}