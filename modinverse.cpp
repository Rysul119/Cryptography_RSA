//mod inverse

#include<iostream> 
using namespace std; 

int extendedEuclid(int a, int b, int *x, int *y); 

int inverse(int a, int m);

int main() 
{ 
	int a, m, result;
	cout<<"Enter a: ";
    cin>>a;
    cout<<"Enter m: ";
    cin>>m;
	result = inverse(a, m); 
	cout << "Modular inverse is " << result;
	return 0; 
} 

// Function to find modulo inverse of i.e. a^-1(mod m) 
int inverse(int a, int m)
{ 
	int x, y, modinverse; 
	int g = extendedEuclid(a, m, &x, &y); 
	if (g != 1) 
		cout << "Inverse doesn't exist"; 
	else
	{ 
		// m is added to handle negative x 
		modinverse = (x%m + m) % m; 
		
		return modinverse;
	} 
} 


int extendedEuclid(int a, int b, int *x, int *y) 
{ 
	// Base Case 
	if (a == 0) 
	{ 
		*x = 0, *y = 1; 
		return b; 
	} 

	int x1, y1; // To store results of recursive call 
	int gcd = extendedEuclid(b%a, a, &x1, &y1); // ax+by = gcd(a,b), given a, b trying to find x(mod inverse) and y
	
	// Update variables pointed to the address of x and y, i.e., x1 and y1 for the previous function call using results of recursive 
	*x = y1 - (b/a) * x1; 
	*y = x1; 

	return gcd; 
} 

