#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    size_t n,k;
    cin >> n >> k;

    vector<int> vec(n);
    copy_n(istream_iterator<int>(cin), n, begin(vec));

    size_t l = 0;
    size_t r = 0;

    unordered_map<int,int> um;

    pair<size_t,size_t> ans = {0, 0xffffffff};


    while(r < vec.size())
    {
        um[vec[r]]++;

        while(l < r && um.size() == k)
        {
            ans.first  = l;
            ans.second = r;
            
            um[vec[l]]--;

            if(um[vec[l]] == 0)
                um.erase(vec[l]);

            l++;
        }

        r++;
    }

    cout << ++ans.first << " " << ++ans.second << endl;

    return 0;
}