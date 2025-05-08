#include <iostream>
#include <queue>

using namespace std;

int main(){

    queue<int> q;

    while(1)
    {
        string cmd;

        cin >> cmd;

        if(cmd == "push")
        {
            int n; cin >> n;
            q.push(n);
            cout << "ok" << endl;
        } 
        else if(cmd == "pop")
        {
            if(q.size() == 0){
                cout << "error" << endl;
            } else {
                cout << q.front() << endl;    
                q.pop();
            }
        } 
        else if(cmd == "front")
        {
            if(q.size() == 0){
                cout << "error" << endl;
            } else {
                cout << q.front() << endl;
            }
        } 
        else if(cmd == "size")
        {
            cout << q.size() << endl;
        } 
        else if(cmd == "clear")
        {
            while(q.size()){
                q.pop();
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

