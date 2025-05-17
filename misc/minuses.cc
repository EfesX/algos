#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    stack<int64_t> nums;
    stack<int> signs;
    
    int64_t curr_num = 0;
    int sign = 1;
    int64_t result = 0;
    bool reading_num = false;

    for(size_t i = 0; i < s.size(); i++) 
    {
        if(s[i] == ' ') continue;

        if(isdigit(s[i])) 
        {
            curr_num = curr_num * 10 + (s[i] - '0');
            reading_num = true;
            continue;
        }

        if(reading_num) 
        {
            result += sign * curr_num;
            curr_num = 0;
            reading_num = false;
            sign = 1;
        }

        if(s[i] == '+' || s[i] == '-') 
        {
            sign *= (s[i] == '+' ? 1 : -1);
            continue;
        }
        
        if(s[i] == '(') 
        {
            nums.push(result);
            signs.push(sign);
            result = 0;
            sign = 1;
            continue;
        }
        
        if(s[i] == ')') 
        {
            int64_t temp = result;
            result = nums.top() + signs.top() * temp;
            nums.pop();
            signs.pop();
            continue;
        }
    }

    if(reading_num)
        result += sign * curr_num;

    cout << result << endl;

    return 0;
}