#include <iostream>
using namespace std;

void run(int n){
    cout << "HelloWorld" << endl;
    if(n==1) return;
    run(n-1);
}
int main() {
    // Please write your code here.
    int n;
    cin >> n;
    run(n);
    return 0;
}
