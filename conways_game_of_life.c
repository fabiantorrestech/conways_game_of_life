/*
Fabian Torres
CS107 - Project 4: Conway's Game of Life v2 (with Linked Lists and Pointers)
Lab Wed 1PM
UIN: 652475960

Description/notes: 100% working C:

Compiled in (minGW) GCC on Code::Blocks Windows 10, clang for macOS 10.13.4 on Sublime-Text 3, and OnlineGDB, and ZyBooks.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int rows;
  int columns;
  int *grid; // a pointer to the grid that should be of size rows*columns
  struct node *next_step; // a pointer to the node that holds the grid for the
                          // next time step
};

// for the borders of the grid. it should return the number of alive neighbors
// in the corners of the grid.a
int neighborCorners(struct node *begin, int row, int col) {

  int livingNeighbors = 0;

  if (row == 0 && col == 0) {
    livingNeighbors = *(begin->grid + (begin->columns) * (row + 1) + (col)) +
                      *(begin->grid + (begin->columns) * (row) + (col + 1)) +
                      *(begin->grid + (begin->columns) * (row + 1) + (col + 1));
  } else if (row == 0 && col == (begin->columns - 1)) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col));
  } else if (row == (begin->rows - 1) && col == 0) {
    livingNeighbors = *(begin->grid + (begin->columns) * (row - 1) + (col)) +
                      *(begin->grid + (begin->columns) * (row) + (col + 1)) +
                      *(begin->grid + (begin->columns) * (row - 1) + (col + 1));
  } else if (row == (begin->rows - 1) && col == (begin->columns - 1)) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row - 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col));
  }

  return livingNeighbors;
}

// for the borders of the grid , it should return the number of alive neighbors
// in the corners of the grid.
int neighborEdges(struct node *begin, int row, int col) {
  // initialize the livingNeighbors
  int livingNeighbors = 0;
  // top edges
  if (row == 0) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row) + (col + 1));
  }
  // bottom edges
  else if (row == (begin->rows - 1)) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row - 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row) + (col + 1));
  }
  // left edge
  else if (col == 0) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row - 1) + (col)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col + 1));
  }
  // right edge
  else if (col == (begin->columns - 1)) {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row - 1) + (col)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col - 1));
  }
  return livingNeighbors;
}

// we call the other two cases (the corners and the edges) into neighbors
int neighbors(struct node *begin, int row, int col) {

  int livingNeighbors = 0;

  if ((row == 0 && col == 0) || (row == 0 && col == (begin->columns - 1)) ||
      (row == (begin->rows - 1) && col == 0) ||
      (row == (begin->rows - 1) && col == (begin->columns - 1))) {
    livingNeighbors = neighborCorners(begin, row, col);
  } else if ((row == 0 && col <= (begin->columns - 2)) ||
             (row == (begin->rows - 1) && col <= (begin->columns - 2)) ||
             (row <= (begin->rows - 2) && col == 0) ||
             (row <= (begin->rows - 2) &&
              col ==
                  (begin->columns - 1))) { // check if the cell is by the border
    livingNeighbors = neighborEdges(begin, row, col);
  } else {
    livingNeighbors =
        *(begin->grid + (begin->columns) * (row - 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col)) +
        *(begin->grid + (begin->columns) * (row - 1) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row) + (col - 1));
    livingNeighbors =
        livingNeighbors +
        *(begin->grid + (begin->columns) * (row) + (col + 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col - 1)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col)) +
        *(begin->grid + (begin->columns) * (row + 1) + (col + 1));
  }
  return livingNeighbors;
}

// creates the first node in the linked list
struct node *createInitialNode(FILE *input, int *numsteps) {
  // creating the 1st item our linked list and allocating space for it.
  struct node *begin;
  begin = (struct node *)malloc(sizeof(struct node));
  // scanning for numsteps
  fscanf(input, "%d", numsteps);
  // READIN ROWS AND COLUMNS (WITH SPACES IN BETWEEN)
  fscanf(input, "%d", &begin->rows);
  fscanf(input, "%d", &begin->columns);

  int x = 0;
  int y = 0;
  int coordinate;
  begin->grid = (int *)calloc(begin->rows * begin->columns, sizeof(int));

  // reading in x and y inputs to populate as 1's
  while (fscanf(input, "%d %d", &x, &y) != EOF) {
    // - checking if x and y go over the user's input for rows and columns
    //   because it can't populate where it doensn't exist.
    if (x > begin->rows) {
      printf("ERROR with initial point values.\n");
      return NULL;
    }
    if (y > begin->columns) {
      printf("ERROR with initial point values.\n");
      return NULL;
    }
    coordinate = ((begin->columns) * x) + y;
    *(begin->grid + coordinate) = 1;
  }

  return begin;
}

// this manages your linked list
void nextStep(struct node *begin) {
  // - add a struct node to the end of the list pointed to by begin for the
  //   next time step, so use data in the last node in the list to create the
  //   new timestep.

  // create temp and malloc space for it
  struct node *temp = begin;
  temp = (struct node *)malloc(sizeof(struct node));
  // the assigning temp node's struct members with begin's struct members
  temp->rows = begin->rows;
  temp->columns = begin->columns;
  // set next_step = NULL to have it clear for the next node's contents
  temp->next_step = NULL;
  // calloc assigns 0's to the grid of the size temp->rows * temp->columns
  temp->grid = (int *)calloc(temp->rows * temp->columns, sizeof(int));

  struct node *newnode = begin;

  // traverse to end of list
  // KEEP CHECKING THE NEXT SPOT UNTIL IT REACHES NULL
  while (newnode->next_step != NULL) {
    newnode = newnode->next_step;
  }

  newnode->next_step = temp;

  int i;
  int j;
  int coordinate;
  int neighborsAlive;

  for (i = 0; i < begin->rows; i++) {
    for (j = 0; j < begin->columns; j++) {
      coordinate = (temp->columns) * i + j;
      neighborsAlive = neighbors(newnode, i, j);

      if (*(newnode->grid + coordinate) == 1) {
        if (neighborsAlive < 2 || neighborsAlive > 3) {
          *(temp->grid + coordinate) = 0;
        } else {
          *(temp->grid + coordinate) = 1;
        }
      } else {
        if (neighborsAlive == 3) {
          *(temp->grid + coordinate) = 1;
        } else {
          *(temp->grid + coordinate) = 0;
        }
      }
    }
  }
  return;
}

// print out all the grids contained in the list
// pointed to by begin ptr.
void printList(struct node *begin) {

  int i;        // incrementer for rows
  int j;        // incrementer for columns
  int position; //  'coordinate' from createinitalnode function = position here
                // - equivalent to checking [i+1][j], [i][j+1],
                //   etc...; we will use temp's columns *
                //   i (always 1 less than number of rows) +
                //   j (always one less than the number of columns)

  // while temp's node's contents are still full,
  // which will happen for as many nodes...
  while (begin != NULL) {
    for (i = 0; i < begin->rows; i++) {
      for (j = 0; j < begin->columns; j++) {
        position = (begin->columns) * i + j;
        printf("%d", *(begin->grid + position));
      }
      printf("\n");
    }
    printf("\n");
    begin = begin->next_step;
  }
}

int main() {
  FILE *inFile = NULL;
  char *given_file_name = (char *)malloc(sizeof(char));

  printf("Welcome to Conway's game of Life\n");
  printf("Please enter filename");
  printf("\n");
  scanf("%s", &given_file_name);

  // opening the file given by the user
  inFile = fopen(&given_file_name, "r");

  if (inFile == NULL) {
    printf("ERROR opening filename %sant.txt",
           &given_file_name); // Checks if the file is empty
    return 0;
  }

  // reading in the numsteps given by user; remember that numsteps is a POINTER
  // INT, not a regular int.
  int numsteps;

  struct node *begin;
  begin = createInitialNode(inFile, &numsteps);

  if (begin == NULL) {
    return -1;
  }

  for (int i = 0; i < numsteps; i++) {
    nextStep(begin);
  }

  printList(begin);

  return 0;
}
