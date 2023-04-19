#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "TRex.h"

std::vector<int> GenerateRandomInts(int length)
{

    // seed the std::rand() function
    unsigned seed = time(0);
    srand(seed);

    std::vector<int> randInts(length);
    std::generate(randInts.begin(), randInts.end(), std::rand);

    return randInts;
}

void TestVectorT()
{
    std::vector<bool> testBool = {true, true, true, false, false, false, false};
    TRex::Log(testBool, "Bool Test");

    // Empty vectors no longer throw an error
    std::vector<std::string> testEmptyStr = {};
    TRex::Log(testEmptyStr, "Empty Test Str");

    std::vector<int> testEmptyInt = {};
    TRex::Log(testEmptyInt, "Empty Test Int");

    std::vector<bool> testEmptyBool = {};
    TRex::Log(testEmptyBool, "Empty Test Bool");

    std::vector<int> testFull = {1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 30, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
    TRex::Log(testFull, "Full test");
    std::vector<int> test26 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
    TRex::Log(test26, "Test26");

    std::vector<double> testDouble = {0.122, 0.4444, 0.2431324, 0.23, 0.45676457, 0.9456, 0.1555, 0.9999};
    TRex::Log(testDouble, "1Double Test");

    std::vector<std::string> testString = {
        "a",
        "allspice",
        "b",
        "basil",
        "c",
        "corriander",
        "cumin",
        "d",
        "dill",
        "e",
        "epazote",
        "f",
        "fennel",
        "g",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
        "garlic",
    };
    TRex::Log(testString, "String Test");
}

void TestStack()
{
    std::stack<int> testStack;
    testStack.push(1);
    testStack.push(2);
    testStack.push(3);
    TRex::Log(testStack, "Test Stack");

    std::stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("world!");
    stringStack.push("I");
    stringStack.push("am");
    stringStack.push("alive!");
    TRex::Log(stringStack, "String Stack");

    std::stack<double> doubleStack;
    double dInput1 = 3.46;
    double dInput2 = 79.36;
    double dInput3 = 15463.756;
    double dInput4 = 21.00;
    double dInput5 = 20.50;
    doubleStack.push(dInput1);
    doubleStack.push(dInput2);
    doubleStack.push(dInput3);
    doubleStack.push(dInput4);
    doubleStack.push(dInput5);
    TRex::Log(doubleStack, "Double Stack");

    std::stack<float> floatStack;
    float fInput1 = 4.07;
    float fInput2 = 0.364;
    float fInput3 = -45.23;
    float fInput4 = 10.11;
    float fInput5 = 15.16;
    floatStack.push(fInput1);
    floatStack.push(fInput2);
    floatStack.push(fInput3);
    floatStack.push(fInput4);
    floatStack.push(fInput5);
    TRex::Log(floatStack, "Float Stack");
}

void TestTree()
{

    std::vector<TRex::Node> testTree;
    for (int i = 0; i < 26; i++)
    {
        testTree.push_back(TRex::Node("node " + std::to_string(i)));
    }
    testTree[0].childIndicies.push_back(3);
    testTree[0].childIndicies.push_back(5);
    testTree[0].childIndicies.push_back(7);
    testTree[0].childIndicies.push_back(11);
    TRex::Log(testTree, "Test Tree");
    TRex::Log(testTree, "Test Tree");
}

void TestBubbleSort()
{
    int temp = 0;
    std::vector<int> testDS = {500000000, 330000000, 820000000, 570000000, 960000000, 710000000, 180000000, 100000000, 1700000000, 300000000, 310000000, 20000000, 30000000, 20000000, 250000000};
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
    // Initialize array and DSDebug
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 20; i++)
    {
        TRex::Log(GenerateRandomInts(i), "Build Vector<int>");
    }

    TestStack();

    TestTree();

    TestBubbleSort();

    TestVectorT();

    TRex::End();
    return 0;
}
