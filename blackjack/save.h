/*
 * save.h
 *
 *  Created on: Dec 12, 2011
 *      Author: Eli
 */

#ifndef SAVE_H_
#define SAVE_H_

void newPlayer(); //create new player (overwrite previous)
int loadPlayer(); //returns player's chips
void update(int chips); //receives player's chips, writes to save
void printInfo(); //print out personal info


#endif /* SAVE_H_ */
