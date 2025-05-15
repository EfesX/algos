#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_set>

using namespace std;

int main(){
    unordered_set<string> words;
    copy(
        istream_iterator<string>(cin), 
        istream_iterator<string>(), 
        inserter(words, words.end())
    );
    cout << words.size() << endl;
    return 0;
}
