
//power function

#include <iostream>
using namespace std;

int power(int x, int n);

int main() {
    int x, n, result;
    
    cout<<"Enter the base: ";
    cin>>x;
    cout<<"Enter the power: ";
    cin>>n;
    
    result = power(x, n);
    cout<<x<<" to the power "<<n<< " is "<<result;
    
    return 0;
}

int power(int x, int n) {
    if (n == 1)
        return x;
    if (n == 0)
        return 1; 
    if (n%2)
        return x*power(x, (n-1)/2) * power(x, (n-1)/2);
    else
        return power(x, n/2) * power(x, n/2);
}
