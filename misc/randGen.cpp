#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

cpp_int power(cpp_int x, cpp_int n);
cpp_int randomGen(int range);

int main()
{
    int bitsize;
    cpp_int randomNumber;

    srand(time(0));
    cout<<"Insert the bit size: ";
    cin>> bitsize;

    randomNumber = randomGen(bitsize);
    cout<<"Generated random number: "<<randomNumber;

    return 0;
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


