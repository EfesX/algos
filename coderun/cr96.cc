#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    size_t n,k;
    cin >> n >> k;

    unordered_map<char,size_t> um;
    string text; cin >> text;

    size_t len = 0;
    size_t first = 0;


    for(size_t i = 0, j = 0; i < text.size(); i++)
    {
        um[text[i]]++;

        while(um[text[i]] > k)
        {
            um[text[j]]--;
            if(um[text[j]] == 0)
                um.erase(text[j]);

            j++;
        }

        if(len < i - j + 1)
        {
            len = i - j + 1;
            first = j + 1;
        }
    }

    cout << len << " " << first << endl;

    return 0;
}