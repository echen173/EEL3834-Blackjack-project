#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void newPlayer(){ //create new player

	int start = 1000; //new player's starting chips
	ofstream file;
	vector<string> out;
	string nameOut;

		cin.ignore();
		cout << "Type in your name, please. (no spaces): " << endl;
		getline(cin, nameOut, '\n');
		out.push_back(nameOut);
/*
		cout << "The name you input was: ";
		cout << out[0];
		cout << endl;
*/
		file.open("save.txt");
		file << out[0] << endl;
		file << start << endl;
		file.close();
}
int loadPlayer(){ 	//load Existing Player

	ifstream fileIn;
	vector<string> in;
	string readIn;

	//char confirm = 'n';
	int chips, junk;

		fileIn.open("save.txt");
		if(!fileIn.fail()){

			//while(!fileIn.eof() && (confirm == 'n')){
			fileIn >> readIn;

			//cout << "Welcome ";
			//cout << readIn <<"!"<< endl;
			//cout << "Load your chips? 'y' for yes, 'n' to return to menu ";
			//cin >> confirm;

			//if(confirm == 'y'){
				in.push_back(readIn);
				fileIn >> chips;
			//	cout << "Your chips have been loaded\nNumber of chips: " << chips << endl;
			//}
			//else if(confirm == 'n')
			//	fileIn >> junk;
			//}
			fileIn.close();
		}
		else //file failed to open
			cout << "Error! Save file not found!" << endl;
		return chips;
}
void update(int chips){ //update save file
	ifstream fileIn;
	ofstream file;
	vector<string> save;
	string readIn;
	int num;

		//chips = 3000;
		fileIn.open("save.txt");
			if(!fileIn.fail()){
				getline(fileIn, readIn, '\n');
				save.push_back(readIn);
				fileIn >> num;
			fileIn.close();
				//num = chips;
				cout << "\n" << save[0] << "'s" << endl;//print out updated Player and Chips
				cout << "Remaining chips: " << num << '\n' << endl;

		file.open("save.txt");
			file << save[0] << endl;
			file << num << endl;
		file.close();
			}
			else //file failed to open
				cout << "Error! Save file not found!" << endl;
}
