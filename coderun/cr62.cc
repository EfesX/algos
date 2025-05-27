#include <iostream>
#include <unordered_set>
#include <iterator>

using namespace std;


int main(){

    unordered_set<int> us;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), inserter(us, us.begin()));
    cout << us.size() << endl;

    return 0;
}