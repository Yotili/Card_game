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

// Shuffle the deck
void shuffleDeck(Card deck[]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        int r = rand() % DECK_SIZE;
        swap(deck[i], deck[r]);
    }
}

// Deal cards
void dealCards(Card deck[], Card hand[], int& deckIndex, int handSize) {
    for (int i = 0; i < handSize; i++) {
        hand[i] = deck[deckIndex++];
    }
}

