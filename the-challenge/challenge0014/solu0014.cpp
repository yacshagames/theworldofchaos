#include <iostream>
using std::cout;
using std::cin;

void main()
{
 int a,b;

 cout << "\n\nEnter integer A: ";
 cin >> a;
 cout << "\nEnter integer B: ";
 cin >> b;

 a=a+b,a=a-(b=(((a-b)>=b)*b)+((b>(a-b))*(a-b)));

 if( a==b )
	 cout << "\n\nThey are equal numbers."; 
else 
	 cout << "\n\nThe largest is " << a << " and the smallest is " << b << ".";
}



