#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;

    set<int> sq1, sq2;

    copy_n(istream_iterator<int>(cin), n, inserter(sq1, sq1.begin()));

    vector<int> both;

    for(int i = 0; i < m; i++)
    {
        int val; cin >> val;

        if(sq1.count(val)) both.push_back(val);
        else sq2.insert(val);
    }

    sort(begin(both), end(both));

    cout << both.size() << endl;
    for(int val : both)
    {
        sq1.erase(val);
        cout << val << " ";
    }
    cout << endl;
    
    cout << sq1.size() << endl;
    copy(begin(sq1), end(sq1), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << sq2.size() << endl;
    copy(begin(sq2), end(sq2), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}