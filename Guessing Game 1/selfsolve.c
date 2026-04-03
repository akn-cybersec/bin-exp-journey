#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

int main() {
    // We don't call srand(), or we call srand(1), 
    // to match the default state of the game.
    
    printf("Printing the first 50 winning numbers:\n");
    printf("====================================\n");

    for (int i = 1; i <= 50; i++) {
        // This mimics: (rand() % BUFSIZE) + 1
        long val = rand() % BUFSIZE;
        long winning_guess = val + 1;

        printf("Game %02d: %ld\n", i, winning_guess);
    }

    return 0;
}