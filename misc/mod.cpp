// modulas function


#include <iostream>

using namespace std;

int mod(int a, int b);

int main()
{
    int a, b, result;
    cout<<"Enter a: ";
    cin>>a;
    cout<<"Enter b: ";
    cin>>b;
    result = mod(a, b);
    cout<<result;
    return 0;
}

int mod(int a, int b){
    if ((a%b)>0){
        return a%b;
    }
    else{
        return b+a%b;
    }
}

