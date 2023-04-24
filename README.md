# DSDebug


User Manual - Cycle 1

General Information
T-REX is meant to help C++ programmers visualize data structures using an interactive GUI.

Overview
T-REX allows the user to pass in a data structure into one of its functions. When the program runs, a GUI window is displayed. This window allows the user to navigate through each data structure that was passed into the Log() function.

Getting Started

Setting up TIGR
This program requires the TIGR graphics library to be set up in your program
Download tigr.h and tigr.c from the following links:
tigr.h	https://github.com/erkkah/tigr/blob/master/tigr.h
tigr.c	https://github.com/erkkah/tigr/blob/master/tigr.c

Setting up T-REX
Copy TRex.h and tigr.h into your project's header files folder. Add tigr.c to your source folder.

Go to the file where your main() function is located and #include "TRex.h"

Functions
The following functions are included in the library:

TRex::Log(std::vector<int> vector, std::string vectorName)
Handles the display of the passed-in data structure.

TRex::End()
Allows the GUI loop to continue without the program closing.

How to use the functions
Call TRex()::Log() in the main() method and pass in the vector you would like to sort and a string to be displayed at the top of the window.

Call TRex()::End() at the bottom of the program.
