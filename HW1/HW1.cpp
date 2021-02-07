#include "std_lib_facilities.h"
using namespace std;
int main()
try
{
	vector<int>guess;
	vector<int>answer = { 0,0,0,0 };

	int trial = 0;
	int a = 0;
	int i = 0, k = 0, n;
	int bull = 0, cow = 0;
	char again_or_not;

	//get random 4-digit answer
	for (i = 0; i <= 3; i++)
		answer[i] = randint(0, 9);

	//check if there is a same nuber
	for (i = 0; i <= 2; i++)
	{
		while (answer[i + 1] == answer[i])
			answer[i + 1] = randint(0, 9);
	}

	//guessing numbers
	while (1)
	{
		cout << "Guess for numbers: ";
		//input numbers
		for (int i = 0; i < 4; i++)
		{
			cin >> n;
			guess.push_back(n);
		}
		//error: not a number
		if (!cin) error("Error: Not a number");
		//error: out of range
		for (int i = 0; i < 4; i++)
			if ((guess[i] < 0) || (guess[i] > 9))
				error("out of range [0,9]");

		//check bull- right digit, right position
		for (int i = 0; i < 4; i++)
		{
			if (answer[i] == guess[i + a]) {
				bull++;
			}
		}
		//check cow- right digit, wrong position
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (answer[j] == guess[i + a] && i != j) {
					cow++;
				}
			}
		}
		//if answer is correct, ask player play again or not
		if (bull == 4)
		{
			cout << "Congratulations!" << endl;
			cout << "You guessed correctly." << endl;
			cout << "> Play again?(y/n) ";
			cin >> again_or_not;
			if (again_or_not == 'y')
				//if player wants to play again, continue 
			{
				continue;
				trial = 0;
			}
			// if player wants to quit, break the while
			else
				break;
		}

		else {
			//show count of bull and cow
			cout << bull << " bull and " << cow << " cow." << endl;
		}

		//initialize cow=0,bull=0 to geuss one more time
		cow = 0;
		bull = 0;
		//push.back() substitute from back and it's type is int, so you should a=a+4
		a = a + 4;
		//if you guess wrong answer, trial gets 1
		trial++;

		//if player guess 10times, you failed
		if (trial == 10)
		{
			cout << "You failed!" << endl;
			cout << "Correct numbers are: " << answer[0] << answer[1] << answer[2] << answer[3] << endl;
			//asking player to play again or not
			cout << "> Play again?(y/n)";
			cin >> again_or_not;
			if (again_or_not == 'y')
			{
				//if player wants to play again, start again!
				trial = 0;
				continue;
			}
			else
				//if player wants to quit, break the while
				break;
		}
		keep_window_open();
	}
}
//try...catch 
catch (runtime_error&e)
{
	cout << e.what() << endl;
	return 0;
	keep_window_open();
}