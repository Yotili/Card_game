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

// Validate if a card name is valid
bool isValidCard(const string& value) {
    for (const string& card : VALUES) {
        if (card == value) {
            return true;
        }
    }
    return false;
}

// Main program
int main() {
    srand(time(0));

    Card deck[DECK_SIZE];
    Card playerHand[DECK_SIZE];
    Card computerHand[DECK_SIZE];
    string playerSets[13], computerSets[13];
    int deckIndex = 0, playerHandSize = HAND_SIZE, computerHandSize = HAND_SIZE;
    int playerSetSize = 0, computerSetSize = 0;

    initializeDeck(deck);
    shuffleDeck(deck);

    // Deal cards
    dealCards(deck, playerHand, deckIndex, HAND_SIZE);
    dealCards(deck, computerHand, deckIndex, HAND_SIZE);

    bool isPlayerTurn = true;

    // First phase of the game
    while (deckIndex < DECK_SIZE || playerHandSize > 0 || computerHandSize > 0) {
        bool repeatTurn = true;

        while (repeatTurn) {
            if (playerSetSize == 13 || computerSetSize == 13) {
                break;
            }
            repeatTurn = false;

            if (isPlayerTurn) {
                if (playerHandSize == 0 && deckIndex < DECK_SIZE) {
                    playerHand[playerHandSize++] = deck[deckIndex++];
                    cout << "Player had no cards and drew a card from the deck." << endl;
                }

                if (playerHandSize == 0) break;

                cout << endl << "Your cards: ";
                displayHand(playerHand, playerHandSize);

                string ask;
                do {
                    cout << "Which card do you want to ask for? ";
                    cin >> ask;
                    if (!isValidCard(ask)) {
                        cout << "Invalid input. Please enter a valid card name (e.g., Ace, King, etc.)." << endl;
                    }
                } while (!isValidCard(ask) || !hasCard(playerHand, playerHandSize, ask));

                if (hasCard(computerHand, computerHandSize, ask)) {
                    cout << "The computer has cards of " << ask << "!" << endl;
                    transferCards(computerHand, computerHandSize, playerHand, playerHandSize, ask);
                    repeatTurn = true;
                }
                else {
                    cout << "The computer does not have cards of " << ask << ". You draw a card." << endl;
                    string drawCommand;
                    do {
                        cout << "Type 'Draw' to proceed: ";
                        cin >> drawCommand;
                    } while (drawCommand != "Draw");
                    if (deckIndex < DECK_SIZE) {
                        Card drawnCard = deck[deckIndex++];
                        playerHand[playerHandSize++] = drawnCard;
                        cout << "You drew a card: " << drawnCard.value << endl;
                        if (drawnCard.value == ask) {
                            cout << "You drew " << ask << "! You can continue." << endl;
                            repeatTurn = true;
                        }
                    }
                }

                checkForSet(playerHand, playerHandSize, playerSets, playerSetSize, true);
            }
            else {
                if (computerHandSize == 0 && deckIndex < DECK_SIZE) {
                    computerHand[computerHandSize++] = deck[deckIndex++];
                    cout << "Computer had no cards and drew a card from the deck." << endl;
                }

                if (computerHandSize == 0) break;

                string ask = computerHand[rand() % computerHandSize].value;
                cout << "The computer asks for " << ask << "." << endl;

                if (hasCard(playerHand, playerHandSize, ask)) {
                    cout << "You give the cards of " << ask << " to the computer." << endl;
                    transferCards(playerHand, playerHandSize, computerHand, computerHandSize, ask);
                    repeatTurn = true;
                }
                else {
                    cout << "You do not have cards of " << ask << ". The computer draws a card." << endl;
                    if (deckIndex < DECK_SIZE) {
                        Card drawnCard = deck[deckIndex++];
                        computerHand[computerHandSize++] = drawnCard;
                        if (drawnCard.value == ask) {
                            cout << "The computer drew " << ask << " and continues." << endl;
                            repeatTurn = true;
                        }
                    }
                }

                checkForSet(computerHand, computerHandSize, computerSets, computerSetSize, false);
            }
        }

        isPlayerTurn = !isPlayerTurn;
    }

    // Start second phase
    cout << "The first phase is over. Starting the second phase!" << endl;

    while (true) {
        // Clarify that this loop handles the second phase of the game, where players request sets until one player wins.
        if (playerSetSize == 13 || computerSetSize == 13) {
            break; // End the game if one player has all 13 sets
        }

        bool repeatTurn = true;

        while (repeatTurn) {
            repeatTurn = false;

            if (playerSetSize == 13 || computerSetSize == 13) {
                break; // End the game if one player has all 13 sets
            }

            if (isPlayerTurn) {
                string ask;
                do {
                    cout << endl << "Your turn! Which set do you want to ask for? ";
                    cin >> ask;
                    if (!isValidCard(ask)) {
                        cout << "Invalid input. Please enter a valid set name (e.g., Ace, King, etc.)." << endl;
                    }
                } while (!isValidCard(ask));

                if (hasSet(computerSets, computerSetSize, ask)) {
                    cout << "The computer gives you the set of " << ask << "!" << endl;
                    playerSets[playerSetSize++] = ask;

                    for (int i = 0; i < computerSetSize; i++) {
                        if (computerSets[i] == ask) {
                            computerSets[i] = computerSets[--computerSetSize];
                            break;
                        }
                    }

                    repeatTurn = true;
                }
                else {
                    cout << "The computer does not have the set of " << ask << "." << endl;
                }
            }
            else {
                string ask;
                do {
                    ask = VALUES[rand() % 13];
                } while (!isValidCard(ask));

                cout << endl << "The computer asks for the set of " << ask << "." << endl;

                if (hasSet(playerSets, playerSetSize, ask)) {
                    cout << "You give the computer the set of " << ask << "!" << endl;
                    computerSets[computerSetSize++] = ask;

                    for (int i = 0; i < playerSetSize; i++) {
                        if (playerSets[i] == ask) {
                            playerSets[i] = playerSets[--playerSetSize];
                            break;
                        }
                    }

                    repeatTurn = true;
                }
                else {
                    cout << "You do not have the set of " << ask << "." << endl;
                }
            }
        }

        isPlayerTurn = !isPlayerTurn;
    }

    // End game
    cout << "The game is over!" << endl;
    cout << "Your sets: " << playerSetSize << endl;
    cout << "Computer's sets: " << computerSetSize << endl;

    if (playerSetSize > computerSetSize) {
        cout << "You win!" << endl;
    }
    else {
        cout << "The computer wins!" << endl;
    }

    return 0;
}