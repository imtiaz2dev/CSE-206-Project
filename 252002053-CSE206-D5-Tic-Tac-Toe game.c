#include <stdio.h>
#include <stdlib.h>
struct History {
    int position;
    char player;
    struct History* next;
};
struct Stack {
    int position;
    char player;
    struct Stack* next;
};

void displayBoard(char board[], int tutorial) {
printf("\n");
    if (tutorial) {
        printf("    1   2   3\n");
        printf("  +---+---+---+\n");
        printf("1 | %c | %c | %c |\n", board[0],board[1],board[2]);
        printf("  +---+---+---+\n");
        printf("2 | %c | %c | %c |\n", board[3],board[4],board[5]);
        printf("  +---+---+---+\n");
        printf("3 | %c | %c | %c |\n", board[6],board[7],board[8]);
        printf("  +---+---+---+\n");
} else {
            printf("== TIC-TAC-TOE ==\n");
            printf("\n");

        printf("  +---+---+---+\n");
        printf("  | %c | %c | %c |\n", board[0],board[1],board[2]);
        printf("  +---+---+---+\n");
        printf("  | %c | %c | %c |\n", board[3],board[4],board[5]);
        printf("  +---+---+---+\n");
        printf("  | %c | %c | %c |\n", board[6],board[7],board[8]);
        printf("  +---+---+---+\n");
    }
printf("\n");
}

int checkWin(char board[], char player) {
int win[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
for (int i = 0; i < 8; i++) {
    if (board[win[i][0]] == player &&
        board[win[i][1]] == player &&
board[win[i][2]] == player)
            return 1;
    }
    return 0;
}

void push(struct Stack** top, int position, char player) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    newNode->position = position;
    newNode->player = player;
    newNode->next = *top;
    *top = newNode;
}
int pop(struct Stack** top, int* position, char* player) {
    if (*top == NULL) return 0;
    struct Stack* temp = *top;
    *position = temp->position;
*player = temp->player;
    *top = temp->next;
    free(temp);
    return 1;
}
void addHistory(struct History** head, struct History** tail, int position, char player) {
    struct History* newNode = (struct History*)malloc(sizeof(struct History));
  newNode->position = position;
    newNode->player = player;
 newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}
void removeHistory(struct History** head, struct History** tail) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        *tail = NULL;
    return;
    }
    struct History* temp = *head;
while (temp->next->next != NULL)
        temp = temp->next;
 free(temp->next);
    temp->next = NULL;
    *tail = temp;
}

void showHistory(struct History* head, char p1[], char p2[]) {
    int move = 1;
    printf("\nGame History\n------------\n");
    if (head == NULL) {
        printf("No moves yet.\n");
        return;
    }
while (head != NULL) {
        char* currentName = (head->player == 'X') ? p1 : p2;
        printf("%d. %s (%c) -> Cell %d\n", move, currentName, head->player, head->position + 1);
        head = head->next;
        move++;
    }
}
void showTutorial() {
    system("cls");
    printf("\n  TUTORIAL MODE         \n");
    printf("  +---+---+---+\n");
    printf("  | 1 | 2 | 3 |\n");
    printf("  +---+---+---+\n");
    printf("  | 4 | 5 | 6 |\n");
    printf("  +---+---+---+\n");
    printf("  | 7 | 8 | 9 |\n");
    printf("  +---+---+---+\n\n");
    printf("1-9 : Start Game\n");
    printf("U   : Undo\n");
    printf("H   : History\n");
    printf("T   : Tutorial Mode\n");
    printf("E   : Exit game\n\n");
    printf("X and O take turns.\n");
    printf("Get 3 symbols in a row to win.\n\n");
    printf("Press Enter to return.");
    getchar();
    getchar();
}
int main() {
    char board[9];
    struct Stack* top;
    struct History* head;
    struct History* tail;
    char input, currentPlayer;
    int choice, position, moves, tutorial = 0;
    char player1[50], player2[50];

system("cls");
    printf("=== TIC-TAC-TOE ===\n");
    printf("Enter Player 1 (X) Name: ");
    scanf("%s", player1);
    printf("Enter Player 2 (O) Name: ");
    scanf("%s", player2);

while (1) {
        for (int i = 0; i < 9; i++) board[i] = ' ';
        top = NULL;
    head = NULL;
        tail = NULL;
        moves = 0;
    currentPlayer = 'X';
while (1) {
    system("cls");
            displayBoard(board, tutorial);
            printf("1-9 : Play\n");
            printf("U   : Undo\n");
            printf("H   : History\n");
            printf("T   : Tutorial\n");
            printf("E   : Exit\n");
    char* activeName = (currentPlayer == 'X') ? player1 : player2;
            printf("\nCurrent Turn: %s (%c)", activeName, currentPlayer);
            printf("\nEnter choice: ");
            scanf(" %c", &input);

    if (input == 'E' || input == 'e') return 0;
    if (input == 'T' || input == 't') {
                showTutorial();
                continue;
            }
if (input == 'H' || input == 'h') {
                system("cls");
                displayBoard(board, tutorial);
                showHistory(head, player1, player2);
                printf("\nPress Enter to start");
                getchar();
                getchar();
                continue;
            }
if (input == 'U' || input == 'u') {
            if (pop(&top, &position, &currentPlayer)) {
                    board[position] = ' ';
                    removeHistory(&head, &tail);
                    moves--;
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    printf("\nLast move undone.");
                } else {
                    printf("\nNothing to undo.");
                }
                printf("\nPress Enter to start");
                getchar();
                getchar();
                continue;
            }
        if (input >= '1'&& input <= '9') {
                choice = input - '0';
                position = choice - 1;

                if (board[position] == 'X' || board[position] == 'O') {
                    printf("\nCell already occupied.");
                    printf("\nPress Enter to Start");
                    getchar();
                    getchar();
                    continue;
                }
board[position] = currentPlayer;
                push(&top, position,currentPlayer);
                addHistory(&head, &tail, position, currentPlayer);
                moves++;

                if (checkWin(board, currentPlayer)) {
                    system("cls");
                    displayBoard(board, tutorial);
                    char* winnerName = (currentPlayer == 'X') ? player1 : player2;
                    printf("Congratulations! %s (%c) wins!\n", winnerName, currentPlayer);
                    break;
                }
                if (moves == 9) {
                    system("cls");
                    displayBoard(board, tutorial);
                    printf("Game Draw!\n");
                    break;
                }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                continue;
            }
            printf("\nInvalid choice.");
            printf("\nUse 1-9, U, H, T or E.");
            printf("\nPress Enter to Start");
            getchar();
            getchar();
        }
while (1) {
            printf("\n");
            printf("N. New Game\n");
            printf("H. History\n");
            printf("E. Exit\n");
            printf("\nEnter choice: ");
            scanf(" %c", &input);
if (input == 'N' || input == 'n') break;
    if (input == 'H' || input == 'h') {
                system("cls");
                displayBoard(board, tutorial);
                showHistory(head, player1, player2);
                printf("\nPress Enter to Start");
                getchar();
                getchar();
                continue;
            }
  if (input == 'E' || input == 'e') return 0;

            printf("\nInvalid choice.");
            printf("\nUse N, H or E.");
            printf("\nPress Enter to Start Again");
            getchar();
            getchar();
        }
    }
}
