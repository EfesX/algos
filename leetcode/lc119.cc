#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans;
        ans.push_back(1);

        for(int j = 1; j <= rowIndex; j++){
            int prev = ans[0];
            for(size_t i = 1; i < ans.size(); i++){
                int t = ans[i];
                ans[i] = prev + ans[i];
                prev = t;
            }
            ans.push_back(1);
        }
        
        return ans;
    }
};

int main(){
    return 0;
}