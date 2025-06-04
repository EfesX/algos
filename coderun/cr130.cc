#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <climits>
#include <vector>

using namespace std;

int main()
{
    string text;
    copy(istream_iterator<char>(cin), istream_iterator<char>(), back_inserter(text));

    int maxval = INT_MIN;

    map<char,int> um;
    for(size_t i = 0; i < text.size(); i++){
        um[text[i]]++;
        maxval = max(um[text[i]], maxval);
    }

    vector<vector<char>> hist(maxval + 1, vector<char>(um.size(), ' '));

    size_t i = 0;
    for(auto [k,_] : um){
        hist[hist.size() - 1][i] = k;
        i++;
    }

    const vector<char>& keys = hist[hist.size() - 1];

    for(i = 0; i < keys.size(); i++){
        int val = um[keys[i]];
        
        while(val > 0){
            hist[hist.size() - val - 1][i] = '#';
            val--;
        }
    }

    for(const auto& vec : hist){
        for(char ch : vec) cout << ch;
        cout << endl;
    }

    return 0;
}