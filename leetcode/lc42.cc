#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int trap(const vector<int>& height)
    {
        int sz = height.size();

        vector<int> left(sz, 0);
        vector<int> right(sz, 0);

        int l_max = 0;
        int r_max = 0;
        int result = 0;

        for(int i = 0; i < sz; i++)
        {
            left[i]  = l_max;
            l_max = max(l_max, height[i]);

            right[sz - i - 1]  = r_max;
            r_max = max(r_max, height[sz - i - 1]);
        }

        for(int i = 0; i < sz; i++)
        {
            if((height[i] >= left[i]))
                continue;

            if((height[i] >= right[i]))
                continue;

            result += min(left[i], right[i]);
            result -= height[i];
        }
            
        return result;
    }
};

int main()
{
    Solution s;
    cout << s.trap({2, 0, 4, 0, 1}) << endl;
    cout << s.trap({0}) << endl;
    cout << s.trap({1}) << endl;
    cout << s.trap({0, 0, 0}) << endl;
    cout << s.trap({1, 1}) << endl;
    cout << s.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    return 0;
}
