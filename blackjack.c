#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 12
#define MAX_HAND 10

// Cards representation
char *values[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "J", "Q", "K"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clovers"};

// Structure for a card
struct card {
    char *value;
    char *suit;
    int numericValue;
};

struct card deck[TOTAL_CARDS];
struct card playerHand[MAX_HAND];
int numPlayerCards = 0;
int playerSum = 0;
char choice;

void initializeDeck() {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];
        deck[i].numericValue = (i % CARD_VALUES) + 1;
        if (deck[i].numericValue > 10) {
            deck[i].numericValue = 10;
        } 
        if (i % CARD_VALUES == CARD_VALUES - 1) {
            deck[i].numericValue = 11;
        }
    }    
}

void shuffleDeck() {
    srand(time(NULL));
    for (int i = TOTAL_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void showCard(struct card c) {
    printf("  %s of %s\n", c.value, c.suit);
}

int sumHand(struct card hand[], int numCards) {
    int sum = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; i++) {
        sum += hand[i].numericValue;

        // Contar los As por separado
        if (hand[i].numericValue == 11) {
            numAces++;
        }
    }

    // Ajustar por los As para evitar pasarse
    while (sum > 21 && numAces > 0) {
        sum -= 10;  // Tratar el As como 1 en lugar de 11
        numAces--;
    }

    return sum;
}


int main() {
    initializeDeck();
    shuffleDeck();

    printf("Welcome to Blackjack!\n");

    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];
    playerSum = sumHand(playerHand, numPlayerCards);

    printf("Your cards:\n");
    showCard(playerHand[0]);
    showCard(playerHand[1]);
    printf("Total Amount: %d\n", playerSum);

    while (playerSum < 21) {
        printf("Do you want another card? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            playerHand[numPlayerCards] = deck[numPlayerCards + 1];
            playerSum = sumHand(playerHand, ++numPlayerCards);

            printf("New card:\n");
            showCard(playerHand[numPlayerCards - 1]);
            printf("Total Amount: %d\n", playerSum);
        } else {
            break;
        }
    }

    if (playerSum == 21) {
        printf("Blackjack! You win.\n");
    } else if (playerSum > 21) {
        printf("You have passed. Game Over.\n");
    } else {
        printf("You have stood with %d. Game Over.\n", playerSum);
    }

    return 0;
}