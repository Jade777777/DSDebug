#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <queue>
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

    std::stack<int> longStack;
    longStack.push(1);
    longStack.push(2);
    longStack.push(3);
    longStack.push(4);
    longStack.push(5);
    longStack.push(6);
    longStack.push(7);
    longStack.push(8);
    longStack.push(9);
    longStack.push(10);
    longStack.push(11);
    longStack.push(12);
    longStack.push(13);
    longStack.push(14);
    longStack.push(15);
    longStack.push(16);
    longStack.push(17);
    longStack.push(18);
    longStack.push(19);
    longStack.push(20);
    longStack.push(21);
    longStack.push(22);
    longStack.push(23);
    longStack.push(24);
    longStack.push(25);
    longStack.push(26);
    longStack.push(27);
    longStack.push(28);
    TRex::Log(longStack, "Long Stack");
}

void TestQueue()
{
    std::queue<int> intQueue;
    intQueue.push(1);
    intQueue.push(2);
    intQueue.push(3);
    TRex::Log(intQueue, "Int Queue");

    std::queue<std::string> stringQueue;
    stringQueue.push("Hello");
    stringQueue.push("there!");
    stringQueue.push("I'm");
    stringQueue.push("a");
    stringQueue.push("queue!");
    TRex::Log(stringQueue, "String Queue");

    std::queue<double> doubleQueue;
    double dInput1 = 4.19;
    double dInput2 = 3.141592;
    double dInput3 = 3.5;
    double dInput4 = 21.00;
    doubleQueue.push(dInput1);
    doubleQueue.push(dInput2);
    doubleQueue.push(dInput3);
    doubleQueue.push(dInput4);
    TRex::Log(doubleQueue, "Double Queue");

    std::queue<float> floatQueue;
    floatQueue.push(45.87);
    floatQueue.push(126.352);
    floatQueue.push(0.9836);
    TRex::Log(floatQueue, "Float Queue");

    std::queue<int> longQueue;
    longQueue.push(1);
    longQueue.push(2);
    longQueue.push(3);
    longQueue.push(4);
    longQueue.push(5);
    longQueue.push(6);
    longQueue.push(7);
    longQueue.push(8);
    longQueue.push(9);
    //
    longQueue.push(10);
    longQueue.push(11);
    longQueue.push(12);
    longQueue.push(13);
    //
    longQueue.push(14);
    longQueue.push(15);
    longQueue.push(16);
    longQueue.push(17);
    longQueue.push(18);
    longQueue.push(19);
    longQueue.push(20);
    longQueue.push(21);
    longQueue.push(22);
    longQueue.push(23);
    longQueue.push(24);
    longQueue.push(25);
    longQueue.push(26);
    TRex::Log(longQueue, "Long Queue");

    std::queue<int> mediumQueue;
    mediumQueue.push(1);
    mediumQueue.push(2);
    mediumQueue.push(3);
    mediumQueue.push(4);
    mediumQueue.push(5);
    mediumQueue.push(6);
    mediumQueue.push(7);
    mediumQueue.push(8);
    mediumQueue.push(9);
    mediumQueue.push(10);
    mediumQueue.push(11);
    mediumQueue.push(12);
    mediumQueue.push(13);
    TRex::Log(mediumQueue, "Medium Sized Queue");
}

void TestTree()
{

    std::vector<TRex::Node> testTree;
    for (int i = 0; i < 26; i++)
    {
        testTree.push_back(TRex::Node("node " + std::to_string(i)));
    }
    testTree[0].AddChild(3);
    testTree[0].AddChild(5);
    testTree[0].AddChild(7);
    testTree[0].AddChild(11);
    testTree[3].AddChild(13);   
    testTree[3].AddChild(17);
    testTree[3].AddChild(19);
    testTree[5].AddChild(23);
    testTree[5].AddChild(3);
    testTree[5].AddChild(5);
    testTree[7].AddChild(7);
    TRex::Log(testTree, "Test Tree");
    TRex::Log(testTree, "Test Tree");
}

void SimpleTestTree() {
    std::vector<TRex::Node> testTRee;
    testTRee.push_back(TRex::Node("A"));
    testTRee.push_back(TRex::Node("B"));
    testTRee.push_back(TRex::Node("C"));
    testTRee.push_back(TRex::Node("D"));
    testTRee[0].AddChild(1);
    testTRee[0].AddChild(2);
    testTRee[1].AddChild(3);
    testTRee[2].AddChild(1);
    testTRee[3].AddChild(3);
    TRex::Log(testTRee, "Simple Test Tree");

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

    TestQueue();

    TestTree();

    TestBubbleSort();

    TestVectorT();

    SimpleTestTree();



    TRex::End();
    return 0;
}
