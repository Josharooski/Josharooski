/* DICE GAME
* This dice-based game is meant for 2 players to throw a maximum of four dice
* to try to reach or surpass a target score. A score of 1 results in a "bust"
* and the player recieves no points for that round.
* 
* Player data is contained in a struct named player. Each player has an ID,
* score, and boolean winner value. A player's fist die is automatically
* rolled for them. A random number between DICE_MIN and DICE_MAX is made
* and saved. A roulette style effect is achieved by displaying a random
* number, waiting for CYCLE_SPEED milliseconds, backspacing and deleting
* the number, then repeating the process.
* 
* Each player's score is checked after their turn against TARGET_SCORE. After
* GAME_ROUNDS rounds if no player's score is at or above TARGET_SCORE the player
* with the highest score wins.
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>
#include <conio.h>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void gameSetupAndGo();
bool gameBeginCheck();
void gameLoop(bool& gameOver, player& playerOne, player& playerTwo);
void doOnePlayerRound(player& player);
int getDiceRoll();
void rulesExplain();
void announceWinner(player& playerOne, player& playerTwo);
void seedRand();

const int DICE_MIN = 1;
const int DICE_MAX = 6;
const int CYCLE_NUM = 25;
const int CYCLE_SPEED = 33;
const int GAME_ROUNDS = 4;
const int TARGET_SCORE = 48;

struct player {
	int score;
	int ID;
	bool winner;
};


int main() {
	seedRand();
	gameSetupAndGo();
}


void gameSetupAndGo() {
	player p1, p2;
	p1.score = 0;
	p1.ID = 1;
	p1.winner = false;
	p2.score = 0;
	p2.ID = 2;
	p2.winner = false;

	if (!gameBeginCheck()) {
		exit(0);
	}

	bool gameIsOver = false;
	while (!gameIsOver) {
		gameLoop(gameIsOver, p1, p2);
	}

	announceWinner(p1, p2);
}

bool gameBeginCheck() {
	char input;
	bool continueGame = false;
	rulesExplain();
	cin >> input;
	cout << endl << endl;

	if (input == 'y') {
		continueGame = true;
	}

	return continueGame;
}

void gameLoop(bool& gameOver, player& playerOne, player& playerTwo) {
	for (int i = 0; i < GAME_ROUNDS; i++) {
		cout << "Round " << i + 1 << " -" << endl;
		doOnePlayerRound(playerOne);
		if (playerOne.score >= TARGET_SCORE) {
			gameOver = true;
			playerOne.winner = true;
		}

		doOnePlayerRound(playerTwo);
		if (playerTwo.score >= TARGET_SCORE) {
			gameOver = true;
			playerTwo.winner = true;
		}
		cout << "Player 1 - " << playerOne.score
			<< " Player 2 - " << playerTwo.score;
		cout << endl << endl;
	}

	if (playerOne.score > playerTwo.score) {
		playerOne.winner = true;
	}
	else {
		playerTwo.winner = true;
	}
	gameOver = true;
	
}

void doOnePlayerRound(player& player) {
	int currentScore, totalScore = 0;
	char playerChoice = '\0';
	bool continueRound = true;
	string roundStatus;
	cout << "Player " << player.ID << ": ";

	int roundCount = 0;
	while (continueRound && roundCount < GAME_ROUNDS) {
		currentScore = getDiceRoll();
		cout << currentScore << ' ';

		if (currentScore != 1 && player.score <= 100) {
			totalScore += currentScore;
			playerChoice = _getch();
			if (playerChoice == 'p') {
				continueRound = false;
				roundStatus = "Pass";
			}
			else if (roundCount == (GAME_ROUNDS - 1)) {
				roundStatus = "Max Rolls";
				continueRound = false;
			}
			playerChoice = '\0';
		}
		else if (currentScore == 1) {
			totalScore = 0;
			roundStatus = "Bust!";
			continueRound = false;
		}
		else {
			roundStatus = "Max Rolls";
		}

		roundCount++;
	}

	player.score += totalScore;
	cout << '(' << roundStatus << ", +" << totalScore << ')' << endl;
}

int getDiceRoll() {
	int count = 0, realNum, tempNum;
	realNum = DICE_MIN + (rand() % DICE_MAX);
	while (count < CYCLE_NUM) {
		tempNum = DICE_MIN + (rand() % DICE_MAX);
		cout << tempNum;
		sleep_for(milliseconds(CYCLE_SPEED));
		cout << "\b \b";
		count++;
	}
	
	return realNum;
}

void rulesExplain() {
	cout << "\tWELCOME TO THE DICE GAME OF THE CENTURY!" << endl;
	cout << "Your goal is to get as close to a score of " << TARGET_SCORE 
		<< " as possible in 4 rounds." << endl;
	cout << "However, roll a one (1) and you get no points at all for that round!" << endl;
	cout << "CONTROLS: " << "\n\t Type 'h' to roll another die, 'p' to pass that round." << endl;
	cout << "You go first! Ready? (y/n): ";
}



void announceWinner(player& playerOne, player& playerTwo) {
	int winnerID;
	if (playerOne.score > playerTwo.score) {
		winnerID = playerOne.ID;
	}
	else {
		winnerID = playerTwo.ID;
	}

	cout << "Player 1 score: " << playerOne.score << endl;
	cout << "Player 2 score: " << playerTwo.score << endl;
	cout << endl;
	cout << "Congratulations to Player " << winnerID << '!';
	cout << endl;
}

void seedRand() {
	srand(time(NULL));
}