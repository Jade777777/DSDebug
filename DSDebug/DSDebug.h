#pragma once
#include "tigr.h"
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <type_traits>
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template<typename T>
concept totalyOrdered = std::totally_ordered<T> && !(std::integral<T> || std::floating_point<T>);

class DSDebug
{
private:
    class DSFrame {
    public:
        virtual void Draw() = 0;
    };
#pragma region DataStructures

    //
    template <typename T>
        requires arithmetic<T>
    class VectorNumFrame : public DSFrame {
    private:
        std::vector<T> data;
    public:
        VectorNumFrame(std::vector<T> data) {
            this->data = data;
        }
        void Draw() {

            //print out frames
            int offset = 0;
            for (auto const& c : data) {
                
                //getting width of bar
                int rectangleWidthMax = 580;
                double frameMax = *std::max_element(data.begin(), data.end());
                double barSizePercent = c / double(frameMax);
                int barSize = rectangleWidthMax * barSizePercent;

                std::cout << barSize<< "   " << std::to_string(c) << std::endl;
                //print bar
                tigrFillRect(screen, 30, 100 + offset, barSize, 10, tigrRGB(255, 0, 0));

                std::string iValue = std::to_string(c);
                
                char const* iPrintValue = iValue.c_str();
                

                //print number
                tigrPrint(screen, tfont, 20, 100 + offset, tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);

                offset += 15;
            }
        }
    };


    //
    template<typename T>
        requires totalyOrdered<T>
    class VectorOrderedFrame : public DSFrame { 
    private:
        std::vector<T> data;

        //method found here: https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
        template <typename T>
        std::vector<size_t> sort_indexes(const std::vector<T>& v) {

            // initialize original index locations
            std::vector<size_t> idx(v.size());
            iota(idx.begin(), idx.end(), 0);

            // sort indexes based on comparing values in v
            // using std::stable_sort instead of std::sort
            // to avoid unnecessary index re-orderings
            // when v contains elements of equal values 
            std::stable_sort(idx.begin(), idx.end(),
                [&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });
            return idx;
        }

    public:
        VectorOrderedFrame(std::vector<T> data) {
            this->data = data;
        }

        void Draw() {
            int offset = 15;
            T max = data[0];

            std::vector<size_t> sortedIndex = sort_indexes(data);
            std::vector<int> indexSort(data.size());
            

            for (int val = 0; val < data.size(); val++) {
                int i = sortedIndex[val];
                T c = data[i];
                
                //getting width of bar
                int rectangleWidthMax = 580;
                int barSize = rectangleWidthMax * val/data.size();

                ////print bar
                tigrFillRect(screen, 30, 100 + (offset*i), barSize, 10, tigrRGB(255, 0, 0));

                //determine name
                std::string iValue = ""+c;// std::to_string(c);

                std::cout << c << "   " << iValue << std::endl;

                char const* iPrintValue = iValue.c_str();

                //print number
                tigrPrint(screen, tfont, 20, 100 + (offset*i), tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);

                //offset += 15;
            }
        }
    };



#pragma endregion
    class DSContainer {
    protected:

        std::vector<DSFrame*> frames;//create destructor
        int currentFrame;

    public:
        DSContainer() {
            currentFrame = 0;
        }
        ~DSContainer() {
            for (auto frame : frames) {
                delete frame;
            }
        }
        void SaveFrame(DSFrame* frame) {
            this->frames.emplace_back(frame);
        }
        
        void NextFrame() {
            if (currentFrame < frames.size() - 1) {
                currentFrame++;
            }
        }
        void PrevFrame() {
            if (currentFrame > 0) {
                currentFrame--;
            }
        }
        void SetFrame(int i) {
            currentFrame = i;
        }
        int GetFrame() {
            return currentFrame;
        }
        void Draw() {
            if (frames.size() > currentFrame && currentFrame >= 0) {
                frames[currentFrame]->Draw();
            }
        }
    };



    DSDebug() {}

    static Tigr* screen;

    static std::map <std::string, DSContainer> namedContainers;

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
            std::map <std::string, DSContainer>::iterator it = namedContainers.begin();
            for (it; it != namedContainers.end(); ++it) {
                if (it->first == currentDS) {// find the current data structuer

                    it++;// get the next data structure
                    if (it == namedContainers.end()) {
                        currentDS = namedContainers.begin()->first;
                    }
                    else {
                        currentDS = it->first;
                    }
                    break;
                }
            }
        }
    };
    class PrevDS : public ButtonEvent {
    public:
        void Activate() {
            std::map <std::string, DSContainer>::iterator it = namedContainers.begin();
            for (it; it != namedContainers.end(); ++it) {
                if (it->first == currentDS) {//find the current data structure

                    //get the previous data structure
                    if (it == namedContainers.begin()) {
                        it = namedContainers.end();
                    }
                    it--;
                    currentDS = it->first;
                    break;
                }
            }
        }
    };
    class NextFrame : public ButtonEvent {
    public:
        void Activate() {
            namedContainers[currentDS].NextFrame();
        }
    };
    class PrevFrame : public ButtonEvent {
    public:
        void Activate() {
            namedContainers[currentDS].PrevFrame();
        }
    };
#pragma endregion


    static void DrawWindow() {

        if (currentDS == "") {
            auto it = namedContainers.begin();
            currentDS = it->first;
        }
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        DrawUI();
        DrawDS();
    }

    static void DrawCenterText(int x, int y, std::string text) {
        
        int textXCenter = tigrTextWidth(tfont, text.c_str()) / 2;//text.size() * 4;
        int textYcenter = tigrTextHeight(tfont, text.c_str()) / 2; // assume there are no new lines
        tigrPrint(screen, tfont, x - textXCenter, y - textYcenter, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

    static void DrawButton(int x, int y, int width, int height, std::string text, ButtonEvent &buttonEvent) {
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
                    buttonEvent.Activate();
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

        DrawCenterText(screen->w / 2, 15, currentDS);
        PrevDS x;
        DrawButton(screen->w / 2 - 15 - 90, 5, 30, 30, "PREV.", x);
        NextDS y;
        DrawButton(screen->w / 2 - 15 + 90, 5, 30, 30, "NEXTCCSD", y);
        PrevFrame z;
        DrawButton(screen->w / 2 - 15 - 90, screen->h-35, 30, 30, "PREV.", z);
        NextFrame a;
        DrawButton(screen->w / 2 - 15 + 90, screen->h-35, 30, 30, "NEXT", a);
    }

    static void DrawDS() {
        namedContainers[currentDS].Draw();
    }



public:
    
    void operator = (const DSDebug&) = delete;

    template<typename T>
        requires arithmetic<T>
    static void Log(std::vector<T> dataStructure, std::string dsName) {
        if (!namedContainers.contains(dsName)) {
            namedContainers[dsName] = DSContainer();
            std::cout << "New data strucuter found, instantiating " << dsName << std::endl;
        }
        namedContainers[dsName].SaveFrame(new VectorNumFrame(dataStructure));

        bool displayNext = false;
        while (displayNext)// this will be used to implement a delay  between logs
        {
            tigrUpdate(screen);// checks for user input
            DrawWindow();
        }

    }
    template<typename T>
        requires totalyOrdered<T>
    static void Log(std::vector<T> dataStructure, std::string dsName) {
        if (!namedContainers.contains(dsName)) {
            namedContainers[dsName] = DSContainer();
            std::cout << "New data strucuter found, instantiating " << dsName << std::endl;
        }
        namedContainers[dsName].SaveFrame(new VectorOrderedFrame(dataStructure));

        bool displayNext = false;
        while (displayNext)// this will be used to implement a delay  between logs
        {
            tigrUpdate(screen);// checks for user input
            DrawWindow();
        }

    }



    //template<typename T>
    //    requires arithmetic<T>
    //static void Log(std::vector<T> dataStructure, std::string dsName) {
    //    if (!namedContainers.contains(dsName)) {
    //        namedContainers[dsName] = DSContainer();
    //        std::cout << "New data strucuter found, instantiating " << dsName << std::endl;
    //    }
    //    namedContainers[dsName].SaveFrame(new VectorTFrame(dataStructure));

    //    bool displayNext = false;
    //    while (displayNext)// this will be used to implement a delay  between logs
    //    {
    //        tigrUpdate(screen);// checks for user input
    //        DrawWindow();
    //    }

    //}

    static void End() {
        while (!tigrClosed(screen))
        {
            tigrUpdate(screen);// checks for user input
            DrawWindow();
        }
        tigrFree(screen);
        atexit(DataCleanup);
    }
    static void DataCleanup() {
        std::cout << "Cleaning up all DSDebug data." << std::endl;
    }

};

Tigr* DSDebug::screen = tigrWindow(640, 480, "DSDebug", 0);
std::map <std::string, DSDebug::DSContainer> DSDebug::namedContainers{};
std::string DSDebug::currentDS = "";
bool DSDebug::waitingForInput = true;