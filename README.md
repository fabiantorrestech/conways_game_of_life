# Conway's Game of Life

Live Demo: https://replit.com/@fabiantorrestec/conwaysgameoflife#README.md

_Running this program in a browser-based environment will most likely cause stack overflow or ***stack smashing detected*** error, as it is to prevent stack-based buffer-overflow. This is normal, but the program still works correctly. This does not occur in an IDE or proper development environment._

This is the final project completed in my CS 107 (Introduction to Programming for Computer Engineers) completed in C.
This specific implementation was completed with Linked Lists and pointers, however, we also implemented it via 3D arrays at an earlier point in the course.

The .c file expects an input file formatted like so...

1) number of turns
2) grid size (#rows #columns)
3) coordinates of starting 'alive' positions on the board (#row# #column)

example, given in "conway.txt": 
![](https://i.imgur.com/FAS1lz1.png)

----------------------


Example Output with given Conway.txt file:
![](https://i.imgur.com/FIgFDPq.png)

----------------------
Compiling instructions:

Assuming you have a gcc environment installed, you can simply compile by running the following command in the directory of the .c file:


    gcc conways_game_of_life.c -o conways_game_of_life

Then run the program from the same directory with the compiled executable C file with:
    
    ./conways_game_of_life

