# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define WINDOWS

# ifdef WINDOWS
    # include <Windows.h>
# endif

int countNeighbours(int **current, int row, int column) {
    int neighbours = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = column - 1; j <= column + 1; j++) {
            if (i == row && j == column) {
                continue;
            }
            if (current[i][j]) {
                neighbours++;
            }
        }
    }
    return neighbours;
}

int update(int **current, int numberOfRows, int numberOfColumns, int **next) {
    for (int i = 1; i < numberOfRows - 1; i++) {
        for (int j = 1; j < numberOfColumns - 1; j++) {
            int neighbours = countNeighbours(current, i, j);
            if (current[i][j]) {
                if (neighbours == 2 || neighbours == 3) {
                    next[i][j] = 1;
                } else {
                    next[i][j] = 0;
                }
            } else {
                if (neighbours == 3) {
                    next[i][j] = 1;
                } else {
                    next[i][j] = 0;
                }
            }
        }
    }
}

void draw(char *buffer, int **current, int numberOfRows, int numberOfColumns) {
    int length = 0;
    for (int i = 0; i < numberOfRows; i++) {
        for (int j = 0; j < numberOfColumns; j++) {
            length += sprintf(buffer + length, "%c", current[i][j] ? '@' : ' ');
        }
        length += sprintf(buffer + length, "\n");
    }
    system("cls");
    printf("%s", buffer);
    fflush(stdout);
}

int **newGrid(int numberOfRows, int numberOfColumns) {
    int **grid = (int **) calloc(numberOfRows, sizeof (int *));
    for (int i = 0; i < numberOfRows; i++) {
        grid[i] = (int *) calloc(numberOfColumns, sizeof (int));
    }
    return grid;
}

void initializeGrid(int **grid, int numberOfRows, int numberOfColumns, double filled) {
    for (int i = 1; i < numberOfRows - 1; i++) {
        for (int j = 1; j < numberOfColumns - 1; j++) {
            if ((1.0 * rand()) / RAND_MAX < filled) {
                grid[i][j] = 1;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int numberOfRows = 35;
    int numberOfColumns = 150;
    int delay = 500;
    double filled = 0.3;

    int **current = newGrid(numberOfRows, numberOfColumns);
    int **next = newGrid(numberOfRows, numberOfColumns);
    char *buffer = (char *) calloc(numberOfRows * numberOfColumns, sizeof (char) + 1);

    srand(time(0));
    initializeGrid(current, numberOfRows, numberOfColumns, filled);

    long generation = 0;
    while (1) {
        draw(buffer, current, numberOfRows, numberOfColumns);
        update(current, numberOfRows, numberOfColumns, next);
        int **temp = current;
        current = next;
        next = temp;
        printf("Generation: %d%s", generation++, generation % 3 == 0 ? "." : generation % 3 == 1 ? ".." : "...");
# ifdef WINDOWS
        Sleep(delay);
# endif
    }
}
