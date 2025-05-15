#include <iostream>
#include <vector>
#include <string>

using namespace std;

// O(N * Cn)
class Solution {
    struct node_t 
    {
        string seq;
        int open = 0;
        int closed = 0;
    };

    void generateParenthesis(int n, const node_t& node, vector<string>& result){
        if(node.open + node.closed == n << 1){
            result.push_back(node.seq);
            return;
        }

        if(node.open != n) 
            generateParenthesis(
                n, 
                node_t{
                    node.seq + '(', 
                    node.open + 1, 
                    node.closed     
                }, 
                result
            );

        if(node.closed != n && node.closed < node.open) 
            generateParenthesis(
                n, 
                node_t{
                    node.seq + ')', 
                    node.open    , 
                    node.closed + 1 
                }, 
                result
            );
    }

public:
    vector<string> generateParenthesis(int n){
        vector<string> result;
        generateParenthesis(n, node_t{"(", 1, 0}, result);
        return result;
    }
};

int main()
{
    Solution s;
    auto res = s.generateParenthesis(3);
    for(string p : res)
        cout << p << endl;

    return 0;
}
