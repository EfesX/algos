#include <iostream>

using namespace std;

int main() {
    int x1, y1;
    cin >> x1 >> y1;

    int x2, c;
    cin >> x2 >> c;

    int label = x1 ^ y1;
    int y = x2 ^ c;

    cout << label << endl;
    cout << y << endl;

    return 0;
}
