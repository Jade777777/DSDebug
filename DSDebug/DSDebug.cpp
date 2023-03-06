#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "DSDebug.h"

class f {
public:
    f() {

    }
};

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
    
    
    std::vector<bool> testBool = { true, true, true, false, false , false, false};
    DSDebug::Log(testBool, "Bool Test");

    std::vector<double> testDouble = { 0.122,0.4444,0.2431324,0.23,0.45676457,0.9456,0.1555,0.9999 };
    DSDebug::Log(testDouble, "1Double Test");

    std::vector<std::string> testString = { "a","allspice", "b","basil", "c","corriander","cumin", "d","dill", "e", "epazote", "f", "fennel", "g", "garlic"};
    DSDebug::Log(testString, "String Test");

    f a = f();
    f b = f();
    std::vector<f> testClass = { a, b, a};
    //DSDebug::Log(testClass, "Class Test");

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

