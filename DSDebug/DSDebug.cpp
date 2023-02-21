#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "DSDebug.h"


int main(int argc, char* argv[])
{
    //Initialize array and DSDebug
    std::vector<int> testDS= { 2,3,4,5,6,7,8 };
    DSDebug::Log(testDS, "1Test");
    
    testDS = { 2,3,4,5,6,7 };
    DSDebug::Log(testDS, "2Test");

    testDS = { 2,3,4,5 };
    DSDebug::Log(testDS, "3Test");

    testDS = { 2,3, };
    DSDebug::Log(testDS, "4Test");

    testDS = { 2,3,4, };
    DSDebug::Log(testDS, "5Test");

    testDS = { 2, };
    DSDebug::Log(testDS, "3Test");

    testDS = { 2,3,4,5,6,};
    DSDebug::Log(testDS, "4Test");

    testDS = { 2,3,4,5,6 };
    DSDebug::Log(testDS, "5Test");
 

    DSDebug::End();
    return 0;
}

