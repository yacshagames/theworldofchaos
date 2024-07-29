#include <iostream>
using std::cout;
using std::cin;

int i, j;
//pointers to the basic functions used in f(x)
double(*p[4])(double x) = { sin, cos, tan, exp };

double f(double x)
{
	return p[i](x)*p[j](x / 2);	//note that the subfunctions of f(x)
								//have the form h(x)g(x/2)
}

int main() {
	double x;
	cout << "\Enter X: ";
	cin >> x;

	while (x == 2) {
		cout << "2 does not belong to the domain!!!"; 
		return 1;
	}

	i = x < 0 ? 0 : x >= 0 && x < 2 ? 1 : 3;	//for h(x) it is recognized
												//what function to point to
	j = x < 0 ? 1 : x >= 0 && x < 2 ? 0 : 2;	 //for g(x/2) it is recognized
												//what function to point to


	cout << "\nResult: f( "<< x <<" ): " << f(x);
	
	return 0;
}


