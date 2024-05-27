#include "life.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ToroidalGrid *createToroidalGrid(int width, int height) {
  ToroidalGrid *grid = malloc(sizeof(ToroidalGrid));
  if (grid == NULL) {
    perror("Error allocating memory for grid");
    exit(EXIT_FAILURE);
  }
  grid->width = width;
  grid->height = height;
  grid->data = malloc(sizeof(CellOptions *) * height);
  for (int i = 0; i < height; i++) {
    grid->data[i] = malloc(sizeof(CellOptions) * width);
    if (grid->data[i] == NULL) {
      perror("Error allocating memory for grid row");
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < width; j++) {
      grid->data[i][j] = DEAD;
    }
  }
  return grid;
}

void freeToroidalGrid(ToroidalGrid *grid) {
  for (int i = 0; i < grid->height; i++) {
    free(grid->data[i]);
  }
  free(grid->data);
  free(grid);
}

void displayToroidalGrid(ToroidalGrid *grid) {
  sleep(1);
  system("clear");
  for (int i = 0; i < grid->height; i++) {
    for (int j = 0; j < grid->width; j++) {
      printf("%c ", grid->data[i][j] ? '1' : '0');
    }
    printf("\n");
  }
}

CellOptions getToroidalGrid(ToroidalGrid *grid, int x, int y) {
  x = (x + grid->width) % grid->width;
  y = (y + grid->height) % grid->height;
  return grid->data[y][x];
}

// Set the value at a given position in the grid
void setToroidalGrid(ToroidalGrid *grid, int x, int y, CellOptions value) {
  x = (x + grid->width) % grid->width;
  y = (y + grid->height) % grid->height;
  grid->data[y][x] = value;
}

int countAliveNeighbors(ToroidalGrid *grid, int x, int y) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      if (getToroidalGrid(grid, x + i, y + j) == ALIVE) {
        count++;
      }
    }
  }
  return count;
}

void updateBoard(ToroidalGrid **grid) {
  ToroidalGrid *newGrid = createToroidalGrid((*grid)->width, (*grid)->height);
  for (int i = 0; i < (*grid)->height; i++) {
    for (int j = 0; j < (*grid)->width; j++) {
      int aliveNeighbors = countAliveNeighbors((*grid), j, i);
      if ((*grid)->data[i][j] == ALIVE) {
        /* If an ALIVE cell has 2 or 3 ALIVE neighbors, it will be ALIVE in the
         * next time step. Otherwise, it will be DEAD.*/
        if (aliveNeighbors == 2 || aliveNeighbors == 3) {
          (newGrid)->data[i][j] = ALIVE;
        } else {
          (newGrid)->data[i][j] = DEAD;
        }
      } else {
        /* If a DEAD cell has 3 ALIVE neighbors, it will be ALIVE in the next
         * time step. */
        if (aliveNeighbors == 3) {
          (newGrid)->data[i][j] = ALIVE;
        } else {
          (newGrid)->data[i][j] = DEAD;
        }
      }
    }
  }
  freeToroidalGrid(*grid);
  *grid = newGrid;
}