#include <iostream>
using namespace std;


void star(int n){
    for(int i=1;i<=n;i++)
    cout << "* ";
    cout << endl;
    if(n==1) return;
    star(n-1);
}
void star_re(int n){
    if(n == 0) return;
   star_re(n-1);
    for(int i=1;i<=n;i++)
    cout << "* ";
    cout << endl;
}
int main() {
    int n;
    cin >> n;
    star(n);
    star_re(n);
    return 0;
}