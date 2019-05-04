#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 4
#define TOTAL_COMBINATION 4536
#define CHANCES 8

struct node {
    char number[DIGITS + 1];
    struct node *next;
};

struct node* create_list(char *num)
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    if (head == NULL) {
        printf("Unable to allocate memory for HEAD.\n");
        exit(1);
    }

    strcpy(head->number, num);
    head->number[DIGITS] = '\0';
    head->next = NULL;

    return head;
}

void append_to_tail(struct node *head, char *num)
{
    struct node *prev_node = head;
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Unable to allocate memory for new_node.\n");
        exit(1);
    }

    while (prev_node->next != NULL) {
        prev_node = prev_node->next;
    }
    prev_node->next = new_node;

    strcpy(new_node->number, num);
    new_node->number[DIGITS] = '\0';
    new_node->next = NULL;

    return;
}

struct node *generate_combination(void)
{
    char a,b,c,d;
    char number[DIGITS + 1] = {"0000"};
    struct node *head = NULL;
    int count = 0;


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

                    if (head == NULL) {
                        head = create_list(number);
                    } else {
                        append_to_tail(head, number);
                    }
                    ++count;
                }// End of d loop
            }// End of c loop
        } // End of b loop
    }// End of a loop

    return head;
}

int match(char *guess, char *number, int usr_bulls, int usr_cows)
{
    int i, j,
        bulls = 0, cows = 0;

   // Get the bulls and cows
    for (i = 0; i < DIGITS; ++i) {
        for (j = 0; j < DIGITS; ++j)
            if (number[i] == guess[j]) {
                if (i == j) {
                    ++bulls;
                } else  {
                    ++cows;
                }
            }
    }

    if ((bulls == usr_bulls) && (cows == usr_cows)) {
        return 1;
    } else {
        return 0;
    }
}

struct node *update_list(struct node *head, char *guess, int usr_bulls, int usr_cows)
{
    struct node *present_node = head;
    struct node *prev_node = head;

    // iterate through list and remove nodes that
    // don't match the bulls and cows given by user.

    while (present_node) {
        if ( !match(guess, present_node->number, usr_bulls, usr_cows) ) {
            //present_node = present_node->next;
            // remove the node and continue
            if (present_node == head) {
                head = head->next;
                free(present_node);
                present_node = head;
                prev_node = head;
            } else {
                present_node = present_node->next;
                free(prev_node->next);
                prev_node->next = present_node;
            }
        } else {
            //printf("match-%s\n", present_node->number);
            prev_node = present_node;
            present_node = present_node->next;
        }

    } // end of while

    return head;
}

int main()
{
    struct node *head = NULL, *present_node = NULL;
    char response;
    char my_guess[5] = {'\0'};
    int tries = 0, bulls, cows;

    head = generate_combination();
    present_node = head;

    printf("Hi!! .. hope you know the game.\n"
           "Do refer https://en.wikipedia.org/wiki/Bulls_and_Cows for rules and description.\n"
           "I shall guess the unique number, within 8 chances.\n");

    printf("\n\nAre you ready with a Unique 4 digit number.\n"
           "Enter 'Y or 'y' for YES:");
    scanf("%c", &response);
    if (response == 'Y' || response == 'y') {
        printf("Great.., let's begin.\n");
    } else {
        printf("Start over when ready..\n");
    }


    while ((tries <= CHANCES) && present_node) {
        ++tries;

        // Get the first number from the list
        present_node = head;
        strcpy(my_guess, head->number);
        printf("<%s>:", my_guess);
        scanf("%d, %d", &bulls, &cows);
        if (bulls == 4) {
            printf(".. He he he ...\n.. I Win ... try Again to defeat me.\n");
            exit(0);
        }

        // Re-arrange the struct based on present bulls and cows response;
        head = update_list(head, my_guess, bulls, cows);

    }

    printf("Ok you win ....\n"
           "Did u cheat or gave wrong information.\n");
    return 0;
}
