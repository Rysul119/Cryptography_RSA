//GCD function

#include <iostream>

using namespace std;

int gcd(int a, int b);

int main()
{
    int a, b, result;
    
    cout<<"Enter the first number: ";
    cin>> a;
    
    cout<<"Enter the second number: ";
    cin>> b;
    
    result = gcd(a, b);
    
    cout<<"The resultant GCD is "<<result;
}

int gcd(int a, int b){
    if (a==0){
        return b;
    }
    if(b==0){
        return a;
    }
    
    if(a>b){
        return gcd(b, a%b); //a%b returns remainder r where a = b*q + r
    }
    
    else{
        return gcd(a, b%a);
    }
}

