General Information\
T-REX is an open source project meant to help C++ programmers visualize data structures using an interactive GUI.

Overview
T-REX allows the user to pass in a data structure into one of its functions. When the program runs, a GUI window is displayed. This window allows the user to navigate through each data structure that was passed into the Log() function.

Getting Started

Setting up TIGR
This program requires the TIGR graphics library to be set up in your program
Download tigr.h and tigr.c from the following links:
tigr.h	https://github.com/erkkah/tigr/blob/master/tigr.h
tigr.c	https://github.com/erkkah/tigr/blob/master/tigr.c

Setting up T-REX
TRex requires C++ 20.

Copy TRex.h and tigr.h into your project's header files folder. Add tigr.c to your source folder.

Go to the file where your main() function is located and #include "TRex.h"

Functions
The following functions are included in the library:

TRex::Log(std::vector<datatype> vector, std::string vectorName)
TRex::Log(std::stack<datatype> stack, std::string stackName)
TRex::Log(std::queue<datatype> queue, std::string queueName)

 Log()handles the display of the passed-in data structure. It accepts vectors, stacks, and queues containing any of the standard C++ primitives.

TRex::End()
Allows the GUI loop to continue without the program closing.

How to use the functions
Call TRex()::Log() in the main() method and pass in the vector you would like to sort and a string to be displayed at the top of the window.

Call TRex()::End() at the bottom of the program.

Examples
int main(int argc, char *argv[])
{
    std::vector<double> demoDouble = { 1.1, 2.6, 12.0, 7.335, 9.4 };
    TRex::Log(demoDouble, "Double Demo");
    
    std::vector<bool> demoBool = { true, false, false, true };
    TRex::Log(demoBool, "Bool Demo");

    std::vector<std::string> demoStr = {"a","b","c", "hello", "world", "goodbye"};
    TRex::Log(demoStr, "String Demo");

    TRex::End();
    return 0;
}
If functioning correctly, the GUI Window will display.

Click the “Prev.” and “Next” buttons to navigate through the data structures.

Implementing Sorting using TREX::Log()
The Log() function also allows you to implement sorting. If placed inside a sorting loop, TREX will display a scrollbar with buttons at the bottom of the screen. This will allow the user to navigate through the sort step-by-step.

Sorting Example
int main(int argc, char *argv[])
{
    std::vector<int> testDS = { 500, 330, 820, 570, 960, 710 };
    int temp = 0;

    TRex::Log(testDS, "Bubble Sort");

    for (int index = 0; index < testDS.size() - 1; index++)
    {
        for (int j = 0; j < testDS.size() - index - 1; j++)
        {
            if (testDS[j] > testDS[j + 1])
            {
                temp = testDS[j];
                testDS[j] = testDS[j + 1];
                testDS[j + 1] = temp;
                TRex::Log(testDS, "Bubble Sort");
            }
        }
    }

    TRex::End();
    return 0;
}

Compiling through the Command Line
Windows
Make sure GCC compiler is installed on your system

Command:
g++ "filename".cpp tigr.c -lopengl32 -lgdi32 -std=c++20

Linux
Make sure the following packages are installed:
sudo apt install libgl1-mesa-dev
sudo apt install libglu1-mesa-dev
sudo apt install libx11-dev

Command:
g++ "filename".cpp tigr.c -lGLU -lGL -lX11 -std=c++20
