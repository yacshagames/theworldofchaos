/* Solved by RiMS */

#include <iostream>
using std::cout;
using std::cin;

/* I hope this is the secant... */
#define SEC(x) (1 / cos( x ) )

/* I define the Expressions for each interval with Macros */
/* This is not mandatory, I could have put it inside
the return(...) but it is clearer to me when coding */
#define Exp1(x) ( 2 * sin( (x)/2 ) * pow( cos( (x)/2 ), 2.0 ) )
#define Exp2(x) ( 1.0/4.0 * sin(2 * (x) ) * SEC( (x)/2 ) )
#define Exp3(x) ( exp( (x) ) * tan( (x) ) )


double f( double x) {
	return( Exp1(x) * (x<0) +
			Exp2(x) * (x>=0) * (x<2) +
			Exp3(x) * (x > 2) );
}

int main() {
	double x;
	cout << "\Enter X: ";
	cin >> x;

	cout << "\nResult: f( "<< x <<" ): " << f(x);
	
	return 0;
}


