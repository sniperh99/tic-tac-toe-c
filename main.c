#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BOLD  "\x1B[1m"
#define RESET "\x1B[0m"


char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};


void loadingEffect() {
    printf("\nChecking result");

    for(int i = 0; i < 5; i++) {
        printf(".");
        Sleep(300);
    }
    printf("\n");
}


void celebrateWin(int player) {
    printf("\n\n");
    printf(YEL "*********************************\n" RESET);
    printf(GRN "   🎉🎉 PLAYER %d WINS!!! 🎉🎉\n" RESET, player);
    printf(YEL "*********************************\n\n" RESET);

    printf(CYN "   *  *   *  *   *  *   *  *\n");
    printf(" *   *   *   *   *   *   *   *\n");
    printf("   *   *   *   *   *   *   *\n" RESET);

    printf("\a"); // Beep sound
}


void displayBoard() {
    system("cls");

    printf(BOLD YEL "\n\t Tic-Tac-Toe" RESET "\n\n");
    printf(WHT "\t-----------" RESET "\n");

    printf("Player 1 (" RED "X" RESET ") - Player 2 (" CYN "O" RESET ")\n\n\n");

    printf("\t    |    |    \n");
    printf("\t  %s |  %s |  %s \n",
           (board[0][0] == 'X') ? RED "X" RESET : (board[0][0] == 'O') ? CYN "O" RESET : WHT "1" RESET,
           (board[0][1] == 'X') ? RED "X" RESET : (board[0][1] == 'O') ? CYN "O" RESET : WHT "2" RESET,
           (board[0][2] == 'X') ? RED "X" RESET : (board[0][2] == 'O') ? CYN "O" RESET : WHT "3" RESET
    );
    printf("\t____|____|____\n");

    printf("\t    |    |    \n");
    printf("\t  %s |  %s |  %s \n",
           (board[1][0] == 'X') ? RED "X" RESET : (board[1][0] == 'O') ? CYN "O" RESET : WHT "4" RESET,
           (board[1][1] == 'X') ? RED "X" RESET : (board[1][1] == 'O') ? CYN "O" RESET : WHT "5" RESET,
           (board[1][2] == 'X') ? RED "X" RESET : (board[1][2] == 'O') ? CYN "O" RESET : WHT "6" RESET
    );
    printf("\t____|____|____\n");

    printf("\t    |    |    \n");
    printf("\t  %s |  %s |  %s \n",
           (board[2][0] == 'X') ? RED "X" RESET : (board[2][0] == 'O') ? CYN "O" RESET : WHT "7" RESET,
           (board[2][1] == 'X') ? RED "X" RESET : (board[2][1] == 'O') ? CYN "O" RESET : WHT "8" RESET,
           (board[2][2] == 'X') ? RED "X" RESET : (board[2][2] == 'O') ? CYN "O" RESET : WHT "9" RESET
    );
    printf("\t    |    |    \n\n");
}


int checkWinner() {
    for (int i = 0; i < 3; i++) {

        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return 1;

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return 1;
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return 1;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return 1;


    int count = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                count++;
        }
    }

    if (count == 0)
        return 0;

    return -1;
}


void resetBoard() {
    char startValue = '1';

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = startValue++;
        }
    }
}


int main() {
    char playAgain;
    int p1Score = 0, p2Score = 0;

    do {
        resetBoard();

        int player = 1;
        int status = -1;
        int choice;
        char mark;

        while (status == -1) {

            displayBoard();
            printf(GRN " Scores -> Player 1: %d | Player 2: %d\n\n" RESET, p1Score, p2Score);

            player = (player % 2) ? 1 : 2;
            mark   = (player == 1) ? 'X' : 'O';

            printf(CYN "👉 Player %d (%c), enter a number (1-9): " RESET, player, mark);
            scanf("%d", &choice);

            int row = (choice - 1) / 3;
            int col = (choice - 1) % 3;

            if (choice >= 1 && choice <= 9 &&
                board[row][col] != 'X' &&
                board[row][col] != 'O') {

                board[row][col] = mark;

                loadingEffect();  // NEW

                status = checkWinner();

                if (status == -1)
                    player++;

            } else {
                printf("\nInvalid move! Press Enter to try again...");
                getchar();
                getchar();
            }
        }

        displayBoard();

        if (status == 1) {
            celebrateWin(player);   // NEW

            if (player == 1)
                p1Score++;
            else
                p2Score++;

        } else {
            printf(YEL "\n😐 It's a DRAW!\n" RESET);
            printf("\a");
        }

        printf("\nWould you like to play another round? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');


    printf("\n\nFinal Standings -> P1: %d | P2: %d\n", p1Score, p2Score);
    printf("\nThanks for playing!\n");

    return 0;
}
