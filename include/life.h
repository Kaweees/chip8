#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>

/* Begin typedef declarations */

/* Represents the types of cell states */
typedef enum CellOptions {
  DEAD = 0,
  ALIVE = 1,
} CellOptions;

/* Represents a toroidal grid */
typedef struct ToroidalGrid {
  int width;
  int height;
  CellOptions **data;
} ToroidalGrid;

/* Begin function prototype declarations */

/* Creates a toroidal grid */
ToroidalGrid *createToroidalGrid(int width, int height);

/* Frees the memory allocated for a toroidal grid */
void freeToroidalGrid(ToroidalGrid *grid);

/* Updates the toroidal grid */
void updateToroidalGrid(ToroidalGrid *grid);

/* Displays the toroidal grid */
void displayToroidalGrid(ToroidalGrid *grid);

/* Get the value at a given position in the grid */
CellOptions getToroidalGrid(ToroidalGrid *grid, int x, int y);

/* Set the value at a given position in the grid */
void setToroidalGrid(ToroidalGrid *grid, int x, int y, CellOptions value);

/* Returns the number of alive neighbors of a cell */
int countAliveNeighbors(ToroidalGrid *grid, int x, int y);

/* Returns the state of a cell in the next generation */

#endif /* LIFE_H */