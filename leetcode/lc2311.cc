#include <bitset>
#include <string>

using namespace std;

class Solution {
public:
    int longestSubsequence(string s, int k) {
        bitset<32> bs(0);

        int idx = 0;
        int i = 0;

        for(i = 0; i < s.size() && idx < 32; i++){
            bs[idx] = s[s.size() - 1 - i] == '1';

            if(bs.to_ullong() > k)
                break;
            
            idx++;
        }

        for(; i < s.size(); i++)
            idx += s[s.size() - 1 - i] == '0';

        return idx;
    }
};

int main(){
    return 0;
}