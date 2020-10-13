//GCD function

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

cpp_int gcd(cpp_int a, cpp_int b);

int main()
{
    cpp_int a, b, result;
    
    cout<<"Enter the first number: ";
    cin>> a;
    
    cout<<"Enter the second number: ";
    cin>> b;
    
    result = gcd(a, b);
    
    cout<<"The resultant GCD is "<<result<<endl;

    return 0;
}

cpp_int gcd(cpp_int a, cpp_int b){
    if (a==0){
        return b;
    }
    else if(b==0){
        return a;
    }
    
    else if(a>b){
        return gcd(b, a%b); //a%b returns remainder r where a = b*q + r
    }
    
    else{
        return gcd(a, b%a);
    }
}

