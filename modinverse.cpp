//mod inverse

#include<iostream> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace std; 
using namespace boost::multiprecision;

cpp_int extendedEuclid(cpp_int a, cpp_int b, cpp_int *x, cpp_int *y); 
cpp_int inverse(cpp_int a, cpp_int m);
void error();

int main() 
{ 
	cpp_int a, m, result;
	cout<<"Enter a: ";
    cin>>a;
    cout<<"Enter m: ";
    cin>>m;
	result = inverse(a, m); 
	cout << "Modular inverse is " << result<<endl;
	return 0; 
} 


// Function to find modulo inverse of i.e. a^-1(mod m) using extended Euclid's algorithm
cpp_int inverse(cpp_int a, cpp_int m)
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
	
	// Update variables pointed to the address of x and y, i.e., x1 and y1 for the previous function call using results of recursion 
	*x = y1 - (b/a) * x1; 
	*y = x1; 

	return gcd; 
} 

//A simple function to handle an error
void error()
{
	cout << "Modular inverse doesn't exist."<<endl; 
	exit(EXIT_FAILURE);
}