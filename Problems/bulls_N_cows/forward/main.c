#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DIGITS 4
#define TOTAL_COMBINATION 4536
#define CHANCES 8
#define VALID_GUESS 1
#define INVALID_GUESS 0

char *generate_guess(void)
{
    char a,b,c,d;
    char number[DIGITS + 1] = {"0000"};
    int count = 0, index, i;
    char *sequence[TOTAL_COMBINATION] = {'\0'};
    static char* computer_guess = NULL;
    time_t t;

    number[4] = '\0';
    for (a = '1'; a <= '9'; ++a) {
        for (b = '0'; b <= '9'; ++b) {
            if (b == a)
                continue;
            for (c = '0'; c <= '9'; ++c) {
                if (c == a || c == b)
                    continue;
                for (d = '0'; d <= '9'; ++d) {
                    if (d == a || d == b || d == c)
                        continue;
                    number[0] = a; number[1] = b;
                    number[2] = c; number[3] = d;

                    sequence[count] = malloc(sizeof(char) * 4);
                    strcpy(sequence[count], number);
                    ++count;
                }// End of d loop
            }// End of c loop
        } // End of b loop
    }// End of a loop

    // Randomly generate a number between 0 - 4536
    /* Intializes random number generator and generate a random index
       return the number pointing to random index
    */
    srand((unsigned) time(&t));
    computer_guess = sequence[rand() % TOTAL_COMBINATION];

    // free the allocated sequences
    for (i = 0; i < count; ++i)
        free(sequence[i]);

    return computer_guess;

}

int valid_guess(char *guess)
{
    /* It should be a 4 digit number */
    if (strlen(guess) != 4) {
        return INVALID_GUESS;
    }

    /* First digit shouldn't be zero*/
    if (guess[0] == '0') {
        return INVALID_GUESS;
    }

    /* It should be a unique 4 digit number */
    if (
        (guess[0] == guess[1]) || (guess[0] == guess[2]) ||
        (guess[0] == guess[3]) || (guess[1] == guess[2]) ||
        (guess[1] == guess[3]) || (guess[2] == guess[3])
        )
    {
                return INVALID_GUESS;
    }

    return VALID_GUESS;
}

void bulls_N_cows(char *user_guess, char *comp_guess, int *bulls, int *cows)
{
    int i,j;

    if (strcmp(user_guess, comp_guess) == 0) {
        // User guessed correctly
        *bulls = 4;
        *cows = 0;
        return;
    }

    for (i = 0; i < DIGITS; ++i) {
        for (j = 0; j < DIGITS; ++j) {
            if (comp_guess[i] == user_guess[j]) {
                if (i == j)
                    (*bulls)++;
                else
                    (*cows)++;
            }
        }
    }

    return;
}

int main () {

    char *user_guess[5] = {'\0'};
    int tries, bulls = 0, cows = 0;
    char *comp_guess = generate_guess();

    /* User can input their guess. They are given 8 chances.
     * Response will be given as number of cows and bulls
     * The game rules and description are mentioned at
     * https://en.wikipedia.org/wiki/Bulls_and_Cows
     */

    printf("Hi!! .. hope you know the game.\n"
           "Do refer https://en.wikipedia.org/wiki/Bulls_and_Cows for rules and description.\n"
           "You are given 8 chances to guess.\n");

    while (tries < CHANCES) {
        // Get the user input
        printf("\nEnter the User Guess:");
        scanf("%s", user_guess);
        if (!valid_guess(user_guess)) {
            printf("Invalid guess. Do check the rules and give a proper guess.\n");
            goto next_try;
        }

        bulls_N_cows(user_guess, comp_guess, &bulls, &cows);
        if (bulls == 4) {
            printf("Super .. You guess it.\n");
            return 0;
        }
        printf("<Bulls, Cows>: <%d, %d>\n", bulls, cows);

next_try:
        bulls = 0;
        cows = 0;
        tries++;
   }
    printf("He He ... Play Again. I guessed %s\n", comp_guess);
    return 0;
}
