/*
 * blackjack.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: Eli
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "playingCards.h"
using namespace std;

void game();
void instruction();

int main(){
	int entry;
	bool play = 1;
	srand(static_cast<unsigned int>(time(0))); //use time for RNG seed value

	cout << "Welcome to Blackjack." << endl;
	do{
	cout << "Press 1 to play" << endl;
	cout << "Press 2 to read instructions" << endl;
	cout << "Press 3 to quit" << endl;
	cin >> entry;

	if (cin.fail()){
		cout << "Invalid selection" << endl;
		cin.clear();
		cin.ignore();
	}

	else {
	switch(entry){
		case 1:
			game();
			cout << "\nWelcome back." << endl;
			break;
		case 2:
			instruction();
			break;
		case 3:
			play = 0;
			cout << "Thanks for playing!";
			break;
		default:
			cout << "Invalid selection. Try again." << endl;
			break;
		}
	}
	}while(play);


	return 0;
}

void game(){
	Deck deck;
	Hand player1, house;
	int entry, Psum, Hsum;
	bool stop = 0;

	player1 = deck.createHand();
	house = deck.createHand();

	cout << "\n**********\nDEALER \nHand: ? ";
	printCard(house.card[1]);

	cout << "\n\n**********\nPLAYER" << endl;
	printHand(player1);
	int index = 2;
	do{ //player's turn
	cout << "\n\nPress 1 to hit" << endl;
	cout << "Press 2 to stay" << endl;
	cin >> entry;

	if (cin.fail()){
		cout << "Invalid selection" << endl;
		cin.clear();
		cin.ignore();
	}

	else {
	switch(entry){
		case 1:
			player1.card[index] = deck.hit();
			player1.size++;
			index++;
			printHand(player1);
			Psum = player1.sum(); //check if bust and return sum
			cout << "\nPlayer sum: " << Psum << endl;
			break;
		case 2:
			printHand(player1);
			Psum = player1.sum(); //check if bust and return sum
			cout << "\nPlayer sum: " << Psum << endl;
			stop = 1;
			break;
		default:
			cout << "Invalid selection. Try again." << endl;
			break;
		}
	}
	}while((!player1.bust) && (!stop));

	if (player1.bust){
		cout << "\nYou busted! \nDealer wins!" << endl;
	}

	else { //computer's turn
		stop = 0;
		index = 2;
		Hsum = house.sum();
		cout << "\n**********\nDEALER" <<endl;

		while((Hsum < 17) && (!house.bust)){
				printHand(house);
				cout << "\nDealer sum: " << Hsum << endl;
				cout << "\nDealer will hit." << endl;
				house.card[index] = deck.hit();
				house.size++;
				index++;
				Hsum = house.sum(); //check if bust and return sum
		}

		printHand(house);
		cout << "\nDealer sum: " << Hsum << endl;

		if(!house.bust){
			cout << "\nDealer will stay." << endl;

		if ((!house.bust) && ((Hsum > Psum) || (player1.bust)))
			cout << "\nDealer wins!"<< endl;
		else if (Hsum == Psum)
			cout << "\nIt's a tie!"<< endl;
		else
			cout << "\nYou win!"<< endl;
		}
		else
			cout << "\nDealer busts. \nYou win!" << endl;
	}

	/*
	cout << "\nRemaining cards in deck: " << endl;

	for (int i = 0; i < 52; i++){ //for debugging: test if cards are taken out of deck
		if (deck.card[i].picked == 0)
		printCard(deck.card[i]);
	}
	*/

}

void instruction(){

}
