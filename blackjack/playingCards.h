/*
 * playingCards.h
 *
 *  Created on: Nov 19, 2011
 *      Author: Eli
 */

#ifndef PLAYINGCARDS_H_
#define PLAYINGCARDS_H_

class Card{
public:
	int number;
	char suit;
	bool picked;

	void setPicked(){
			picked = 1;
		}

private:
	int getNumber();
	char getSuit();
};

class Hand{
public:
	int size;
	bool bust;
	Card card[10];

	Hand(){
		size = 0;
		bust = 0;
	}

	int sum(){ //check for bust
		int value, ace = 0, sum = 0;
		for (int i = 0; i < size; i++){
			if ((card[i].number == 11) || (card[i].number == 12) || (card[i].number == 13))
				value = 10;
			else
				value = card[i].number;

			if (value == 1){ //account for Ace being 1 or 11
				ace++;
			}

			else
			sum += value;
		}

		sum += (ace*11);
		while(ace){ //Ace can be 1 or 11
			if (sum>21){
				sum -= 10;
			}
			ace--;
		}

		if (sum > 21)
			bust = 1;
		else
			bust = 0;
		return sum;
	}
};

class Deck {
public:
	//int remaining;
	Card card[52];
	Deck(){		//default constructor
		int k = 0;
		for (int i=1; i<=4; i++){   //card suits c(clubs), d(diamond), h(hearts), s(spades)
			for (int j=1; j<=13; j++){  //card values 1 - 13
				card[k].number = j;
				switch(i){
				case 1:
					card[k].suit = 'c';
					break;
				case 2:
					card[k].suit = 'd';
					break;
				case 3:
					card[k].suit = 'h';
					break;
				case 4:
					card[k].suit = 's';
					break;
				}
				card[k].picked = 0; //initialize all cards to "not picked"
				k++;
			}
		}
		//remaining = 52;
	}

	Card hit(){
		int index;
		Card x;

		//if (remaining != 0){
		do{
		index = rand() % 52;
		}while(card[index].picked);

		card[index].setPicked();
		x = card[index];
		//remaining--;
		//}
		return x;
	}

	void shuffle(){
		for (int i = 0; i<52; i++){
			card[i].picked = 0;
		}
	}

	Hand createHand(){
		Hand hand;
		hand.card[0] = hit();
		hand.card[1] = hit();
		hand.size = 2;
		return hand;
	}
};

void printCard(Card card);
void printHand(Hand hand);

#endif /* PLAYINGCARDS_H_ */
