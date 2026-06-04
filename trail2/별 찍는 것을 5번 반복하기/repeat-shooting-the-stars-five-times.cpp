#include <iostream>
using namespace std;

void printStars(){
    for(int j=0;j<5;j++){
        for(int i=0;i<10;i++)
            cout<<"*";
        cout << endl;
    }
    return;
}
int main() {
    // Please write your code here.
    printStars();
    return 0;
}