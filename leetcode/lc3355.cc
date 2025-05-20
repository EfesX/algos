#include <iostream>
#include <vector>

using namespace std;

struct segtree_t 
{
    int sz_origin;
    vector<int> tree;

    inline void build(int v, int tl, int tr, const vector<int>& arr)
    {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }
        
        const int tm = (tl + tr) >> 1;
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx | 1;

        build(l_ch_idx,     tl, tm, arr);
        build(r_ch_idx, tm + 1, tr, arr);
    }

    inline int get(int v, int tl, int tr, int pos) const 
    {
        if(tl == tr) return tree[v];

        const int tm = (tl + tr) >> 1;
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx + 1;

        if(pos <= tm)
            return tree[v] + this->get(l_ch_idx, tl, tm, pos);

        return tree[v] + this->get(r_ch_idx, tm + 1, tr, pos);
    }
    
    inline void add_range(int v, int tl, int tr, int l, int r, int value){
        if(l > tr || r < tl) return;

        if(l == tl && r == tr)
        {
            tree[v] += value;
            return;
        }
        
        const int tm = (tl + tr) >> 1;
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx + 1;

        add_range(l_ch_idx,     tl, tm, l, min(r, tm), value);
        add_range(r_ch_idx, tm + 1, tr, max(l,tm+1), r, value);
    }

    segtree_t(const vector<int>& arr) : 
        sz_origin(arr.size()),
        tree(arr.size() * 4)
    {
        build(1, 0, sz_origin - 1, arr);
    }

    int get(int pos) const {
        return this->get(1, 0, sz_origin - 1, pos);
    }

    void add_range(int l, int r, int value){
        add_range(1, 0, sz_origin - 1, l, r, value);
    }
};

class Solution{
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries){
        segtree_t st(nums);

        for(auto& q : queries)
            st.add_range(q[0], q[1], -1);

        for(size_t i = 0; i < nums.size(); i++)
            if(st.get(i) > 0)
                return false;

        return true;
    }
};

int main(){
    {
        vector<int> nums = {1, 0, 1};
        vector<vector<int>> queries = {
            {0,2}
        };
        Solution s;
        cout << boolalpha << s.isZeroArray(nums, queries) << endl;
    }
    {
        vector<int> nums = {4, 3, 2, 1};
        vector<vector<int>> queries = {
            {1,2,3},
            {0,1,2}
        };
        Solution s;
        cout << boolalpha << s.isZeroArray(nums, queries) << endl;
    }

    return 0;
}
