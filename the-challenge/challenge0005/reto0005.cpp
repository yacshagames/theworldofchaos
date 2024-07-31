/* CHALLENGE0005.CPP
* ========== cworld@egroups.com
*
* 1. (and fundamental): Why can't you get the SUCCESS message?
* What is wrong and why?
* 2. (secondary): How should the program be changed so that it works?
* (i.e. so that it accepts 1.2 as a solution)
*
* Notes: Tested in TurboC++, BorlandC++ , DJGPP
*
* (C) Antonio Romeral 3-Sept-2000
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	float  vfloat;
	int exito = 0;

	cout << " CHALLENGE0005.CPP Guess the secret number" << endl;
	cout << " ========== (by the way, that number is 1.2)" << endl;
	cout << " (c) Antonio Romeral 3- Sept - 2000\n" << endl;

	do {
		cout << "(To give up enter 0)" << endl;
		cout << "What is the secret decimal number (between 1 and 2)? The number is: ";
		cin >> vfloat;
		cout << "\n You have entered the number: " << vfloat;

		if (vfloat == 1.2) {
			cout << ">>> YOU GOT IT RIGHT!!!! " << endl;
			exito = 1;
			break;
		}
		else {
			cout << ">>> THIS IS NOT THE NUMBER. Please try again\n" << endl;
		}

	} while (vfloat);

	cout << "\n\n\n" << endl;
	
	if (exito) 
		cout << "PERFECT. YOU ACHIEVED THE IMPOSSIBLE" << endl;
	else {
		cout << "Try again (what the hell is going on here?)" << endl;
		cout << "(pay attention... the solution is 1.2). Try again!!!" << endl;
	}

	return 0;
}