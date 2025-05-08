#include <iostream>
#include <stack>

using namespace std;

int main()
{
    stack<int> st;

    while(1)
    {
        string cmd;
        cin >> cmd;

        if(cmd == "push")
        {
            int n; cin >> n;
            st.push(n);
            cout << "ok" << endl;
        } 
        else if(cmd == "pop")
        {
            if(st.size() == 0)
            {
                cout << "error" << endl;
            } 
            else 
            {
                cout << st.top() << endl;    
                st.pop();
            }
        } 
        else if(cmd == "back")
        {
            if(st.size() == 0)
            {
                cout << "error" << endl;
            } 
            else 
            {
                cout << st.top() << endl;
            }
        } 
        else if(cmd == "size")
        {
            cout << st.size() << endl;
        } 
        else if(cmd == "clear")
        {
            while(st.size())
            {
                st.pop();
            }
            cout << "ok" << endl;
        } 
        else 
        {   
            break;
        }
    }

    cout << "bye" << endl;
    return 0;
}

