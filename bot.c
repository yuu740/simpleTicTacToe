#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "home.h"
#include "bot.h"

#define BOARD_SIZE 3
char boardBot[BOARD_SIZE][BOARD_SIZE];
char currentPlayerBot;

static void initializeBoardBot() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            boardBot[i][j] = ' ';
    currentPlayerBot = 'X';
}

static void drawBoardBot() {
    clearScreen();
    printTitleArt();
    printf("\n");
    int cellNumber = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardBot[i][j] == ' ') {
                printf(" %d ", cellNumber);
            } else {
                printf(" %c ", boardBot[i][j]);
            }
            if (j < 2) printf("|");
            cellNumber++;
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

static int checkWinBot() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (boardBot[i][0] == currentPlayerBot && boardBot[i][1] == currentPlayerBot && boardBot[i][2] == currentPlayerBot)
            return 1;
        if (boardBot[0][i] == currentPlayerBot && boardBot[1][i] == currentPlayerBot && boardBot[2][i] == currentPlayerBot)
            return 1;
    }
    if (boardBot[0][0] == currentPlayerBot && boardBot[1][1] == currentPlayerBot && boardBot[2][2] == currentPlayerBot)
        return 1;
    if (boardBot[0][2] == currentPlayerBot && boardBot[1][1] == currentPlayerBot && boardBot[2][0] == currentPlayerBot)
        return 1;
    return 0;
}

static int checkDrawBot() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (boardBot[i][j] == ' ')
                return 0;
    return 1;
}

static void switchPlayerBot() {
    currentPlayerBot = (currentPlayerBot == 'X') ? 'O' : 'X';
}

static void botEasyMove() {
    int emptyCells[9];
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boardBot[i][j] == ' ') {
                emptyCells[count++] = i * 3 + j;
            }
        }
    }
    if (count > 0) {
        int move = emptyCells[rand() % count];
        int row = move / 3;
        int col = move % 3;
        boardBot[row][col] = currentPlayerBot;
    }
}

static void botMediumMove() {
    // Check blocking first
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        if (boardBot[row][col] == ' ') {
            boardBot[row][col] = 'X';
            if (checkWinBot()) {
                boardBot[row][col] = currentPlayerBot;
                return;
            }
            boardBot[row][col] = ' ';
        }
    }
    botEasyMove();
}

static int minimax(int isMaximizing) {
    if (checkWinBot()) return isMaximizing ? -1 : 1;
    if (checkDrawBot()) return 0;
    int bestScore = isMaximizing ? -100 : 100;
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        if (boardBot[row][col] == ' ') {
            boardBot[row][col] = isMaximizing ? 'O' : 'X';
            int score = minimax(!isMaximizing);
            boardBot[row][col] = ' ';
            bestScore = isMaximizing ? (score > bestScore ? score : bestScore)
                                     : (score < bestScore ? score : bestScore);
        }
    }
    return bestScore;
}

static void botHardMove() {
    int bestScore = -100;
    int move = -1;
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        if (boardBot[row][col] == ' ') {
            boardBot[row][col] = 'O';
            int score = minimax(0);
            boardBot[row][col] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    if (move != -1) {
        int row = move / 3;
        int col = move % 3;
        boardBot[row][col] = currentPlayerBot;
    }
}

void playBot(int difficulty) {
    initializeBoardBot();
    int cell;
    while (1) {
        drawBoardBot();
        if (currentPlayerBot == 'O') {
            Sleep(500);
            if (difficulty == 1) {
                botEasyMove();
            } else if (difficulty == 2) {
                botMediumMove();
            } else {
                botHardMove();
            }
        } else {
            printf("Player %c, choose cell number (1-9): ", currentPlayerBot);
            scanf("%d", &cell);
            if (cell < 1 || cell > 9) {
                printf("Invalid cell number! Try again.\n");
                Sleep(1000);
                continue;
            }
            int row = (cell - 1) / 3;
            int col = (cell - 1) % 3;
            if (boardBot[row][col] == ' ') {
                boardBot[row][col] = currentPlayerBot;
            } else {
                printf("Cell already taken! Try again.\n");
                Sleep(1000);
                continue;
            }
        }
        if (checkWinBot()) {
            drawBoardBot();
            printf("\nPlayer %c Wins!\n", currentPlayerBot);
            Sleep(1500);
            break;
        } else if (checkDrawBot()) {
            drawBoardBot();
            printf("It's a tie!\n");
            Sleep(1500);
            break;
        }
        switchPlayerBot();
    }
}

