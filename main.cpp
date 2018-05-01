#include <iostream>
#include <cstring>
using namespace std;
int main() {
    char *a=new char[5];
    strcpy(a,"none");
    a[4]='\0';
    cout<<a<<endl;
    return 0;
}