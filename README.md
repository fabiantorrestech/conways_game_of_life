# Conway's Game of Life

This is the final project completed in my CS 107 (Introduction to Programming) completed in C.
This specific implementation was completed with Linked Lists and pointers, however, we also implemented it via 3D arrays at an earlier point in the course.

The .c file expects a file formatted like so...

1) number of turns

2) grid size (#rows #columns)

3) coordinates of starting 'alive' positions on the board (#row# #column)

example: 
![](https://i.imgur.com/FAS1lz1.png)

----------------------


Example Output with given Conway.txt file:
![](https://i.imgur.com/FIgFDPq.png)

----------------------
Compiling instructions:

Assuming you have a gcc environment installed, you can simply compile by running the following command in the directory of the .c file:


    gcc conways_game_of_life.c -o conways_game_of_life
