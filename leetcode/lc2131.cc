#include <array>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int longestPalindrome(vector<string>& words) 
    {
        array<array<int, 26>, 26> freq = {};
        int ans = 0;
        
        for (const auto& word : words) 
        {
            int a = word[0] - 'a';
            int b = word[1] - 'a';
            
            if (freq[b][a] > 0) 
            {
                ans += 4;
                freq[b][a]--;
            } 
            else 
            {
                freq[a][b]++;
            }
        }
        
        for (int i = 0; i < 26; ++i) 
        {
            if (freq[i][i] > 0) 
            {
                ans += 2;
                break;
            }
        }
        
        return ans;
    }
};

int main(){
    return 0;
}