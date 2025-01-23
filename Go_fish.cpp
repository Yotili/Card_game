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

// Display the hand
void displayHand(Card hand[], int size) {
    for (int i = 0; i < size; i++) {
        cout << hand[i].value << " ";
    }
    cout << endl;
}

// Check if a card exists in the hand
bool hasCard(Card hand[], int size, const string& value) {
    for (int i = 0; i < size; i++) {
        if (hand[i].value == value) {
            return true;
        }
    }
    return false;
}

// Transfer cards between hands
void transferCards(Card from[], int& fromSize, Card to[], int& toSize, const string& value) {
    for (int i = 0; i < fromSize; i++) {
        if (from[i].value == value) {
            to[toSize++] = from[i];
            from[i] = from[--fromSize];
            i--; // Recheck the current index since elements are shifted
        }
    }
}

// Check for a completed set
bool checkForSet(Card hand[], int& handSize, string sets[], int& setSize, bool isPlayer) {
    int counts[13] = { 0 };
    for (int i = 0; i < handSize; i++) {
        for (int j = 0; j < 13; j++) {
            if (hand[i].value == VALUES[j]) {
                counts[j]++;
                break;
            }
        }
    }

    bool foundSet = false;
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 4) {
            sets[setSize++] = VALUES[i];
            if (isPlayer) {
                cout << "You have a full set of " << VALUES[i] << "!" << endl;
                string confirmation;
                do {
                    cout << "Type 'Complete' to acknowledge: ";
                    cin >> confirmation;
                } while (confirmation != "Complete");
            }
            else {
                cout << "The computer completes the set of " << VALUES[i] << "!" << endl;
            }

            for (int j = 0; j < handSize; j++) {
                if (hand[j].value == VALUES[i]) {
                    hand[j] = hand[--handSize];
                    j--; // Recheck the current index
                }
            }
            foundSet = true;
        }
    }
    return foundSet;
}

// Check if a set exists in the player's sets
bool hasSet(const string sets[], int setSize, const string& value) {
    for (int i = 0; i < setSize; i++) {
        if (sets[i] == value) {
            return true;
        }
    }
    return false;
}

