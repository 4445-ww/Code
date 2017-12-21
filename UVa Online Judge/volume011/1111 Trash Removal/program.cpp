// Trash Removal
// UVa ID: 1111
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
#include <list>
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

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };
}vertices[110];

double norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> vertices[i].x >> vertices[i].y;
        }
        
        double mostH = 1e9;
        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            
            double maxH = 0;
            for (int k = 0; k < n; k++)
            {
                double h = getDistPL(vertices[k], vertices[i], vertices[j]);
                maxH = max(maxH, h);
            }
            
            mostH = min(mostH, maxH);
        }
        
        cout << "Case " << ++cases << ": " << fixed << setprecision(2) << mostH << '\n';
    }

    return 0;
}