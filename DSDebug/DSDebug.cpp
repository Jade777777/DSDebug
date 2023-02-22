#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "DSDebug.h"


int main(int argc, char* argv[])
{
    int temp = 0;
    std::vector<int> testDS = { 500000000,330000000,820000000,570000000,960000000,710000000,180000000,100000000, 1700000000, 300000000, 310000000, 20000000, 30000000,20000000,250000000 };
    DSDebug::Log(testDS, "Bubble Sort");
    for (int index = 0; index < testDS.size() - 1; index++) {
        for (int j = 0; j < testDS.size() - index - 1; j++) {
            if (testDS[j] > testDS[j + 1]) {
                temp = testDS[j];
                testDS[j] = testDS[j + 1];
                testDS[j + 1] = temp;
                DSDebug::Log(testDS, "Bubble Sort");
            }
        }
    }
    //Initialize array and DSDebug
    
    
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

