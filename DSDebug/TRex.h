#pragma once
#include "./Tigr/tigr.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <type_traits>
#include <concepts>
#include <stack>
#include <queue>
#include <typeinfo>
#include <type_traits>

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template <typename T>
concept totallyOrdered = std::totally_ordered<T> && !(std::integral<T> || std::floating_point<T>);



static bool initialSlider = true;
static bool updateSlider = false;
static int sliderX;
static int sliderY;
static int prevx = 0, prevy = 0, prev = 0;


/// <summary>
/// TRex provides the ability to visualize data structures .
/// Targeted at 240 lv students easily.
/// Works on Windows and Linux.
/// </summary>
class TRex
{
private:
    /// <summary>
    /// Abstract class for all data structures. 
    /// Each data structure is made out of an array of DSFrame.
    /// Each frame has a unique draw function allowing for easy developement of variation.
    /// </summary>
    class DSFrame
    {
    public:
        virtual void Draw() = 0;
    };
#pragma region UI
    /// <summary>
    /// Abstract class allowing programmers to give custom functionality to buttons.
    /// </summary>
    class ButtonEvent
    {
    public:
        virtual void Activate() = 0;
    };
    /// <summary>
    /// Draw Window is the main draw function. It draws the UI and the current data structure.
    /// </summary>
    static void DrawWindow()
    {

        if (currentDS == "")
        {
            auto it = namedContainers.begin();
            currentDS = it->first;
        }
        // new bg color
        tigrClear(screen, tigrRGB(122, 115, 255));
        DrawUI();
        DrawDS();
    }


    static void DrawCenterText(int x, int y, std::string text)
    {
        int textXCenter = tigrTextWidth(tfont, text.c_str()) / 2;  // text.size() * 4;
        int textYcenter = tigrTextHeight(tfont, text.c_str()) / 2; // assume there are no new lines
        tigrPrint(screen, tfont, x - textXCenter, y - textYcenter, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

     /// <summary>
     /// Draw a button paired with a button event. 
     /// If the button event is activated it will be activated imediatley after the button is drawn. 
     /// </summary>
    static void DrawButton(int x, int y, int width, int height, std::string text, ButtonEvent &buttonEvent)
    {
        width = std::max(width, tigrTextWidth(tfont, text.c_str()) / 2) + 4;

        TPixel neutral = tigrRGB(48, 45, 102);
        TPixel highlight = tigrRGB(81, 76, 173);
        TPixel selected = tigrRGB(48, 45, 102);

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
            tigrRect(screen, x, y, width, height, neutral);
            // waitingForInput = true;
        }

        DrawCenterText(xCenter, yCenter + 2, text);
    }
#pragma endregion
#pragma region DataStructures
public:
    /// <summary>
    /// The Node object is used to create a n-ary tree data structure.
    /// Users of the TRex library can create a vector of nodes and pass it into the log function.
    /// </summary>
    class Node
    {
    public:
        std::string name;
        std::vector<int> childIndicies;
        Node(std::string n)
        {
            name = n;
        }
        void AddChild(int index)
        {
            childIndicies.push_back(index);
        }
    };

private:


    template <typename T>
    class StackFrame : public DSFrame
    {
    private:
        std::vector<T> data;
        int size;
        int remainderCount;
        int currentFrame;

    public:
        StackFrame(std::vector<T> stack, int queueSize, int frame, int remaining = 0)
        {
            data = stack;
            size = queueSize;
            remainderCount = remaining;
            currentFrame = frame;
        }

        void Draw()
        {
            int count = 0;
            int spacing = 5;
            int itemCount = data.size();
            int width = 50;
            int y = (width * count) + (spacing * count);
            int textY = 0;
            int yLoc = 0;
            for (auto const &c : data)
            {
                if (size <= 7)
                {
                    y = (width * count) + (spacing * count);
                    width = 50;
                    yLoc = (480 - (width * 2)) - y;
                    textY = (480 - (80)) - y;
                }
                else if (size >= 8 && size <= 13)
                {
                    y = (width * count) + (spacing * count);
                    width = 25;
                    yLoc = (480 - (width * 3)) - y;
                    textY = (480 - (66)) - y;
                }
                else if (size >= 14)
                {
                    spacing = 1;
                    y = (width * count) + (spacing);
                    width = 16;
                    yLoc = (480 - (width * 4)) - y;
                    textY = (480 - (60)) - y;
                }
                if (count <= 24)
                {
                    tigrFillRect(screen, 17, yLoc, 600, (width), tigrRGB(48, 45, 102));
                    std::string text;
                    if (std::is_same_v<std::decay_t<decltype(c)>, std::string>)
                        text = c;
                    else if (std::is_same_v<std::decay_t<decltype(c)>, int>)
                    {
                        char str[50];

#ifdef linux
                        snprintf(str, sizeof(str), "%d", c);
#elif _WIN32
                        sprintf_s(str, "%d", c);
#else
                        
#endif
                        
                        text = str;
                    }
                    else if (std::is_same_v<std::decay_t<decltype(c)>, double>)
                    {
                        char str[50];
#ifdef linux
                        snprintf(str, sizeof(str), "%f", c);
#elif _WIN32
                        sprintf_s(str, "%f", c);
#else
                        
#endif
                        text = str;
                    }
                    else if (std::is_same_v<std::decay_t<decltype(c)>, float>)
                    {
                        char str[50];
#ifdef linux
                        snprintf(str, sizeof(str), "%f", c);
#elif _WIN32
                        sprintf_s(str, "%f", c);
#else
                        
#endif
                        text = str;
                    }

                    char const *valuePrint = text.c_str();
                    tigrPrint(screen, tfont, 320 - (tigrTextWidth(tfont, valuePrint) / 2), textY, tigrRGB(0xFF, 0xFF, 0xFF), valuePrint);
                    count++;
                }
            }
            if (remainderCount > 0 && currentFrame == 25)
            {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values not being shown";
                char const *remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 17, 36, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);
            }
        }
    };

private:
    template <typename T>
    class QueueFrame : public DSFrame
    {
    private:
        std::vector<T> data;
        int size;
        int remainderCount;
        int currentFrame;

    public:
        QueueFrame(std::vector<T> queue, int queueSize, int frame, int remaining = 0)
        {
            data = queue;
            size = queueSize;
            remainderCount = remaining;
            currentFrame = frame;
        }

        void Draw()
        {
            int count = 0;
            int spacing = 5;
            int itemCount = data.size();
            int width = 50;
            int y = (width * count) + (spacing * count);
            int textY = 0;
            int yLoc = 0;
            for (auto const &c : data)
            {
                if (size <= 7)
                {
                    y = (width * count) + (spacing * count);
                    width = 50;
                    yLoc = (480 - (width * 2)) - y;
                    textY = (480 - (80)) - y;
                }
                else if (size >= 8 && size <= 13)
                {
                    y = (width * count) + (spacing * count);
                    width = 25;
                    yLoc = (480 - (width * 3)) - y;
                    textY = (480 - (66)) - y;
                }
                else if (size >= 14)
                {
                    spacing = 1;
                    y = (width * count) + (spacing);
                    width = 16;
                    yLoc = (480 - (width * 4)) - y;
                    textY = (480 - (60)) - y;
                }
                if (count <= 24)
                {
                    tigrFillRect(screen, 17, yLoc, 600, (width), tigrRGB(48, 45, 102));
                    std::string text;
                    if (std::is_same_v<std::decay_t<decltype(c)>, std::string>)
                        text = c;
                    else if (std::is_same_v<std::decay_t<decltype(c)>, int>)
                    {
                        char str[50];
#ifdef linux
                        snprintf(str, sizeof(str), "%d", c);
#elif _WIN32
                        sprintf_s(str, "%d", c);
#else

#endif
                        text = str;
                    }
                    else if (std::is_same_v<std::decay_t<decltype(c)>, double>)
                    {
                        char str[50];
#ifdef linux
                        snprintf(str, sizeof(str), "%f", c);
#elif _WIN32
                        sprintf_s(str, "%f", c);
#else

#endif
                        text = str;
                    }
                    else if (std::is_same_v<std::decay_t<decltype(c)>, float>)
                    {
                        char str[50];
#ifdef linux
                        snprintf(str, sizeof(str),"%f", c);
#elif _WIN32
                        sprintf_s(str, "%f", c);
#else

#endif
                        text = str;
                    }

                    char const *valuePrint = text.c_str();
                    tigrPrint(screen, tfont, 320 - (tigrTextWidth(tfont, valuePrint) / 2), textY, tigrRGB(0xFF, 0xFF, 0xFF), valuePrint);
                    count++;
                }
            }
            if (remainderCount > 0 && currentFrame == 25)
            {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values not being shown";
                char const *remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 17, 36, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);
            }
        }
    };
    /// <summary>
    /// Contains the data and draw function for an n-ary tree data structure;
    /// </summary>
    class TreeFrame : public DSFrame
    {
    private:
        std::vector<Node> data;
        int currentRoot = 0;

        class SelectNode : public ButtonEvent
        {
        public:
            int root;
            TreeFrame *treeFrame;
            SelectNode(TreeFrame *tf, int r)
            {
                root = r;
                treeFrame = tf;
            }
            void Activate()
            {
                treeFrame->currentRoot = root;
                std::cout << "Setting root to node " << root << "!" << std::endl;
            }
        };

    public:
        TreeFrame(std::vector<Node> nodes)
        {
            data = nodes;
        }
        void Draw()
        {
            int x = 17;
            int y = 47;
            int nodeButtonWidth = 100;
            int nodeButtonHeight = 15;
            int nodeButtonSpace = 3;
            int nodeCount = data.size();
            int maxDisplay = 20;
            maxDisplay = std::min(maxDisplay, nodeCount);
            int hiddenNodes = nodeCount - maxDisplay;

            for (int i = 0; i < maxDisplay; i++)
            {
                int offset = ((nodeButtonHeight + nodeButtonSpace) * i);
                SelectNode accessNode = SelectNode(this, i);
                DrawButton(x, y + offset, nodeButtonWidth, nodeButtonHeight, data[i].name, accessNode);
            }
            if (hiddenNodes > 0)
            {
                std::string remainderStr = std::to_string(hiddenNodes) + " more values";
                int offset = ((nodeButtonHeight + nodeButtonSpace) * maxDisplay);
                char const *remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, x + 5, y + offset, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);

                std::string addOnStr = "not being shown";
                char const *addOnPrint = addOnStr.c_str();
                tigrPrint(screen, tfont, x + 5, y + offset + 15, tigrRGB(0xFF, 0xFF, 0xFF), addOnPrint);
            }

            // Draw tree from current root
            DrawCenterText(screen->w * 0.5, y, data[currentRoot].name + " children:");

            for (int i = 0; i < data[currentRoot].childIndicies.size(); i++)
            {

                int childIndex = data[currentRoot].childIndicies[i];

                int offset = ((nodeButtonHeight + nodeButtonSpace) * (i + 1));
                std::string text = data[childIndex].name;

                SelectNode accessChild = SelectNode(this, childIndex);
                DrawButton(screen->w * 0.5 - (0.5 * nodeButtonWidth), y + offset, nodeButtonWidth, nodeButtonHeight, text, accessChild);
            }
        }
    };

    /// <summary>
    /// A frame that can contain an array like data structure for any arithmetic type.
    /// </summary>
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
            for (auto const &c : data)
            {
                // Added to limit the amount of bars that can show on screen at once
                if (barCounter <= 24)
                {
                    // getting width of bar
                    int rectangleWidthMax = 580;
                    double frameMax = *std::max_element(data.begin(), data.end());
                    double barSizePercent = c / double(frameMax);
                    int barSize = rectangleWidthMax * barSizePercent;

                    // print bar
                    tigrFillRect(screen, 17, 47 + offset, barSize, 16, tigrRGB(48, 45, 102));

                    std::string iValue = "" + std::to_string(c);

                    char const *iPrintValue = iValue.c_str();

                    // print number
                    tigrPrint(screen, tfont, 20, 50 + offset, tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);

                    offset += 15;
                }
                else
                {

                    // used to check if there are remaining values offscreen
                    remainderCount++;
                }

                barCounter++;
            }

            // Print how many values remain offscreen if there are more than 25 values
            if (remainderCount > 0)
            {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values";
                char const *remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + offset, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);

                std::string addOnStr = "not being shown";
                char const *addOnPrint = addOnStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + offset + 15, tigrRGB(0xFF, 0xFF, 0xFF), addOnPrint);
            }
        }
    };

    /// <summary>
    /// A single frame of a vector like data structure for any totally ordered type.
    /// </summary>
    template <typename T>
        requires totallyOrdered<T>
    class VectorOrderedFrame : public DSFrame
    {
    private:
        std::vector<T> data;

        // method found here: https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
        template <typename S>
        std::vector<size_t> sort_indexes(const std::vector<S> &v)
        {

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
            for (int val = 0; val < data.size(); val++)
            {
                // Added to limit the amount of bars that can show on screen at once
                if (val <= 24)
                {
                    i = sortedIndex[val];
                    T c = data[i];

                    // getting width of bar
                    int rectangleWidthMax = 580;
                    int barSize = rectangleWidthMax * val / data.size();

                    ////print bar
                    tigrFillRect(screen, 17, 47 + (offset * i), barSize, 16, tigrRGB(48, 45, 102));

                    // determine name
                    std::string iValue = "" + c; // std::to_string(c);

                    char const *iPrintValue = iValue.c_str();

                    // print number
                    tigrPrint(screen, tfont, 20, 50 + (offset * i), tigrRGB(0xFF, 0xFF, 0xFF), iPrintValue);
                }
                else
                {
                    // Print elipses if there is too much on screen
                    remainderCount++;
                    /*std::string elipses = "(...)";
                    char const* elipsesPrint = elipses.c_str();
                    tigrPrint(screen, tfont, 580, 50 + (offset * i) + 15, tigrRGB(0xFF, 0xFF, 0xFF), elipsesPrint);*/
                }
            }

            // Print how many values remain offscreen if there are more than 25 values
            if (remainderCount > 0)
            {
                std::string remainderStr = "There are " + std::to_string(remainderCount) + " more values";
                char const *remainderPrint = remainderStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + (offset * i) + 15, tigrRGB(0xFF, 0xFF, 0xFF), remainderPrint);

                std::string addOnStr = "not being shown";
                char const *addOnPrint = addOnStr.c_str();
                tigrPrint(screen, tfont, 450, 50 + (offset * i) + 30, tigrRGB(0xFF, 0xFF, 0xFF), addOnPrint);
            }
        }
    };

#pragma endregion
    /// <summary>
    /// holds a vector of frames and allows for navigation between them.
    /// </summary>
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
                    initialSlider = true;
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
                    initialSlider = true;
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
            updateSlider = true;
        }
    };
    class PrevFrame : public ButtonEvent
    {
    public:
        void Activate()
        {
            namedContainers[currentDS].PrevFrame();
            updateSlider = true;
        }
    };
#pragma endregion

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
        }
    };
#pragma endregion

    static void DrawSlider(int x, int y, int width, int height, SliderEvent &sliderEvent)
    {
        TPixel neutral = tigrRGB(48, 45, 102);
        TPixel highlight = tigrRGB(81, 76, 173);

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
        int containerSize = namedContainers[currentDS].GetSize() - 1;

        // Sets slider knob to left of bar if not used yet
        if (initialSlider)
        {
            sliderX = ((double)namedContainers[currentDS].GetFrame() / (double)containerSize) * (double)sliderLength + (double)sliderLeftMax;
            sliderY = y - 1;
            initialSlider = false;
        }

        if (updateSlider)
        {
            sliderX = ((double)namedContainers[currentDS].GetFrame() / (double)containerSize) * (double)sliderLength + (double)sliderLeftMax;
            updateSlider = false;
        }

        // Calculates the current value of the slider
        double sliderValue;

        // Create slider bar
        tigrRect(screen, barX, barY, (barWidth * 2), (barHeight * 2), neutral);

        // Slider knob creation
        tigrFill(screen, sliderX - (0.35 * sliderHW), sliderY - (0.35 * sliderHW) + 2, sliderHW * 0.7, sliderHW * 0.7 - 1, highlight);

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
                    sliderValue = ((double)sliderX - (double)sliderLeftMax) / (double)sliderLength;
                    sliderEvent.Activate(sliderValue * containerSize);
                }
                else if (prevx > mX && sliderX != sliderLeftMax)
                {
                    sliderX--;
                    sliderValue = ((double)sliderX - (double)sliderLeftMax) / (double)sliderLength;
                    sliderEvent.Activate(sliderValue * containerSize);
                }
            }
            // Functionality that moves slider if clicking on bar
            else if (prev && (mX >= barX && mX <= barMaxX) && (mY >= barY && mY <= barMaxY) && (mX <= sliderX || mX >= sliderX))
            {
                if (mX <= sliderRightMax && mX >= sliderLeftMax)
                {
                    sliderX = mX;
                    sliderValue = ((double)sliderX - (double)sliderLeftMax) / (double)sliderLength;
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
                    sliderEvent.Activate(containerSize);
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
    }

    static void DrawUI()
    {
        // Only shows frame traversal buttons if there are more than 1 frame
        bool frameTraversalVisible = true;
        if (namedContainers[currentDS].GetSize() <= 1)
            frameTraversalVisible = false;
        DrawCenterText(screen->w / 2 + 2, 22, currentDS);
        int rw = 300;
        tigrRect(screen, (screen->w - rw) / 2 + 2, 5, rw, 30, tigrRGB(48, 45, 102));

        PrevDS x;
        DrawButton(screen->w / 2 - 15 - 150 - 20, 5, 30, 30, "PREV.", x);
        NextDS y;
        DrawButton(screen->w / 2 - 15 + 150 + 20, 5, 30, 30, "NEXT", y);
        PrevFrame z;
        NextFrame a;
        GoToSFrame b;
        if (frameTraversalVisible)
        {
            DrawButton(screen->w / 2 - 15 - 150 - 20, screen->h - 35, 30, 30, "<<", z);
            DrawButton(screen->w / 2 - 15 + 150 + 20, screen->h - 35, 30, 30, ">>", a);
            DrawSlider(screen->w / 2 + 2, screen->h - 35 + 15, 300, 30, b);
        }
    }

    static void DrawDS()
    {
        namedContainers[currentDS].Draw();
    }

public:
    void operator=(const TRex &) = delete;

    static void Log(std::vector<Node> nodes, std::string dsName)
    {
        if (!namedContainers.contains(dsName))
        {
            namedContainers[dsName] = DSContainer();
            std::cout << "New data structure found, instantiating " << dsName << std::endl;
        }
        namedContainers[dsName].SaveFrame(new TreeFrame(nodes));

        bool displayNext = false;
        while (displayNext) // this will be used to implement a delay  between logs
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
        }
    }

    template <typename T>
    static void Log(std::stack<T> dataStructure, std::string dsName)
    {
        if (!namedContainers.contains(dsName))
        {

            namedContainers[dsName] = DSContainer();
            std::cout << "New data structure found, instantiating " << dsName << std::endl;
        }

        std::vector<T> stackContents;
        int size = dataStructure.size();
        int count = 0;
        int remainderCount = 0;
        int frameCount = 0;
        bool maxSize = false;
        int neededPops = size - 24;
        if (neededPops > 0)
        {
            for (int i = 0; i < neededPops; i++)
            {

                dataStructure.pop();
            }
        }
        for (int i = 0; i < size; i++)
        {

            if (count < 24)
            {
                stackContents.push_back(dataStructure.top());
                dataStructure.pop();
                count++;
            }
            else
            {
                maxSize = true;
                remainderCount++;
            }
        }

        if (maxSize)
        {
            size = 24;
        }

        std::reverse(stackContents.begin(), stackContents.end());

        std::vector<T> frame;
        frameCount++;
        namedContainers[dsName].SaveFrame(new StackFrame(frame, size, frameCount, remainderCount));
        for (auto it = stackContents.begin(); it != stackContents.end(); ++it)
        {
            frame.push_back(*it);
            frameCount++;
            namedContainers[dsName].SaveFrame(new StackFrame(frame, size, frameCount, remainderCount));
        }
        for (int i = 0; i < size; i++)
        {
            frame.pop_back();
            frameCount++;
            namedContainers[dsName].SaveFrame(new StackFrame(frame, size, frameCount, remainderCount));
        }

        bool displayNext = false;
        while (displayNext) // this will be used to implement a delay  between logs
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
        }
    }

    template <typename T>
    static void Log(std::queue<T> dataStructure, std::string dsName)
    {
        if (!namedContainers.contains(dsName))
        {
            namedContainers[dsName] = DSContainer();
            std::cout << "New data structure found, instantiating " << dsName << std::endl;
        }

        std::vector<T> queueContents;
        int size = dataStructure.size();
        int count = 0;
        int remainderCount = 0;
        int frameCount = 0;
        bool maxSize = false;
        for (int i = 0; i < size; i++)
        {
            if (count < 24)
            {
                queueContents.insert(queueContents.begin(), dataStructure.front());
                dataStructure.pop();
                count++;
            }
            else
            {
                maxSize = true;
                remainderCount++;
            }
        }

        if (maxSize)
        {
            size = 24;
        }

        std::vector<T> frame;
        frameCount++;
        namedContainers[dsName].SaveFrame(new QueueFrame(frame, size, frameCount, remainderCount));
        for (auto it = queueContents.rbegin(); it != queueContents.rend(); ++it)
        {
            frame.insert(frame.begin(), *it);
            frameCount++;
            namedContainers[dsName].SaveFrame(new QueueFrame(frame, size, frameCount, remainderCount));
        }
        for (int i = 0; i < size; i++)
        {
            frame.pop_back();
            frameCount++;
            namedContainers[dsName].SaveFrame(new QueueFrame(frame, size, frameCount, remainderCount));
        }

        bool displayNext = false;
        while (displayNext) // this will be used to implement a delay  between logs
        {
            tigrUpdate(screen); // checks for user input
            DrawWindow();
        }
    }

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