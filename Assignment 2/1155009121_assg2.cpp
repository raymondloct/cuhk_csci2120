// CSCI2120 Introduction to Software Engineering
//
// Assignment 2
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
// Date : 7-Mar-2016

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

string gestures[] = {"rock", "paper", "scissors", "Spock", "lizard"};

class Player {
	protected:
		string name; // name of the player
		int score; // the number of games won
		string winStmt; // winning statement of the player
	public:
		/* constructor with name and winStmt as input */
		Player(string playerName, string stmt) {
			name = playerName;
			score = 0;
			winStmt = stmt;
		}

		/* accessor for name */
		string getName() {
			return name;
		}

		/* display the gesture chosen */
		void display(int gesture){
			cout << name << ", your gesture is " << gestures[gesture] << "." << endl;
		}

		/* increase score by 1 and return the new score */
		int winRound() {
			score++;
			return score;
		}

		/* display the score */
		void showScore(){
			cout << name << " wins " << score << " round(s)." << endl;
		}

		/* display the winning statement */
		void winGame() {
			cout << name << ": " << winStmt << endl;
		}

		/* reset the score */
		void reset(){
			score = 0;
		}

		/* virtual method for getting gesture */
		virtual int getGesture() = 0;

		/* virtual destructor */
		virtual ~Player(){}

};

class HumanPlayer : public Player{
	public:
		/* constructor */
		HumanPlayer(string playerName, string stmt): Player(playerName, stmt){}

		/* get gesture input */
		int getGesture() {
			cout << name << ", please choose your gesture:" << endl; // prompt for user input
			int i;
			for (i = 0; i < 5; i++) {
				cout << (i+1) << ". " << gestures[i] << endl; // display the choices
			}
			bool valid = false; // whether a valid input has been received
			int choice;
			char c;
			while(!valid){
				c = _getch();
				if(c-'1' >= 0 && c-'5' <= 0){ // input is from 1 to 5
					choice = c - '1';
					valid = true;
				}
			}
			system("cls");
			return choice;
		}
};

class ComputerPlayer : public Player {
	public:
		/* constructor */
		ComputerPlayer() : Player("Computer", "You cannot beat a computer!") {
			srand(time(NULL)); // use time as random seed
		}

		/* generate random gesture */
		int getGesture() {
			return rand() % 5; // random number between 0 and 4
		}
};

class Game {
	private:
		Player *player1;
		Player *player2;
		int maxRounds; // maximum no. of Rounds
		int currentRound; // current Round no.

	public:
		/* check if input contains at least one alphabet */
		bool hasAlphabet(string input) {
			/* return true if the input contains at least one alphabet */
			for (int i = 0; i < input.length(); i++) {
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

		/* get name and winning statement from user */
		HumanPlayer *initHPlayer(string tempName, string otherName){
			system("cls");
			string name;
			if(tempName == ""){
				cout << "Please input your name:" << endl;
			}else{
				cout << tempName << ", please input your name:" << endl;
			}
			bool valid = false; // whether a valid input has been received
			while(!valid){
				getline(cin, name);
				if(!hasAlphabet(name)){
					cout << "Invalid player name! Your name should contain at least one alphabet." << endl;
				}else{
					if(name == "Computer"){
						cout << "Your name cannot be Computer" << endl;
					}else if(otherName != "" && name == otherName){
						cout << "Duplicated names" << endl;
					}else{
						valid = true;
					}
				}
			}
			cout << "Please input your winning statement:" << endl;
			string stmt;
			valid = false;
			while(!valid){
				getline(cin, stmt);
				if(!hasAlphabet(stmt)){
					cout << "Invalid winning statement! Your statement should contain at least one alphabet." << endl;
				}else{
					valid = true;
				}
			}
			HumanPlayer *guest = new HumanPlayer(name, stmt); // create the player with name and statement input
			return guest;
		}

		/* determine outcome and display results */
		/* return true if the game should continue */
		bool determine(int gesture1, int gesture2){
			system("cls");
			player1->display(gesture1);
			player2->display(gesture2);
			if(gesture1 == gesture2){ // in case of a draw
				cout << "Draw! Press any key to repeat this round..." << endl;
				_getch();
				return true;
			}else{
				currentRound++;
				int wScore;
				int winner = 0;
				if(((gesture2+5-gesture1) % 5) % 2 == 1){ // determine if player 2 won
					cout << player2->getName() << " wins in this round!" << endl;
					wScore = player2->winRound();
					winner = 2;
				}else{
					cout << player1->getName() << " wins in this round!" << endl;
					wScore = player1->winRound();
					winner = 1;
				}
				player1->showScore();
				player2->showScore();
				if(wScore*2 > maxRounds){
					cout << endl;
					if(winner == 1){
						player1->winGame();
					}else{
						player2->winGame();
					}
					return false;
				}
				cout << endl << "Press any key to continue..." << endl;
				_getch();
				return true;
			}
		}

		/* initialize the game by creating the players */
		bool init(){
			cout << "Rock - paper - scissors - Spock - lizard" << endl;
			cout << "1. Player vs. Computer\n2. Player vs. Player\n3. Exit" << endl;
			char c;
			int choice1;
			bool valid = false; // whether a valid input has been received
			while (!valid) {
				c = _getch();
				if (c == '3') {
					return false; // exit game
				}
				else if (c == '1' || c == '2') {
					choice1 = c - '1';
					valid = true;
				}
			}
			system("cls");
			cout << "Please select the Number of Rounds:" << endl;
			cout << "1. Three rounds\n2. Five rounds" << endl;
			valid = false;
			int choice2;
			while(!valid){
				c = _getch();
				if(c == '1' || c == '2'){
					choice2 = c - '1';
					valid = true;
				}
			}
			if(choice1 == 0){
				player1 = initHPlayer("", "");
				player2 = new ComputerPlayer;
			}else{
				player1 = initHPlayer("Player 1", "");
				player2 = initHPlayer("Player 2", player1->getName()); // need to check if the names are duplicated
			}
			maxRounds = 3+2*choice2;
			while(startGame()){} // loop while the player wants to continue
			return true;
		}

		/* start a new game, return true if new game after this */
		bool startGame() {
			currentRound = 0;
			while(currentRound <= maxRounds){
				int gesture1; // gesture by player 1
				int gesture2; // gesture by player 2
				system("cls");
				cout << "Round " << currentRound+1 << endl;
				gesture1 = player1->getGesture();
				gesture2 = player2->getGesture();
				if(!determine(gesture1, gesture2)){ // check the result, see if the game has ended
					char playAgain;
					cout << "Would you like to play again? (y/n)" << endl;
					bool valid = false;
					while(!valid){
						playAgain = _getch();
						if(playAgain == 'n'){ // delete current players and initialize again
							delete player1;
							delete player2;
							system("cls");
							return false;
						}else if(playAgain == 'y'){ // reset the player scores and start a new game
							player1->reset();
							player2->reset();
							system("cls");
							return true;
						}
					}
				}
				system("cls");
			}
			return false;
		}
};

int main() {
	Game game;
	while(game.init()){} // loop while the player does not exit
	return 0;
}
