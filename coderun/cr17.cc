#include <iostream>
#include <stack>

using namespace std;

struct pipeline_t {
    stack<double> storage;
    stack<double> factory;

    bool next_item(double item){
        if(storage.empty()) {
            storage.push(item);
            return true;
        }

        while(!storage.empty() && storage.top() < item){
            factory.push(storage.top());
            storage.pop();
        }

        if(!factory.empty() && factory.top() > item){
            return false;
        }

        storage.push(item);
        return true;
    }

    void reset(){
        while(!storage.empty()) storage.pop();
        while(!factory.empty()) factory.pop();
    }
};

int main(){
    int N; cin >> N;

    pipeline_t pipeline;

    for(int i = 0; i < N; i++){
        int k; cin >> k;
        bool ok = true;
        for(int i = 0; i < k; i++){
            double item; cin >> item;
            ok &= pipeline.next_item(item);
        }
        cout << ok << endl;
        pipeline.reset();
    }

    return 0;
}
