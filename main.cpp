#include <iostream>
#include "function.h"
using namespace std;

int main() {
    char c[2], a[42], b[42];
    HugeInteger result,resultWithString;

    while (  cin>>c>>a>>b ) {
        HugeInteger n1(a);
        HugeInteger n2(b);

        if(c[0] == '+') {
            result = n1+n2;
            resultWithString = n1+b;
            cout<<result<<endl<<resultWithString<<endl;

        } else if(c[0] == '-') {
            result = n1-n2;
            resultWithString = n1-b;
            cout<<result<<endl<<resultWithString<<endl;

        }else if(c[0] == '*') {
            result = n1*n2;
            resultWithString = n1*b;
            cout<<result<<endl<<resultWithString<<endl;

        }else if(c[0] == '/') {
            result = n1/n2;
            resultWithString = n1/b;
            cout<<result<<endl<<resultWithString<<endl;

        } else if (c[0] == '>') {
            cout<< (n1>n2) <<endl;
        } else {
            cout<<"ERROR";
            return 0;
        }
    }
    return 0;
}// end main

