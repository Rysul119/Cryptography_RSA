//RSA 

#include <iostream>
#include <ctime> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

//An RSA class

class RSA {
    public:
        cpp_int message;
        int keybit; //for generating a key
        int pqbit; // for generating two large prime numbers
        RSA(int x, int y);
        cpp_int keygen();
        cpp_int keycalc();
        void encryption(cpp_int plaintext); //ecryption method
        void decryption(cpp_int ciphertext, cpp_int pq, cpp_int publickey); //decryption method
    private:
        cpp_int n, p, q, phi, skey, pkey;
        int iter = 10; // for the primality testing of generate large prime numbers
        cpp_int gcd(cpp_int a, cpp_int b);
        cpp_int power(cpp_int x, cpp_int n);
        cpp_int randomGen(int range);
        bool isPrime(cpp_int p, int iter);
        cpp_int primerGenerator(int iterg, int bitsize);
        cpp_int extendedEuclid(cpp_int a, cpp_int b, cpp_int *x, cpp_int *y); 
        cpp_int inverse(cpp_int a, cpp_int m);
        void error();

};

RSA::RSA(int x, int y)
{
    keybit = x;
    pqbit = y;
}

cpp_int RSA::gcd(cpp_int a,  cpp_int b){
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

cpp_int RSA::power(cpp_int x, cpp_int n) {
    if (n == 1)
        return x;
    else if (n == 0)
        return 1; 
    else if (n%2)
        return x*power(x, (n-1)/2) * power(x, (n-1)/2);
    else
        return power(x, n/2) * power(x, n/2);
}

cpp_int RSA::randomGen(int range)
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

bool RSA::isPrime(cpp_int p, int iter){
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

cpp_int RSA::primerGenerator(int iterg, int bitsize){

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

cpp_int RSA::extendedEuclid(cpp_int a, cpp_int b, cpp_int *x, cpp_int *y) 
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
cpp_int RSA::inverse(cpp_int a, cpp_int m)
{ 
	cpp_int x, y, modinverse; 
	cpp_int g = extendedEuclid(a, m, &x, &y); 
	if (g != 1){
		error();
		return 0;
    }
	else
	{ 
		// m is added to handle negative x 
		modinverse = (x%m + m) % m; 
		return modinverse;
	} 
} 

cpp_int RSA::keygen( )
{
    //generates a private key
    skey = primerGenerator(iter, keybit);
    return skey;
}

cpp_int RSA::keycalc()
{
    p = primerGenerator(iter, pqbit);
    cout<<"Value of p: "<<p<<endl;

    q = primerGenerator(iter, pqbit);
    cout<<"Value of q: "<<q<<endl;

    n = p * q;
    //calculating the Euler function phi(n) for the given p and q where n = p*q
    phi = (p-1) * (q-1);

    //calculating the public key
    pkey = inverse(skey, phi);
    return pkey;
}

void RSA::encryption(cpp_int plaintext)
{
    cpp_int enc;
    enc = power(plaintext, skey)%n;
    cout<<"Encrypted message: "<<enc<<endl;
}

void RSA::decryption(cpp_int ciphertext, cpp_int pq, cpp_int publickey)
{
    cpp_int dec;
    dec = power(ciphertext, pkey)%pq;
    cout<<"Decrypted message: "<<dec<<endl;
}

//A simple function to handle an error
void RSA::error()
{
	cout << "Modular inverse doesn't exist."<<endl; 
	exit(EXIT_FAILURE);
}


int main()
{
    //Create an RSA object
    //Ask for the bit size of private key
    //Generate the key
    //Ask for the bit size of the 2 randomly generated number
    //Calculate the public key
    //Ask for the plaintext
    //Do encryption
    //Do decryption, check by using the same ciphertext, n and public key from above
}

