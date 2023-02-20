#include <iostream>
#include "tigr.h"
#include <vector>
#include <string>
#include <map>










class DSDebug 
{
private:

    class DataStructure {
    private:
        std::vector<int> frames;

    public:
        DataStructure() {
        }

        void SaveFrame(std::vector<int> frames) {
            this->frames = frames;
        }

        void Draw() {
            {
                const int increment = 70;
                int xOffset = 50;
                int length = frames.size();

                for (int i = 0; i < length; i++)
                {
                    // temp 4 increments x value by 20 every loop moving it across the screen
                    xOffset += increment;
                    // Next two lines change the array from a int array to a const char * array (Tigr stuff)
                    std::string iValue = std::to_string(frames[i]);
                    char const* iPrintValue = iValue.c_str();
                    tigrPrint(screen, tfont, xOffset, 400, tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);
                }

            }
        }

    };

    DSDebug() {}

    static Tigr* screen;

    static std::map <std::string, DataStructure> dataStructures;

    static std::string currentDS;

    static bool waitingForInput;



    class ButtonEvent { 
    public:
        virtual void Activate() = 0; 
    
    };



#pragma region ButtonEvents
    class NextDS : public ButtonEvent {
    public:
        void Activate() {
            std::map <std::string, DataStructure>::iterator it = dataStructures.begin();
            for (it; it != dataStructures.end(); ++it) {
                if (it->first == currentDS) {// find the current data structuer

                    it++;// get the next data structure
                    if (it == dataStructures.end()) {
                        currentDS = dataStructures.begin()->first;
                    }
                    else {
                        currentDS = it->first;
                    }
                    break;
                }
            }
        }
    };
    class PreviousDS : public ButtonEvent {
    public:
        void Activate() {
            std::map <std::string, DataStructure>::iterator it = dataStructures.begin();
            for (it; it != dataStructures.end(); ++it) {
                if (it->first == currentDS) {//find the current data structure
                    
                    //get the previous data structure
                    if (it == dataStructures.begin()) {
                        it = dataStructures.end();
                    }
                    it--;
                    currentDS = it->first;
                    break;
                }
            }
        }
    };
#pragma endregion


    static void DrawWindow() {
        
        if (currentDS== "") {
            auto it = dataStructures.begin();
            currentDS = it->first;
        }
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        DrawUI();
        DrawDS();
    }

    static void DrawCenterText(int x, int y, std::string text) {
        int textXCenter = text.size() * 3;
        int textYcenter = 5; // assume there are no new lines
        tigrPrint(screen, tfont, x - textXCenter, y - textYcenter, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

    static void DrawButton(int x, int y, int width, int height, std::string text, ButtonEvent *buttonEvent) {
        TPixel neutral = tigrRGB(200, 200, 200);
        TPixel highlight = tigrRGB(230, 230, 230);
        TPixel selected = tigrRGB(170, 170, 170);


        int xCenter = x + (0.5 * width);
        int yCenter = y + (0.5 * height);


        int mx;
        int my;
        int input;// 1 is left click

        
        tigrMouse(screen, &mx, &my, &input);


        if (mx >= x && mx <= x + width && my >= y && my <= y + height) {
            if (input == 1) {
                //button selected
                tigrFill(screen, x, y, width, height, selected);
                waitingForInput = false;
            }
            else {
                
                //button Highlighted
                tigrFill(screen, x, y, width, height, highlight);
                if (waitingForInput == false) {
                    
                    //ACTIVATE EVENT HERE
                    buttonEvent->Activate();
                }
                waitingForInput = true;
            }
        }
        else {
            //button at neutral
            tigrFill(screen, x, y, width, height, neutral);
            //waitingForInput = true;
        }

        DrawCenterText(xCenter, yCenter, text);

    }
    
    static void DrawUI() {

        ButtonEvent *nextDSEvent;
        NextDS nextDS = NextDS();
        nextDSEvent = &nextDS;

        ButtonEvent* prevDSEvent;
        PreviousDS prevDS = PreviousDS();
        prevDSEvent = &prevDS;


        DrawCenterText(screen->w / 2, 15, currentDS);
        DrawButton(screen->w / 2 - 15 - 90, 5, 30, 30, "PREV.", prevDSEvent);
        DrawButton(screen->w / 2 - 15 + 90, 5, 30, 30, "NEXT", nextDSEvent);
    }
  
    static void DrawDS() {
        dataStructures[currentDS].Draw();
    }



public:

    void operator = (const DSDebug&) = delete;

    static void Log(std::vector<int> dataStructure, std::string dsName) {

        if (!dataStructures.contains(dsName)) {
            dataStructures[dsName] = DataStructure();
            std::cout << "New data strucuter found, instantiating "<< dsName << std::endl;
        }
        dataStructures[dsName].SaveFrame(dataStructure);
        

        bool displayNext = false;
        while (displayNext)// this will be used to implement a delay  between logs
        {
            tigrUpdate(screen);// checks for user input
            DrawWindow();
        }

    }
    static void End() {
        while (!tigrClosed(screen))
        {
            tigrUpdate(screen);// checks for user input
            DrawWindow();
        }
        tigrFree(screen);
    }

    
};

Tigr* DSDebug::screen = tigrWindow(640, 480, "DSDebug", 0);
std::map <std::string, DSDebug::DataStructure> DSDebug::dataStructures{};
std::string DSDebug::currentDS = "";
bool DSDebug::waitingForInput = true;















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

