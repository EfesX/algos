#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    TreeNode* build(const vector<int>& nums, int l, int r){
        if(l >= r)
            return nullptr;

        int m = (l + r) / 2;

        TreeNode* left = build(nums, l, m);
        TreeNode* right = build(nums, m + 1, r);

        return new TreeNode(nums[m], left, right);
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size());
    }
};

int main(){
    return 0;
}