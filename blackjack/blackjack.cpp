/*
 * blackjack.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: Eli
 */

//write in checks for when chips are zero
//consider improving code by using more functions
//make printMenu /pseudo-gui
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "playingCards.h"
#include "save.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void game();
void instruction();

int main(){
	int entry, chips;
	char check;
	bool play = 1;
	srand(static_cast<unsigned int>(time(0))); //use time for RNG seed value
	ifstream newFile;

	cout << "Welcome to Blackjack.\n" << endl;
	newFile.open("save.txt");

	if(newFile.fail()){ //runs if first time playing
		cout << "Hi! I noticed this is your first time playing. Please create a save file! <Press Enter>" << endl;
		newPlayer();
	}

	do{
	cout << "Press 1 to start playing!" << endl;
	cout << "Press 2 to read the instructions" << endl;
	cout << "Press 3 to reset save\n\t (Great for if you go broke!)" << endl;
	cout << "Press 4 to quit" << endl;
	cin >> entry;

	if (cin.fail()){
		cout << "Invalid selection" << endl;
		cin.clear();
		cin.ignore();
	}
	else {

	switch(entry){
		case 1:
			chips = loadPlayer();
			cout << "\nYour chips have been loaded\nNumber of chips: " << chips << endl;
			if(chips==0)
				cout << "Oh no! You're out of chips! Please create a new save and start over." << endl;
			else{
			game();
			cout << "\nWelcome back." << endl;
			}
			break;
		case 2:
			instruction();
			break;
		case 3:
			cout << "Are you sure you want to create a new save? (Previous save will be overwritten)\nY/N: ";
			cin >> check;
			if(check == 'y' || check == 'Y')
			newPlayer();
			break;
		case 4:
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
	int contin = 1, chips, betselect, bet, entry, Psum = 0, Hsum = 0;
	bool stop, s_flag, f_flag;

	while(contin){
	deck.shuffle();
	int index = 2;
	s_flag = 0; //surrender flag
	f_flag = 1; //first action flag
	stop = 0;

	printInfo();
	chips = loadPlayer();


	cout << "\n\nPlace your bet:\n\nPress <1 for $10> <2 for $20> <3 for $50> "
					"\n\t<4 for $100> <5 for ALL IN>: "; 								//betting phase
			cin >> betselect;
			if (!cin.fail()){
				switch(betselect){ //finishing betting phase
				case 1:
					bet = 10;
					break;
				case 2:
					bet = 20;
					break;
				case 3:
					bet = 50;
					break;
				case 4:
					bet = 100;
					break;
				case 5:
					bet = chips;
					break;
				default:
					cout << "Invalid selection. Bet defaulted to $5." << endl;
					bet = 5;
					break;
				}
			}
			else {
					cout << "Invalid selection. Bet defaulted to $5." << endl;
					bet = 5;
					cin.clear();
					cin.ignore();
				}

		if (bet > chips) //check for enough chips
			cout << "\nYou don't have enough chips for that! Reset your save if you need to." << endl;
		else{

	player1 = deck.createHand();
	house = deck.createHand();

	cout << "\n**********\nDEALER \nHand: ? ";
	printCard(house.card[1]);

	cout << "\n\n**********\nPLAYER" << endl;
	printHand(player1);

do{ //player's turn

			cout << "\n\nPress <1 to Hit> <2 to Stay>";
			if(f_flag)
				cout << "<3 to Surrender> <4 to Double Down>: " << endl;
			else
				cout << ": "<< endl;

			cin >> entry;


		if (cin.fail()){
			cout << "Invalid selection" << endl;
			cin.clear();
			cin.ignore();
		}
		else {
			switch(entry){
			case 1://Hit
				f_flag = 0;
				player1.card[index] = deck.hit(); //Hit routine
				player1.size++;
				index++;
				printHand(player1);
				Psum = player1.sum(); //check if bust and return sum
				cout << "\nPlayer sum: " << Psum << endl;
				break;
			case 2://Stay
				printHand(player1);
				Psum = player1.sum(); //check if bust and return sum
				cout << "\nPlayer sum: " << Psum << endl;
				stop = 1;
				break;
			case 3: //Surrender
				if(f_flag){
				s_flag = 1;
				stop = 1;
				}
				else{ //Stay routine
					cout << "Invalid selection. \nDefaulted to 'Stay'." << endl;
					printHand(player1);
									Psum = player1.sum(); //check if bust and return sum
									cout << "\nPlayer sum: " << Psum << endl;
									stop = 1;
				}
				break;
			case 4: //Double Down
				if((f_flag) && !((bet*2)>chips)){
				bet *= 2;
				stop = 1;
				player1.card[index] = deck.hit(); //Hit routine
								player1.size++;
								index++;
								printHand(player1);
								Psum = player1.sum(); //check if bust and return sum
								cout << "\nPlayer sum: " << Psum << endl;
				}
				else { //Stay routine
					if((bet*2)>chips)  //message for not enough chips to double down
						cout << "You don't have enough chips for that!" << endl;

					cout << "Invalid selection. \nDefaulted to 'Stay'." << endl;
					printHand(player1);
									Psum = player1.sum(); //check if bust and return sum
									cout << "\nPlayer sum: " << Psum << endl;
									stop = 1;
				}
				break;
			default:
				cout << "Invalid selection. \nDefaulted to 'Stay'." << endl;
				printHand(player1); //Stay routine
								Psum = player1.sum(); //check if bust and return sum
								cout << "\nPlayer sum: " << Psum << endl;
								stop = 1;
				break;
				}
			}
		}while((!player1.bust) && (!stop));

	if(!s_flag){//Surrender flag not set
		if (player1.bust){ 											 //LOSS
			cout << "\nYou busted! \nDealer wins!" << endl;
			chips -= bet;
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

				if ((!house.bust) && ((Hsum > Psum) || (player1.bust))){ //LOSS
					cout << "\nDealer wins!"<< endl;
					chips -= bet;
				}
				else if (Hsum == Psum){									//TIE
					cout << "\nIt's a tie!"<< endl;
				}
				else{													//WIN
					cout << "\nYou win!"<< endl;
					chips += bet;
				}
			}
			else{														//WIN
				cout << "\nDealer busts. \nYou win!" << endl;
				chips += bet;
			}
		}
	}

	else { //Surrender flag is set
		cout << "\nYou surrendered." << endl;
		chips -= ((float)bet/2);
		}
	}

update(chips); //update player's chips into save file after a hand

cout << "Would you like to continue? <1 for yes> <0 for no> : ";
cin >> contin;

if (cin.fail()){
	cout << "Invalid selection" << endl;
	contin = 0;
	cin.clear();
	cin.ignore();
	}
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

