#include <iostream>
#include <list>

using namespace std;

int main(){

    list<int> ll;

    while(1)
    {
        string cmd;
        cin >> cmd;

        if(cmd == "push_front")
        {
            int n; cin >> n;
            ll.push_front(n);
            cout << "ok" << endl;
        } 
        else if(cmd == "push_back")
        {
            int n; cin >> n;
            ll.push_back(n);
            cout << "ok" << endl;
        }
        else if(cmd == "pop_front")
        {
            if(ll.empty()){
                cout << "error" << endl;
            } else {
                cout << ll.front() << endl;
                ll.pop_front();
            }
        } 
        else if(cmd == "pop_back")
        {
            if(ll.empty()){
                cout << "error" << endl;
            } else {
                cout << ll.back() << endl;
                ll.pop_back();
            }
        } 
        else if(cmd == "front")
        {
            if(ll.empty()){
                cout << "error" << endl;
            } else {
                cout << ll.front() << endl;
            }
        } 
        else if(cmd == "back")
        {
            if(ll.empty()){
                cout << "error" << endl;
            } else {
                cout << ll.back() << endl;
            }
        } 
        else if(cmd == "size")
        {
            cout << ll.size() << endl;
        } 
        else if(cmd == "clear")
        {
           ll.clear();
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

