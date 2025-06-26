#include <iostream>
#include <string>

using namespace std;

int compress(string& s)
{
    size_t l = 0;
    size_t r = 0;

    char last = s[0];
    int cnt = 0;

    while(r < s.size())
    {
        while(r < s.size() && s[r] == last)
        {
            r++;
            cnt++;
        }

        if(cnt == 1)
        {
            s[l++] = last;
        }
        else if(cnt == 2)
        {
            s[l++] = last;
            s[l++] = last;
        }
        else
        {
            s[l++] = last;
            string num = to_string(cnt);
            for(auto ch : num)
                s[l++] = ch;
        }

        cnt = 0;

        if(r >= s.size())
            break;

        last = s[r];
    }

    return l;
}

int main()
{
    string str; cin >> str;
    int r = compress(str);
    cout << string(&str[0], r) << endl;
}