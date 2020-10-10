#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

cpp_int gcd(cpp_int a, cpp_int b);
cpp_int power(cpp_int x, cpp_int n);
bool isPrime(cpp_int p, int iter);
cpp_int primerGenerator(cpp_int upper, cpp_int lower, int iterg);

int main()
{
    cpp_int upper, lower, prime; 
    int iter;

    srand(time(0));

    cout<<"Insert upper limit: ";
    cin>>upper;
    cout<<"Insert lower limit: ";
    cin>>lower;
    cout<<"Insert iteration: ";
    cin>>iter;
    prime = primerGenerator(upper, lower, iter);
    cout<<"Generated prime number: "<<prime;
    return 0;
}

cpp_int gcd(cpp_int a,  cpp_int b){
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

cpp_int power(cpp_int x, cpp_int n) {
    if (n == 3)
        return x*x*x;
    if (n == 2)
        return x*x; 
    if (n%2)
        return x*power(x, (n-1)/2) * power(x, (n-1)/2);
    else
        return power(x, n/2) * power(x, n/2);
}

bool isPrime(cpp_int p, int iter){
    cpp_int a; 
    cpp_int powr;
    //srand((time(0))); 
    for(int i=0; i<iter; i++){
        a = rand()%(p-1)+1;
        //cout<<"Value of a is: "<<a<<endl;
        if (gcd(a, p)>1)
        {
            cout<<"GCD is true"<< endl;
            return false;
        }
        powr = power(a, p-1);
        //cout<<powr<<endl;
        if(powr%p!=1) //a^(p-1)!=1 (mod p) //check
        {
            cout<<"Fermat little theorem is true"<< endl;
            return false;
        }
    }
    
    return true;
}

cpp_int primerGenerator(cpp_int upper, cpp_int lower, int iterg){

    cpp_int candidate;
    bool candidate_result;

    //srand(time(0));
    //increase the randomness and iteration not working << done had a bug in the main()
    for(int i = 0; i<100000; i++){
        candidate = rand()%(upper - lower) + lower;
        cout<<"Primer candidate is: "<<candidate<<endl;
        candidate_result = isPrime(candidate, iterg);

        if(candidate_result){
            return candidate;
        }
    }
    
    
    return 0;

}

