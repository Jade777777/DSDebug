#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "TRex.h"

class f {
public:
    f() {

    }
};


std::vector<int> GenerateRandomInts(int length) {

    //seed the std::rand() function
    unsigned seed = time(0);
    srand(seed);

    std::vector<int> randInts(length);
    std::generate(randInts.begin(), randInts.end(), std::rand);

    return randInts;
}


void TestVectorT()
{
    std::vector<bool> testBool = { true, true, true, false, false , false, false };
    TRex::Log(testBool, "Bool Test");

    std::vector<double> testDouble = { 0.122,0.4444,0.2431324,0.23,0.45676457,0.9456,0.1555,0.9999 };
    TRex::Log(testDouble, "1Double Test");

    std::vector<std::string> testString = { "a","allspice", "b","basil", "c","corriander","cumin", "d","dill", "e", "epazote", "f", "fennel", "g", "garlic" };
    TRex::Log(testString, "String Test");

    f a = f();
    f b = f();
    std::vector<f> testClass = { a, b, a };
    //DSDebug::Log(testClass, "Class Test");
}

void TestBubbleSort()
{
    int temp = 0;
    std::vector<int> testDS = { 500000000,330000000,820000000,570000000,960000000,710000000,180000000,100000000, 1700000000, 300000000, 310000000, 20000000, 30000000,20000000,250000000 };
    TRex::Log(testDS, "Bubble Sort");
    for (int index = 0; index < testDS.size() - 1; index++) {
        for (int j = 0; j < testDS.size() - index - 1; j++) {
            if (testDS[j] > testDS[j + 1]) {
                temp = testDS[j];
                testDS[j] = testDS[j + 1];
                testDS[j + 1] = temp;
                TRex::Log(testDS, "Bubble Sort");
            }
        }
    }
    //Initialize array and DSDebug

}


int main(int argc, char* argv[])
{
    for (int i = 0; i < 20; i++) {
        TRex::Log(GenerateRandomInts(i),"Build Vector<int>");
    }


    TestBubbleSort();

    TestVectorT();


    TRex::End();
    return 0;
}

