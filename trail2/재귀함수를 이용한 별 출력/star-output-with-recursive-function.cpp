#include <iostream>
using namespace std;

void star(int n) {
    if (n == 0) return;

    star(n - 1);

    for (int i = 1; i <= n; i++) {
        cout << "*";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;

    star(n);

    return 0;
}