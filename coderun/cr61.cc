#include <iostream>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    
    string line;
    unordered_set<int> v1;
    set<int> ans;

    {
        getline(cin, line);
        istringstream iss(line);
        copy(istream_iterator<int>(iss), istream_iterator<int>(), inserter(v1, v1.begin()));
    }
    {
        getline(cin, line);
        istringstream iss(line);

        for(auto it = istream_iterator<int>(iss); it != istream_iterator<int>(); it++){
            if(v1.count(*it)) ans.insert(*it);
        }
    }
    
    copy(begin(ans), end(ans), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}