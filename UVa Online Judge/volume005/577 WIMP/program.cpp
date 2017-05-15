// WIMP
// UVa ID: 577
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int CLOSE_BOX = 0, ZOOM_BOX = 1, MOTION_BAR = 2, DATA_AREA = 3, EMPTY = -1;

struct window
{
    int id;
    int left, top, right, bottom;
    int fullscreen;

    bool contains(int area, int x, int y)
    {
        int l = left, t = top, r = right, b = bottom;

        if (fullscreen) l = 0, t = 0, r = 1023, b = 1023;
        if (area == CLOSE_BOX) return x >= l && x <= (l + 24) && y >= t && y <= (t + 24);
        if (area == ZOOM_BOX) return x >= (r - 24) && x <= r && y >= t && y <= (t + 24);
        if (area == MOTION_BAR) return x >= (l + 25) && x <= (r - 25) && y >= t && y <= (t + 24);
        if (area == DATA_AREA) return x >= l && x <= r && y >= (t + 25) && y <= b;
    }
};

int windowId = 0;
int mouseX, mouseY, lastMouseX, lastMouseY;
int isMouseDown = 0, isWindowMoving = 0;
int mouseDownArea, mouseDownWindowId;
int mouseUpArea, mouseUpWindowId;
int windowIndex = -1;
map<int, window > windows;
vector<int> zOrder;

void findMouse(int x, int y, int &mouseId, int &mouseArea, int &idx)
{
    mouseId = EMPTY, mouseArea = EMPTY, windowIdex = -1;

    for (int i = 0; i < zOrder.size(); i++)
        for (int area = CLOSE_BOX; area <= DATA_AREA; area++)
            if (windows[zOrder[i]].contains(area, x, y))
                mouseId = zOrder[i], idx = i, mouseArea = area;
}

bool isFullscreen(window w)
{
    return w.left == 0 && w.top == 0 && w.right == 1023 && w.bottom == 1023;
}

void displayWindow(int id)
{
    cout << windows[id].left << ", " << windows[id].top << ", ";
    cout << windows[id].right << ", " << windows[id].bottom << "\n";
}

void moveWindow(int id, int offsetX, int offsetY)
{
    windows[id].left += offsetX;
    windows[id].top += offsetY;
    windows[id].right += offsetX;
    windows[id].bottom += offsetY;
    
    cout << "Moved window " << id << " to ";
    
    displayWindow(id);
}

void createWindow()
{
    int left, top, right, bottom;

    cin >> left >> top >> right >> bottom;
    
    window w = window{windowId, left, top, right, bottom, 0};
    w.fullscreen = isFullscreen(w);
    windows[windowId] = w;
    zOrder.push_back(windowId);

    cout << "Created window " << windowId << " at ";
    cout << left << ", " << top << ", " << right << ", " << bottom << '\n';

    windowId++;
}

void redraw()
{
    for (auto it = zOrder.begin(); it != zOrder.end(); it++)
    {
        window w = windows[*it];
        cout << "Window " << w.id << " at ";
        cout << w.left << ", " << w.top << ", " << w.right << ", " << w.bottom << '\n';
    }
}

void mouseDown()
{
    cin >> mouseX >> mouseY;

    findMouse(mouseX, mouseY, mouseDownWindowId, mouseDownArea, windowIndex);

    if (mouseDownWindowId != EMPTY)
    {
        zOrder.erase(zOrder.begin() + windowIndex);
        zOrder.push_back(mouseDownWindowId);
        cout << "Selected window " << windows[mouseDownWindowId].id << '\n';
    }

    isMouseDown = 1;
    lastMouseX = mouseX, lastMouseY = mouseY;
}

void mouseUp()
{
    cin >> mouseX >> mouseY;

    if (isWindowMoving)
    {
        moveWindow(mouseDownWindowId, mouseX - lastMouseX, mouseY - lastMouseY);
        isWindowMoving = 0;
    }
    else
    {
        findMouse(mouseX, mouseY, mouseUpWindowId, mouseUpArea, windowIndex);

        if (mouseDownWindowId == mouseUpWindowId && mouseDownWindowId != EMPTY && mouseDownArea == mouseUpArea)
        {
            if (mouseUpArea == CLOSE_BOX)
            {
                windows.erase(mouseUpWindowId);
                zOrder.erase(zOrder.begin() + windowIndex);
                cout << "Closed window " << mouseUpWindowId << '\n';
            }
            else if (mouseUpArea == ZOOM_BOX)
            {
                if (windows[mouseUpWindowId].fullscreen)
                {
                    windows[mouseUpWindowId].fullscreen = 0;
                    cout << "Resized window " << mouseUpWindowId << " to ";
                    displayWindow(mouseUpWindowId);
                }
                else
                {
                    windows[mouseUpWindowId].fullscreen = 1;
                    cout << "Resized window " << mouseUpWindowId << " to ";
                    cout << "0, 0, 1023, 1023\n";
                }
            }
        }
    }

    isMouseDown = 0;
}

void mouseMove()
{
    cin >> mouseX >> mouseY;

    if (isMouseDown && mouseDownArea == MOTION_BAR && !windows[mouseDownWindowId].fullscreen)
    {
        moveWindow(mouseDownWindowId, mouseX - lastMouseX, mouseY - lastMouseY);
        isWindowMoving = 1;
    }

    lastMouseX = mouseX, lastMouseY = mouseY;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string action;

    while (cin >> action)
    {
        if (action == "ZZ") break;
        if (action == "CR") { createWindow(); continue; }
        if (action == "RE") { redraw(); continue; }
        if (action == "DN") { mouseDown(); continue; }
        if (action == "UP") { mouseUp(); continue; }
        if (action == "AT") { mouseMove(); continue; }
    }

    return 0;
}
