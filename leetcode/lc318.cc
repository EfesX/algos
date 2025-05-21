#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        unordered_map<string_view, int> um;
        size_t ans = 0;

        for(string& s : words){
            int bs = 0;

            for(char sym : s)
                bs |= (1 << (sym - 'a'));
            
            for(auto [k,v] : um){
                if((bs & v) == 0)
                    ans = max(ans, s.size() * k.size());
            }

            um[s] = bs;
        }

        return static_cast<int>(ans);
    }
};

int main(){
    return 0;
}