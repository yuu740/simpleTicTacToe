#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "home.h"
#include "multiplayer.h"

#define BOARD_SIZE 3
char board[BOARD_SIZE][BOARD_SIZE];
char currentPlayer;

static void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
    currentPlayer = 'X';
}

static void drawBoard() {
    clearScreen();
    printTitleArt();
    printf("\n");
    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                setColor(7);
                printf(" %d ", cellNumber);
            } else {
                if (board[i][j] == 'X') setColor(12);
                else setColor(9);
                printf(" %c ", board[i][j]);
            }
            setColor(7);
            if (j < 2) printf("|");
            cellNumber++;
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}


static int checkWin() {
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

static int checkDraw() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

static void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void playMultiplayer() {
    initializeBoard();
    int cell;
    while (1) {
        drawBoard();
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
        if (checkWin()) {
            drawBoard();
            printf("\nPlayer %c Wins!\n", currentPlayer);
            Sleep(1500);
            break;
        } else if (checkDraw()) {
            drawBoard();
            printf("It's a tie!\n");
            Sleep(1500);
            break;
        }
        switchPlayer();
    }
}
