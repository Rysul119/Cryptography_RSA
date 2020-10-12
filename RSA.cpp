//RSA 

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
cpp_int extendedEuclid(cpp_int a, cpp_int b, cpp_int *x, cpp_int *y); 
cpp_int inverse(cpp_int a, cpp_int m);
cpp_int RSA(cpp_int message, cpp_int key);

int main()
{
    cpp_int skey, pkey; 
    int iter, size, message;

    srand(time(0));

    cout<<"Insert iteration: ";
    cin>>iter;
    cout<<"Insert bit size or the key: ";
    cin>>size;
    skey= primerGenerator(iter, size);
    cout<<"Generated secret key: "<<skey<<endl;

    message = 10;

    //calling RSA for encryption for finding the public key, encryption, and decryption of message
    
    pkey = RSA(message, skey);

    cout<<"The public key is: "<<pkey<<endl;

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
    //cout<<binNumber[0];
    
    //binary number formation
    for(int i=1; i<range-1; i++){
        binNumber[i] = rand()%2;
        //cout<<binNumber[i];
    }

    binNumber[range-1] = 1;
    //cout<<binNumber[range-1]<<endl;
    
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
            //cout<<"GCD is true"<< endl;
            return false;
        }
        //powr = power(a, p-1);
        //cout<<powr<<endl;
        if(power(a, p-1)%p!=1) //a^(p-1)!=1 (mod p) //check
        {
            //cout<<"Fermat little theorem is true"<< endl;
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
        //cout<<"Primer candidate is: "<<candidate<<endl;
        candidate_result = isPrime(candidate, iterg);

        if(candidate_result){
            return candidate;
        }
    }
    
    
    return 0;

}


cpp_int extendedEuclid(cpp_int a, cpp_int b, cpp_int *x, cpp_int *y) 
{ 
	// Base Case 
	if (a == 0) 
	{ 
		*x = 0, *y = 1; 
		return b; 
	} 

	cpp_int x1, y1; // To store results of recursive call 
	cpp_int gcd = extendedEuclid(b%a, a, &x1, &y1); // ax+by = gcd(a,b), given a, b trying to find x(mod inverse) and y
	
	// Update variables pointed to the address of x and y, i.e., x1 and y1 for the previous function call using results of recursive 
	*x = y1 - (b/a) * x1; 
	*y = x1; 

	return gcd; 
} 

// Function to find modulo inverse of i.e. a^-1(mod m) 
cpp_int inverse(cpp_int a, cpp_int m)
{ 
	cpp_int x, y, modinverse; 
	cpp_int g = extendedEuclid(a, m, &x, &y); 
	if (g != 1) 
		cout << "Inverse doesn't exist"; 
	else
	{ 
		// m is added to handle negative x 
		modinverse = (x%m + m) % m; 
		
		return modinverse;
	} 
} 


//Implementation of RSA
cpp_int RSA(cpp_int message, cpp_int skey)
{
    cpp_int p, q, n, phi, pkey, enc, dec;
    int bit_size = 14;
    int iter = 10;

    p = primerGenerator(iter, bit_size);
    cout<<"Value of p: "<<p<<endl;

    q = primerGenerator(iter, bit_size);
    cout<<"Value of q: "<<q<<endl;

    n = p * q;
    //calculating the Euler function phi(n) for the given p and q where n = p*q
    phi = (p-1) * (q-1);

    //finding the public key
    pkey = inverse(skey, phi);

    cout<<"Actuale message: "<<message<<endl;

    //performing encryption on message
    enc = power(message, pkey)%n;

    cout<<"Encrypted message: "<<enc<<endl;

    //performing decryption on message
    dec = power(enc, skey)%n;

    cout<<"Decrypted message: "<<dec<<endl;

    return pkey;
}
