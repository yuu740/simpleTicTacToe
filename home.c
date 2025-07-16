#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "home.h"
#include "multiplayer.h"
#include "bot.h"

#define WIDTH 30
#define HEIGHT 15
#define MAX_SYMBOLS 10

typedef struct {
    int x, y;
    char symbol;
    int dx, dy;
} Symbol;

HANDLE hConsole;

void clearScreen() {
    COORD topLeft = {0, 0};
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD length;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    length = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', length, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft);
}

static void moveSymbols(Symbol symbols[], int count) {
    for (int i = 0; i < count; i++) {
        symbols[i].x += symbols[i].dx;
        symbols[i].y += symbols[i].dy;

        if (symbols[i].x <= 0 || symbols[i].x >= WIDTH - 1) symbols[i].dx *= -1;
        if (symbols[i].y <= 0 || symbols[i].y >= HEIGHT - 1) symbols[i].dy *= -1;
    }
}

static void drawSymbols(Symbol symbols[], int count) {
    clearScreen();
    for (int i = 0; i < count; i++) {
        COORD pos = {symbols[i].x, symbols[i].y};
        SetConsoleCursorPosition(hConsole, pos);

        if (symbols[i].symbol == 'X') {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        } else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }

        printf("%c", symbols[i].symbol);
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void showHomeScreen() {
    Symbol symbols[MAX_SYMBOLS];
    srand((unsigned int)time(NULL));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        symbols[i].x = rand() % WIDTH;
        symbols[i].y = rand() % HEIGHT;
        symbols[i].symbol = (i % 2 == 0) ? 'X' : 'O';
        symbols[i].dx = (rand() % 2 == 0) ? 1 : -1;
        symbols[i].dy = (rand() % 2 == 0) ? 1 : -1;
    }

    int cycles = 0;
    while (cycles < 50) {
        moveSymbols(symbols, MAX_SYMBOLS);
        drawSymbols(symbols, MAX_SYMBOLS);
        Sleep(100);
        cycles++;
    }
}

void showMenu() {
    int choice;
    do {
        clearScreen();
        printTitleArt();
        printf("1. Play\n");
        printf("2. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int mode;
            printf("1. Multiplayer\n");
            printf("2. Versus Bot\n");
            printf("Choose: ");
            scanf("%d", &mode);
            
            if (mode == 1) {
                playMultiplayer();
            } else if (mode == 2) {
                int difficulty;
                printf("Choose Difficulty:\n1. Easy\n2. Medium\n3. Hard\n");
                scanf("%d", &difficulty);
                playBot(difficulty);
            }
        }
        
    } while (choice != 2);
    printf("Thank you for playing!\n");
}

void waterfallAnimation() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 30; x++) {
            char c = (rand() % 2 == 0) ? 'X' : 'O';
            printf("%c", c);
        }
        printf("\n");
    }
}

void printTitleArt() {
    printf("\n=============================\n");
    printf("   SIMPLE TIC TAC TOE (C)   \n");
    printf("=============================\n\n");
}
