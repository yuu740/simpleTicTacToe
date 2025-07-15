#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "home.h"
#include "multiplayer.h"
#include "bot.h"

void showHomeScreen() {
    int cycles = 0;
    while (cycles < 10) {
        clearScreen();
        waterfallAnimation();
        printTitleArt();
        Sleep(300);
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

void clearScreen() {
    system("cls");
}
