#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "home.h"
#include "multiplayer.h"
#include "bot.h"

int main() {
    openingAnimation();
    srand((unsigned int)time(NULL));
    showMenu();
    return 0;
}