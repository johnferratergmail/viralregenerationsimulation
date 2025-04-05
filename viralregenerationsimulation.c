#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 40
#define GENERATIONS 100
#define ALIVE 1
#define DEAD 0


void printGrid(int grid[ROWS][COLS]) {
    system("clear"); 
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(grid[i][j] ? "O" : " ");
        }
        printf("\n");
    }
}

int countLiveNeighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int ni = x + i;
            int nj = y + j;
            if ((i != 0 || j != 0) && ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

void updateGrid(int grid[ROWS][COLS]) {
    int temp[ROWS][COLS] = {0};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int liveNeighbors = countLiveNeighbors(grid, i, j);

            if (grid[i][j] == ALIVE) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    temp[i][j] = DEAD; 
                } else {
                    temp[i][j] = ALIVE; 
                }
            } else {
                if (liveNeighbors == 3) {
                    temp[i][j] = ALIVE; 
                }
            }
        }
    }

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = temp[i][j];
}
void initializeGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = rand() % 2;
}

int main() {
    int grid[ROWS][COLS];
    initializeGrid(grid);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        printGrid(grid);
        updateGrid(grid);
        usleep(200000); 
    }

    return 0;
}
