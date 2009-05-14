#include <iostream>
#include <SDL/SDL.h>

using namespace std;
// game includes...
#include "globals.h"

int main(int argc, char* args[]) {
	try {
		
		srand((unsigned)time(0));  // seed for random numbers

		/**********************
		** boring init stuff **
		**********************/

		if (argc > 1) {
			// ooh, got arguments. at the moment we only care about the first one
			if (strcmp(args[1], "--editor") == 0) {
				cout << "Starting editor" << endl;
				return mainEditor(argc, args);
			} else {
				cout << "Unknown argument: " << args[1] << " - skipping..." << endl;
			}
		}

		return mainGame(argc, args);
		
	} catch (...) {
			cout << "Exception occured..." << endl;
			return 1;
	}
}
