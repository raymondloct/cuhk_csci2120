// CSCI2120 Introduction to Software Engineering
//
// Assignment 1
//
// I declare that the assignment here submitted is original except for source
// material explicitly acknowledged.I also acknowledge that I am aware of
// University policy and regulations on honesty in academic work, and of the
// disciplinary guidelines and procedures applicable to breaches of such policy
// and regulations, as contained in the following University website :
// http ://www.cuhk.edu.hk/policy/academichonesty/.
//
// Student Name : Lo Chun Tung
// Student ID : 1155009121
// Date : 13-Feb-2016

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class PasswordPanel {
private:
	string password; // a string for storing the password

public:
	/* accessor for the password, in string format */
	string getPassword() {
		return password;
	}

	/* generate random password */
	void generate() {
		srand(time(NULL));
		string choices = "0123456789";
		password = "";
		for (int i = 0;i < 4; i++) {
			int chosen = rand() % choices.length();
			password += choices.at(chosen); // append the selected char to password
			choices.replace(chosen, 1, ""); // remove the selected from available options
		}
	}

	/* check the guessed sequence against password */
	/* return the hint as a string */
	string check(string guess) {
		string hint = "";
		for (int i = 0;i < 4;i++) {
			if (guess.at(i) == password.at(i)) {
				hint += 'O';
			}
			else {
				bool matched = false;
				for(int j=0;j<4;j++){
					if (guess.at(i) == password.at(j)) {
						matched=true;
					}
				}
				if (matched) {
					hint += '.';
				}
				else {
					hint += 'X';
				}
			}
		}
		return hint;
	}

};

class Player {
private:
	string name;
	int trials;

public:
	/* constructor with name and trials as input */
	Player(string playerName, int initTrials) {
		name = playerName;
		trials = initTrials;
	}

	/* accessor for the name of player */
	string getName() {
		return name;
	}

	/* reduce the number of trials by 1 */
	/* return the number of remaining trials */
	int reduceTrials() {
		if (trials > 0) {
			trials--;
		}
		return trials;
	}
};

class PasswordGuessingGame {
public:
	/* check if the input is a valid name */
	bool validName(string input) {
		/* return true if the input contains at least one alphabet */
		for (int i = 0;i < input.length();i++) {
			char c = input.at(i);
			if (c - 'a' >= 0 && c - 'z' <= 0) {
				return true; // character is within a-z
			}
			if (c - 'A' >= 0 && c - 'Z' <= 0) {
				return true; // character is within A-Z
			}
		}
		return false;
	}

	/* check if the input is a valid guess */
	bool validGuess(string input) {
		if (input.length() != 4) {
			return false; // input is not 4-digit long
		}
		for (int i = 0;i < 4;i++) {
			char digit = input.at(i);
			if (digit - '0' < 0 || digit - '9' > 0) {
				return false; // character is not within 0-9
			}
			for (int j = i + 1;j < 4;j++) {
				if (digit == input.at(j)) {
					return false; // duplicate digit
				}
			}
		}
		return true;
	}

	/* start a new game */
	void startGame() {
		int maxTrials = 6;
		string name;
		cout << "Please enter your name: ";
		getline(cin, name); // read the input and set it to variable "name"
		while (!validName(name)) {
			cout << "Your input has to contain at least one alphabet character." << endl << "Please enter your name: ";
			getline(cin, name); // ask player to input name and read again
		}
		Player guest(name, maxTrials); // create Player instance
		PasswordPanel panel; // create PasswordPanel instance
		panel.generate(); // generate random password
		cout << guest.getName() << ", you have to guess a 4-digit password in " << maxTrials << " trials!" << endl;
		bool ended = false; // indicator of whether the game has ended
		string guess;
		string hint; // resultant hint after guessing
		while (!ended) {
			cout << "Make a guess:" << endl;
			getline(cin, guess);
			if (!validGuess(guess)) {
				cout << "Your guess should be a 4-digit number with no duplicate digits." << endl << endl;
			}
			else {
				hint = panel.check(guess); // check the guess against the password
				if (hint == "OOOO") {
					cout << guest.getName() << ", you have cracked the password! Congratulations!" << endl;
					ended = true; // player have guessed correctly
				}
				else {
					int remainingTrials = guest.reduceTrials();
					cout << hint << " (Number of trials left: " << remainingTrials << ")" << endl << endl; // display the hint and number of remaining trials
					if (remainingTrials == 0) {
						cout << guest.getName() << ", you have used up all trials! The password is " << panel.getPassword() << "! Game Over!" << endl;
						ended = true; // player have used up all trials
					}
				}
			}
		}

	}
};

int main() {
	PasswordGuessingGame game;
	game.startGame();
	return 0;
}