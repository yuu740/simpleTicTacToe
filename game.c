#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "game.h"
#include "home.h"

#define BOARD_SIZE 3
char board[BOARD_SIZE][BOARD_SIZE];
char currentPlayer;

void initializeBoard() {
    clearScreen();
    printTitleArt();
    printf("\nInitializing board...\n");
    Sleep(500);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';

            clearScreen();
            printTitleArt();
            printf("\n");

            for (int y = 0; y <= i; y++) {
                for (int x = 0; x < BOARD_SIZE; x++) {
                    if (y < i || (y == i && x <= j)) {
                        setColor(8);
                        printf("   ");
                    } else {
                        printf("   ");
                    }
                    if (x < 2) printf("|");
                }
                printf("\n");
                if (y < BOARD_SIZE - 1) printf("---|---|---\n");
            }
            setColor(7);
            Sleep(80);
        }
    }
    Sleep(300);
}

void drawBoard() {
    clearScreen();
    printTitleArt();
    printf("\n");

    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Sleep(100);

            if (board[i][j] == ' ') {
                setColor(7);
                printf(" %d ", cellNumber);
            } else {
                if (board[i][j] == 'X') setColor(12);
                else setColor(9);
                printf(" %c ", board[i][j]);
            }
            setColor(7);
            if (j < 2) {
                printf("|");
                Sleep(50);
            }
            cellNumber++;
        }
        printf("\n");
        if (i < 2) {
            printf("---|---|---\n");
            Sleep(150);
        }
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            return 1;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            return 1;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        return 1;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        return 1;
    return 0;
}

int checkDraw() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void botEasyMove() {
    int emptyCells[9];
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                emptyCells[count++] = i * 3 + j;
            }
        }
    }
    if (count > 0) {
        int move = emptyCells[rand() % count];
        int row = move / 3;
        int col = move % 3;
        board[row][col] = currentPlayer;
    }
}

void playGame(int vsBot, int difficulty) {
    initializeBoard();
    int cell;
    while (1) {
        drawBoard();
        if (vsBot && currentPlayer == 'O' && difficulty == 1) {
            Sleep(1000);
            botEasyMove();
        } else {
            printf("Player %c, choose cell number (1-9): ", currentPlayer);
            scanf("%d", &cell);
            if (cell < 1 || cell > 9) {
                printf("Invalid cell number! Try again.\n");
                Sleep(1000);
                continue;
            }
            int row = (cell - 1) / 3;
            int col = (cell - 1) % 3;
            if (board[row][col] == ' ') {
                board[row][col] = currentPlayer;
            } else {
                printf("Cell already taken! Try again.\n");
                Sleep(1000);
                continue;
            }
        }
        if (checkWin()) {
            drawBoard();
            winAnimation(currentPlayer);
            break;
        } else if (checkDraw()) {
            drawBoard();
            tieAnimation();
            break;
        }
        switchPlayer();
    }
}

void printLargeText(const char *text[]) {
    clearScreen();
    for (int shift = 20; shift >= 0; shift--) {
        clearScreen();
        for (int s = 0; s < shift; s++) printf("\n");
        setColor(14);
        for (int i = 0; text[i] != NULL; i++) {
            printf("%s\n", text[i]);
        }
        setColor(7);
        Sleep(120);
    }
    Sleep(500);
}

void winAnimation(char winner) {
    const char *winTextX[] = {
        "X WINS!",
        NULL
    };
    const char *winTextO[] = {
        "O WINS!",
        NULL
    };
    if (winner == 'X') {
        printLargeText(winTextX);
    } else {
        printLargeText(winTextO);
    }
}

void tieAnimation() {
    const char *tieText[] = {
        "TIE!!!",
        NULL
    };
    printLargeText(tieText);
}
