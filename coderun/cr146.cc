#include <iostream>
#include <queue>


using namespace std;

int main()
{
    queue<int> q1, q2;

    for(int i = 0; i < 5; i++)
    {
        int val; cin >> val;
        q1.push(val);
    }
    
    for(int i = 0; i < 5; i++)
    {
        int val; cin >> val;
        q2.push(val);
    }

    int steps = 0;

    while(!q1.empty() && !q2.empty())
    {
        int val1 = q1.front();
        int val2 = q2.front();

        q1.pop();
        q2.pop();

        if(val2 == 0 && val1 == 9)
        {
            q2.push(val1);
            q2.push(val2);
        }

        else if(val2 == 9 && val1 == 0)
        {
            q1.push(val1);
            q1.push(val2);
        }

        else if(val2 > val1)
        {
            q2.push(val1);
            q2.push(val2);
        }

        else if(val2 < val1)
        {
            q1.push(val1);
            q1.push(val2);
        }

        steps++;

        if(steps == 10e6)
        {
            cout << "botva" << endl;
            return 0;
        }
    }

    
    if(q1.empty()) cout << "second " << steps << endl;
    else if(q2.empty()) cout << "first " << steps << endl;

    return 0;
}
