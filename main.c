#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "home.h"
#include "multiplayer.h"
#include "bot.h"

int main() {
    srand((unsigned int)time(NULL));
    showHomeScreen();
    showMenu();
    return 0;
}