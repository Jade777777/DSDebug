#include <iostream>
#include "tigr.h"


class DSDebug 
{
protected:
    DSDebug() {

    }
    static DSDebug* instance;


public:

    DSDebug() = delete;

    void operator = (const DSDebug&) = delete;

    static DSDebug* GetInstance();

    void Test() {
        std::cout << "Test Test Test"<< std::endl;
    }


    
};

DSDebug* DSDebug::instance = nullptr;
DSDebug *DSDebug::GetInstance() {
    if (instance == nullptr) {
        instance = new DSDebug();
    }
}





int main(int argc, char* argv[])
{
    DSDebug::GetInstance()->Test();

    /*Tigr* screen = tigrWindow(320, 240, "Hello", 0);
    while (!tigrClosed(screen))
    {
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;*/
}

