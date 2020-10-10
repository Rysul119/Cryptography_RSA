#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

cpp_int gcd(cpp_int a, cpp_int b);
cpp_int power(cpp_int x, cpp_int n);
cpp_int randomGen(int range);
bool isPrime(cpp_int p, int iter);
cpp_int primerGenerator(int iterg, int bitsize);

int main()
{
    cpp_int prime; 
    int iter, size;

    srand(time(0));

    cout<<"Insert iteration: ";
    cin>>iter;
    cout<<"Insert bit size: ";
    cin>>size;
    prime = primerGenerator(iter, size);
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
    if (n == 1)
        return x;
    if (n == 0)
        return 1; 
    if (n%2)
        return x*power(x, (n-1)/2) * power(x, (n-1)/2);
    else
        return power(x, n/2) * power(x, n/2);
}

cpp_int randomGen(int range)
{
    cpp_int binNumber[range];
    cpp_int randNumber = 0;
    binNumber[0] = 1;
    cout<<binNumber[0];
    
    //binary number formation
    for(int i=1; i<range-1; i++){
        binNumber[i] = rand()%2;
        cout<<binNumber[i];
    }

    binNumber[range-1] = 1;
    cout<<binNumber[range-1]<<endl;
    
    //bin to decimal convertion

    for(int i = 0; i<range; i++){
        randNumber += binNumber[i] * power(2, i);
    }

    return randNumber;
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

cpp_int primerGenerator(int iterg, int bitsize){

    cpp_int candidate;
    bool candidate_result;

    //srand(time(0));
    //increase the randomness and iteration not working << done had a bug in the main() input
    for(int i = 0; i<100000; i++){
        candidate = randomGen(bitsize);
        cout<<"Primer candidate is: "<<candidate<<endl;
        candidate_result = isPrime(candidate, iterg);

        if(candidate_result){
            return candidate;
        }
    }
    
    
    return 0;

}

