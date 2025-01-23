#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int DECK_SIZE = 52;
const int HAND_SIZE = 6;
const string VALUES[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

// Card structure
struct Card {
    string value;
};

// Initialize the deck
void initializeDeck(Card deck[]) {
    int index = 0;
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[index++].value = VALUES[i];
        }
    }
}