#include <stdio.h>

char board[3][3];
char currentPlayer = 'X';

// Inisialisasi papan kosong
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Menampilkan papan ke layar
void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n\n");
}

// Cek apakah ada pemenang
int checkWin() {
    // Cek baris dan kolom
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return 1;
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return 1;
    }
    // Cek diagonal
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return 1;
    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return 1;

    return 0;
}

// Cek apakah papan penuh (draw)
int checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Tukar pemain
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int row, col;
    initializeBoard();

    while (1) {
        printBoard();
        printf("Player %c, masukkan baris dan kolom (1-3): ", currentPlayer);
        scanf("%d %d", &row, &col);

        row--; col--;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = currentPlayer;

            if (checkWin()) {
                printBoard();
                printf("Player %c menang!\n", currentPlayer);
                break;
            } else if (checkDraw()) {
                printBoard();
                printf("Seri!\n");
                break;
            }

            switchPlayer();
        } else {
            printf("Posisi tidak valid, coba lagi.\n");
        }
    }

    return 0;
}
