#include <iostream>
#include "tigr.h"
#include <vector>
#include <string>
#include <map>




class DataStructure {
private:
    std::vector<int> frame;

public:
    DataStructure() {
    }
    void SaveFrame(std::vector<int> frame) {
        this->frame = frame;
    }

};

class DSDebug 
{
private:

    DSDebug() {}
    static Tigr* screen;

    static std::map <std::string, DataStructure> dataStructures;

public:

    void operator = (const DSDebug&) = delete;

    static void Log(std::vector<int> dataStructure, std::string dsName) {

        if (!dataStructures.contains(dsName)) {
            dataStructures[dsName] = DataStructure();
            std::cout << "New data strucuter found, instantiating "<< dsName << std::endl;
        }
        dataStructures[dsName].SaveFrame(dataStructure);


        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");

        bool displayNext = false;
        while (displayNext)
        {
            tigrUpdate(screen);// checks for user input
        }

    }
    static void End() {
        while (!tigrClosed(screen))
        {
            tigrUpdate(screen);// checks for user input
        }
        tigrFree(screen);
    }

    
};

Tigr* DSDebug::screen = tigrWindow(320, 240, "DSDebug", 0);
std::map <std::string, DataStructure> DSDebug::dataStructures{};







int main(int argc, char* argv[])
{
    //Initialize array and DSDebug
    std::vector<int> testDS= { 2,3,4,5,6,7,8 };
    DSDebug::Log(testDS, "Test");

    testDS = { 2,3,4,5,6,7,8 };
    DSDebug::Log(testDS, "NewData");

    testDS = { 2,3,4,5,6,7,8 };
    DSDebug::Log(testDS, "NewData");

    DSDebug::End();
    return 0;
}

