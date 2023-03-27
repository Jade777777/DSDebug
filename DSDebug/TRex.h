#pragma once
#include "./Tigr/tigr.h"
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <type_traits>
#include <concepts>


template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template <typename T>
concept totallyOrdered = std::totally_ordered<T> && !(std::integral<T> || std::floating_point<T>);

static bool initialSlider = true;
static int sliderX;
static int sliderY;
static int prevx = 0, prevy = 0, prev = 0;

class TRex
{
private:
    class DSFrame
    {
    public:
        virtual void Draw() = 0;
    };
#pragma region DataStructures

    //
    template <typename T>
        requires arithmetic<T>
    class VectorNumFrame : public DSFrame
    {

    private:
        std::vector<T> data;

    public:
        VectorNumFrame(std::vector<T> data)
        {
            this->data = data;
        }
        void Draw()
        {

            // print out frames
            int offset = 0;
            int barCounter = 0;
            int remainderCount = 0;
            for (auto const& c : data) {
                //Added to limit the amount of bars that can show on screen at once
                if (barCounter <= 24) {
                    //getting width of bar
                    int rectangleWidthMax = 580;
                    double frameMax = *std::max_element(data.begin(), data.end());
                    double barSizePercent = c / double(frameMax);
                    int barSize = rectangleWidthMax * barSizePercent;

                    //print bar
                    tigrFillRect(screen, 30, 50 + offset, barSize, 10, tigrRGB(255, 0, 0));

                    std::string iValue = "" + std::to_string(c);

                    char const* iPrintValue = iValue.c_str();


                    //print number
                    tigrPrint(screen, tfont, 20, 50 + offset, tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);

                    offset += 15;
                   
                }
                else {
                    
                    //used to check if there are remaining values offscreen
                    remainderCount++;
        
                }

                barCounter++;

            }

            //Print how many values remain offscreen if there are more than 25 values
            if (remainderCount > 0) {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values";
                char const* remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + offset, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);

                std::string addOnStr = "not being shown";
                char const* addOnPrint = addOnStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + offset + 15, tigrRGB(0xFF, 0xFF, 0xFF), addOnPrint);
            }
            
        }
    };

    //
    template <typename T>
        requires totallyOrdered<T>
    class VectorOrderedFrame : public DSFrame
    {
    private:
        std::vector<T> data;

        //method found here: https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
        template <typename S>
        std::vector<size_t> sort_indexes(const std::vector<S>& v) {

            // initialize original index locations
            std::vector<size_t> idx(v.size());
            iota(idx.begin(), idx.end(), 0);

            // sort indexes based on comparing values in v
            // using std::stable_sort instead of std::sort
            // to avoid unnecessary index re-orderings
            // when v contains elements of equal values
            std::stable_sort(idx.begin(), idx.end(),
                             [&v](size_t i1, size_t i2)
                             { return v[i1] < v[i2]; });
            return idx;
        }

    public:
        VectorOrderedFrame(std::vector<T> data)
        {
            this->data = data;
        }

        void Draw()
        {
            int offset = 15;
            T max = data[0];

            std::vector<size_t> sortedIndex = sort_indexes(data);
            std::vector<int> indexSort(data.size());
            
            int i;
            int remainderCount = 0;
            for (int val = 0; val < data.size(); val++) {
                //Added to limit the amount of bars that can show on screen at once
                if (val <= 24) {
                    i = sortedIndex[val];
                    T c = data[i];

                    //getting width of bar
                    int rectangleWidthMax = 580;
                    int barSize = rectangleWidthMax * val / data.size();

                    ////print bar
                    tigrFillRect(screen, 30, 50 + (offset * i), barSize, 10, tigrRGB(255, 0, 0));

                    //determine name
                    std::string iValue = "" + c;// std::to_string(c);

                    char const* iPrintValue = iValue.c_str();

                    //print number
                    tigrPrint(screen, tfont, 20, 50 + (offset * i), tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);
                }
                else {
                    //Print elipses if there is too much on screen
                    remainderCount++;
                    /*std::string elipses = "(...)";
                    char const* elipsesPrint = elipses.c_str();
                    tigrPrint(screen, tfont, 580, 50 + (offset * i) + 15, tigrRGB(0xFF, 0xFF, 0xFF), elipsesPrint);*/
                }

            }

            //Print how many values remain offscreen if there are more than 25 values
            if (remainderCount > 0) {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values";
                char const* remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + (offset*i) + 15, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);

                std::string addOnStr = "not being shown";
                char const* addOnPrint = addOnStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + (offset * i) + 30, tigrRGB(0xFF, 0xFF, 0xFF), addOnPrint);
            }
        }
    };

#pragma endregion
    class DSContainer
    {
    protected:
        std::vector<DSFrame *> frames; // create destructor
        int currentFrame;

    public:
        DSContainer()
        {
            currentFrame = 0;
        }
        ~DSContainer()
        {
            for (auto frame : frames)
            {
                delete frame;
            }
        }
        void SaveFrame(DSFrame *frame)
        {
            this->frames.emplace_back(frame);
        }

        void NextFrame()
        {
            if (currentFrame < frames.size() - 1)
            {
                currentFrame++;
            }
        }
        void PrevFrame()
        {
            if (currentFrame > 0)
            {
                currentFrame--;
            }
        }
        void SetFrame(int i)
        {
            currentFrame = i;
        }
        int GetFrame()
        {
            return currentFrame;
        }
        int GetSize()
        {
            return frames.size();
        }
        void Draw()
        {
            if (frames.size() > currentFrame && currentFrame >= 0)
            {
                frames[currentFrame]->Draw();
            }
           
        }
    };

    TRex() {}

    static Tigr *screen;

    static std::map<std::string, DSContainer> namedContainers;

    static std::string currentDS;

    static bool waitingForInput;

    class ButtonEvent
    {
    public:
        virtual void Activate() = 0;
    };

#pragma region ButtonEvents
    class NextDS : public ButtonEvent
    {
    public:
        void Activate()
        {
            std::map<std::string, DSContainer>::iterator it = namedContainers.begin();
            for (it; it != namedContainers.end(); ++it)
            {
                if (it->first == currentDS)
                { // find the current data structuer

                    it++; // get the next data structure
                    if (it == namedContainers.end())
                    {
                        currentDS = namedContainers.begin()->first;
                    }
                    else
                    {
                        currentDS = it->first;
                    }
                    break;
                }
            }
        }
    };
    class PrevDS : public ButtonEvent
    {
    public:
        void Activate()
        {
            std::map<std::string, DSContainer>::iterator it = namedContainers.begin();
            for (it; it != namedContainers.end(); ++it)
            {
                if (it->first == currentDS)
                { // find the current data structure

                    // get the previous data structure
                    if (it == namedContainers.begin())
                    {
                        it = namedContainers.end();
                    }
                    it--;
                    currentDS = it->first;
                    break;
                }
            }
        }
    };
    class NextFrame : public ButtonEvent
    {
    public:
        void Activate()
        {
            namedContainers[currentDS].NextFrame();
        }
    };
    class PrevFrame : public ButtonEvent
    {
    public:
        void Activate()
        {
            namedContainers[currentDS].PrevFrame();
        }
    };
#pragma endregion

    static void DrawWindow()
    {

        if (currentDS == "")
        {
            auto it = namedContainers.begin();
            currentDS = it->first;
        }
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        DrawUI();
        DrawDS();
    }

    static void DrawCenterText(int x, int y, std::string text)
    {

        int textXCenter = tigrTextWidth(tfont, text.c_str()) / 2;  // text.size() * 4;
        int textYcenter = tigrTextHeight(tfont, text.c_str()) / 2; // assume there are no new lines
        tigrPrint(screen, tfont, x - textXCenter, y - textYcenter, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

    static void DrawButton(int x, int y, int width, int height, std::string text, ButtonEvent &buttonEvent)
    {

        width = std::max(width, tigrTextWidth(tfont, text.c_str()) / 2) + 4;

        TPixel neutral = tigrRGB(200, 200, 200);
        TPixel highlight = tigrRGB(230, 230, 230);
        TPixel selected = tigrRGB(170, 170, 170);

        int xCenter = x + (0.5 * width);
        int yCenter = y + (0.5 * height);

        int mx;
        int my;
        int input; // 1 is left click

        tigrMouse(screen, &mx, &my, &input);

        if (mx >= x && mx <= x + width && my >= y && my <= y + height)
        {
            if (input == 1)
            {
                // button selected
                tigrFill(screen, x, y, width, height, selected);
                waitingForInput = false;
            }
            else
            {
                // button Highlighted
                tigrFill(screen, x, y, width, height, highlight);
                if (waitingForInput == false)
                {

                    // ACTIVATE EVENT HERE
                    buttonEvent.Activate();
                }
                waitingForInput = true;
            }
        }
        else
        {
            // button at neutral
            tigrFill(screen, x, y, width, height, neutral);
            // waitingForInput = true;
        }

        DrawCenterText(xCenter, yCenter, text);
    }

    class SliderEvent
    {
    public:
        virtual void Activate(int frame) = 0;
    };

#pragma region SliderEvent
    class GoToSFrame : public SliderEvent
    {
    public:
        void Activate(int frame)
        {
            namedContainers[currentDS].SetFrame(frame);
            std::cout << namedContainers[currentDS].GetSize() << std::endl;
        }
    };
#pragma endregion

    static void DrawSlider(int x, int y, int width, int height, SliderEvent &sliderEvent)
    {
        Tigr *backdrop = tigrBitmap(screen->w, screen->h);
        Tigr *slider = tigrBitmap(screen->w, screen->h);

        int barHeight = height * .5;
        int barWidth = width * .5;
        int innerBarHeight = barHeight * .95;
        int innerBarWidth = barWidth * .95;
        int barX = x - barWidth;
        int barMaxX = barX + barWidth * 2;
        int barY = y - barHeight;
        int barMaxY = barY + barHeight * 2;

        int sliderHW = (barHeight * 2) * 1.2;
        int sliderRightMax = x + barWidth - (sliderHW / 2) - 1;
        int sliderLeftMax = x - barWidth + (sliderHW / 2) - 1;
        int sliderLength = sliderRightMax - sliderLeftMax;
        int successfulClicks = 0;
        int containerSize = namedContainers[currentDS].GetSize();

        // Sets slider knob to left of bar if not used yet
        if (initialSlider)
        {
            sliderX = sliderLeftMax;
            sliderY = y - 1;
            initialSlider = false;
        }

        // Calculates and displays the current value of the slider
        double sliderValue = ((double)sliderX - (double)sliderLeftMax) / (double)sliderLength;
        tigrPrint(backdrop, tfont, width * .5 - (tigrTextWidth(tfont, std::to_string(sliderValue).c_str()) / 2), height * .1, tigrRGB(23, 46, 89), std::to_string(sliderValue).c_str());
        // Create slider bar
        tigrFillRect(backdrop, barX, barY, (barWidth * 2), (barHeight * 2), tigrRGB(128, 128, 128));
        tigrFillRect(backdrop, x - innerBarWidth, y - innerBarHeight, innerBarWidth * 2, innerBarHeight * 2, tigrRGB(100, 100, 100));
        tigrFillRect(backdrop, -1, -1, 3, 3, tigrRGB(57, 234, 123));

        // Slider knob creation
        tigrFillRect(slider, sliderX, sliderY, sliderHW, sliderHW, tigrRGB(0, 0, 0));

        int mX, mY, mB;
        tigrMouse(screen, &mX, &mY, &mB);
        if (mB & 1)
        {
            // Moves slider if dragging
            if (prev && (mX >= sliderX - (sliderHW / 2) && mX < sliderX + (sliderHW / 2)) && (mY >= sliderY && mY < sliderY + sliderHW) && (sliderX <= sliderRightMax) && (sliderX >= sliderLeftMax))
            {
                if (prevx < mX && sliderX != sliderRightMax)
                {
                    sliderX++;
                    sliderEvent.Activate(sliderValue * containerSize);
                }
                else if (prevx > mX && sliderX != sliderLeftMax)
                {
                    sliderX--;
                    sliderEvent.Activate(sliderValue * containerSize);
                }
            }
            // Functionality that moves slider if clicking on bar
            else if (prev && (mX >= barX && mX <= barMaxX) && (mY >= barY && mY <= barMaxY))
            {
                if (mX <= sliderRightMax && mX >= sliderLeftMax)
                {
                    sliderX = mX;
                    sliderEvent.Activate(containerSize * sliderValue);
                }
                else if (mX < sliderLeftMax)
                {
                    sliderX = sliderLeftMax;
                    sliderEvent.Activate(0);
                }
                else if (mX > sliderRightMax)
                {
                    sliderX = sliderRightMax;
                    sliderEvent.Activate(containerSize - 1);
                }
            }
            prevx = mX;
            prevy = mY;
            prev = 1;
        }
        else
        {
            prev = 0;
        }

        // Clips slider to the screen
        tigrBlit(screen, backdrop, barX, barY, barX, barY, width, height);
        tigrBlit(screen, slider, sliderX - 10, sliderY - 10, sliderX + 1, sliderY + 1, sliderHW - (sliderHW * .083333), sliderHW - (sliderHW * .083333));
    }

    static void DrawUI()
    {
        // Only shows frame traversal buttons if there are more than 1 frame
        bool frameTraversalVisible = true;
        if (namedContainers[currentDS].GetSize() <= 1)
            frameTraversalVisible = false;
        DrawCenterText(screen->w / 2, 15, currentDS);
        PrevDS x;
        DrawButton(screen->w / 2 - 15 - 90, 5, 30, 30, "PREV.", x);
        NextDS y;
        DrawButton(screen->w / 2 - 15 + 90, 5, 30, 30, "NEXT", y);
        PrevFrame z;
        NextFrame a;
        GoToSFrame b;
        if (frameTraversalVisible)
        {
            DrawButton(screen->w / 2 - 15 - 90, screen->h - 35, 30, 30, "PREV.", z);
            DrawButton(screen->w / 2 - 15 + 90, screen->h - 35, 30, 30, "NEXT", a);
            DrawSlider(screen->w / 2, screen->h - 35, 100, 20, b);
        }
    }

    static void DrawDS()
    {
        namedContainers[currentDS].Draw();
        
    }

public:
    void operator=(const TRex &) = delete;

    template <typename T>
        requires arithmetic<T>
    static void Log(std::vector<T> dataStructure, std::string dsName)
    {


        if (!namedContainers.contains(dsName))
        {
 
            namedContainers[dsName] = DSContainer();
            std::cout << "New data structure found, instantiating " << dsName << std::endl;
        }

        namedContainers[dsName].SaveFrame(new VectorNumFrame(dataStructure));

        bool displayNext = false;
        while (displayNext) // this will be used to implement a delay  between logs
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
            
        }
    }

    template <typename T>
        requires totallyOrdered<T>
    static void Log(std::vector<T> dataStructure, std::string dsName)
    {
        if (!namedContainers.contains(dsName) && dataStructure.size() > 0)
        {
            namedContainers[dsName] = DSContainer();
            std::cout << "New data structure found, instantiating " << dsName << std::endl;
        }
        else
        {
            return;
        }

        namedContainers[dsName].SaveFrame(new VectorOrderedFrame(dataStructure));

        bool displayNext = false;
        while (displayNext) // this will be used to implement a delay  between logs
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
        }
    }

    static void End()
    {
        while (!tigrClosed(screen))
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
        }
        tigrFree(screen);
        atexit(DataCleanup);
    }
    static void DataCleanup()
    {
        std::cout << "Cleaning up all DSDebug data." << std::endl;
    }
};

Tigr *TRex::screen = tigrWindow(640, 480, "DSDebug", 0);
std::map<std::string, TRex::DSContainer> TRex::namedContainers{};
std::string TRex::currentDS = "";
bool TRex::waitingForInput = true;