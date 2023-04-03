#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

/*
*   Assumptions:
*       the coordinates are integers  
*       the file format is: 
            line 1:         number of points - n
            lines 2 - n+1:  pairs of numbers separated by a space - the coordinates
*/

// auxiliary function
vector<pair<int, int>> read(ifstream& fin) {
    // read the number of points (assume they're given in a file - one on each line)
    int n;
    fin >> n;

    // read the points
    vector<pair<int, int>> points;
    points.reserve(n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        fin >> x >> y;
        points.emplace_back(x, y);
    }

    return points;
}

// hash function for pairs
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
    }
};

/*
    n - the number of points
    time complexity: O(n^2) - assuming a good hash (O(1) look up)
    space complexity: O(n)

    Computes the number of rectangles (parallel with the OX, OY axis)
    that can be created using the given points
*/
int countRectangles(vector<pair<int, int>>& points) {

    unordered_set<pair<int, int>, pair_hash> points_set;
    for (pair<int, int> p : points) {
        points_set.insert(p);
    }

    int count = 0;
    int n = points.size();
    // avoid redundance
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = points[i].first;
            int x2 = points[j].first;
            int y1 = points[i].second;
            int y2 = points[j].second;
            // I don't want the same point twice
            // I don't want 2 points on a horizontal/vertical line (included in the first condition)
            // I don't count both diagonals of a rect (hence the ordering of the coordinates)
            if (x1 != x2 && y1 != y2 && x2 > x1 && y2 > y1) {
                // (x1, y1), (x2, y2) => the other 2 points are (x1, y2) and (x2, y1)
                if (points_set.count({x1, y2}) && points_set.count({x2, y1}))
                    count++;
            }
        }
    }

    return count; 
}

int main()
{
    ifstream fin("in.txt");
    vector<pair<int, int>> points = read(fin);
    
    int ans = countRectangles(points);

    cout << ans;

    return 0;
}
