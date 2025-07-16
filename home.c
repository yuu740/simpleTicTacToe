#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "home.h"
#include "multiplayer.h"
#include "bot.h"

void openingAnimation() {
    for (int k = 0; k < 4; k++) {
        clearScreen();
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 40; x++) {
                if ((x / 4 + y / 2 + k) % 2 == 0) {
                    setColor(12);
                    printf("X");
                } else {
                    setColor(9);
                    printf("O");
                }
            }
            printf("\n");
        }
        setColor(7);
        Sleep(300);
    }
    for (int shift = 20; shift >= 0; shift--) {
        clearScreen();
        for (int s = 0; s < shift; s++) printf("\n");
        setColor(14);
        printf(" __       __            __                                             \n");
    printf("|  \\  _  |  \\          |  \\                                            \n");
    printf("| $$ / \\ | $$  ______  | $$  _______   ______   ______ ____    ______  \n");
    printf("| $$/  \\| $$ /      \\ | $$ /       \\ /      \\ |      \\    \\  /      \\ \n");
    printf("| $$  $$$\\ $$|  $$$$$$\\| $$|  $$$$$$$|  $$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\\n");
    printf("| $$ $$\\$$\\$$| $$    $$| $$| $$      | $$  | $$| $$ | $$ | $$| $$    $$\n");
    printf("| $$$$  \\$$$$| $$$$$$$$| $$| $$_____ | $$__/ $$| $$ | $$ | $$| $$$$$$$$\n");
    printf("| $$$    \\$$$ \\$$     \\| $$ \\$$     \\ \\$$    $$| $$ | $$ | $$ \\$$     \\\n");
    printf(" \\$$      \\$$  \\$$$$$$$ \\$$  \\$$$$$$$  \\$$$$$$  \\$$  \\$$  \\$$  \\$$$$$$$\n");
        setColor(7);
        Sleep(100);
    }
    Sleep(500);
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



void printTitleArt() {
    setColor(14); 
    // printf("");
    printf(" ________  __   ______  ________           ______  ________                     ______  \n");
    printf("|        \\|  \\ /      \\|        \\         /      \\|        \\                   /      \\ \n");
    printf(" \\$$$$$$$$ \\$$|  $$$$$$\\\\$$$$$$$$______  |  $$$$$$\\\\$$$$$$$$______    ______  |  $$$$$$\\\n");
    printf("   | $$   |  \\| $$   \\$$  | $$  |      \\ | $$   \\$$  | $$  /      \\  /      \\ | $$   \\$$\n");
    printf("   | $$   | $$| $$        | $$   \\$$$$$$\\| $$        | $$ |  $$$$$$\\|  $$$$$$\\| $$      \n");
    printf("   | $$   | $$| $$   __   | $$  /      $$| $$   __   | $$ | $$  | $$| $$    $$| $$   __ \n");
    printf("   | $$   | $$| $$__/  \\  | $$ |  $$$$$$$| $$__/  \\  | $$ | $$__/ $$| $$$$$$$$| $$__/  \\\n");
    printf("   | $$   | $$ \\$$    $$  | $$  \\$$    $$ \\$$    $$  | $$  \\$$    $$ \\$$     \\ \\$$    $$\n");
    printf("    \\$$    \\$$  \\$$$$$$    \\$$   \\$$$$$$$  \\$$$$$$    \\$$   \\$$$$$$   \\$$$$$$$  \\$$$$$$ \n");
    setColor(7);
}

void clearScreen() {
    system("cls");
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

