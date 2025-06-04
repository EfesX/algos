#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    string line;
    map<string, int> mm;

    string maxkey = "z";
    int maxval = 0;

    while(getline(cin, line))
    {
        istringstream iss(line);
        string word;
        while(iss >> word)
        {
            mm[word]++;
            if(mm[word] > maxval)
            {
                maxval = mm[word];
                maxkey = word;
            }
            else if(mm[word] == maxval)
            {
                if(word < maxkey)
                {
                    maxval = mm[word];
                    maxkey = word;
                }
            }
        }
    }

    //for(auto [k,v] : mm){
    //    if(v == maxval){
    //        cout << k << endl;
    //        break;
    //    }
    //}

    cout << maxkey << endl;

    return 0;
}
