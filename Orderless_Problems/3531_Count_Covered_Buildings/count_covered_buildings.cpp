/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3531) Count Covered Buildings
    =============================

    ============
    Description:
    ============

    You are given a positive integer n, representing an n x n city. You are
    also given a 2D grid buildings, where buildings[i] = [x, y] denotes a
    unique building located at coordinates [x, y].

    A building is covered if there is at least one building in all four
    directions: left, right, above, and below.

    Return the number of covered buildings.

    ===========================================================================
    FUNCTION: int countCoveredBuildings(int n, vector<vector<int>>& buildings);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
    Output: 1
    Explanation:
        Only building [2,2] is covered as it has at least one building:
            above ([1,2])
            below ([3,2])
            left ([2,1])
            right ([2,3])
        Thus, the count of covered buildings is 1.


    --- Example 2 ---
    Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
    Output: 0
    Explanation:
        No building has at least one building in all four directions.


    --- Example 3 ---
    Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
    Output: 1
    Explanation:
        Only building [3,3] is covered as it has at least one building:
            above ([1,3])
            below ([5,3])
            left ([3,2])
            right ([3,5])
        Thus, the count of covered buildings is 1.


    *** Constraints ***
    2 <= n <= 10^5
    1 <= buildings.length <= 10^5
    buildings[i] = [x, y]
    1 <= x, y <= n
    All coordinates of buildings are unique.

*/

#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.52% */
/* Space Beats: 77.34% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings)
    {
        int result = 0;
        sort(buildings.begin(), buildings.end());

        unordered_map<int, set<int>> umap;
        for (int i = 0; i < buildings.size(); i++)
        {
            int x = buildings[i][0];
            int y = buildings[i][1];

            umap[y].insert(x);
        }

        for (int i = 1; i < buildings.size()-1; i++)
        {
            int x = buildings[i][0];
            int y = buildings[i][1];

            if (buildings[i-1][0] == x && x == buildings[i+1][0])
            {
                auto L = lower_bound(umap[y].begin(), umap[y].end(), 1);
                auto R = lower_bound(umap[y].begin(), umap[y].end(), x + 1);


                if (L != umap[y].end() && *L < x &&
                    R != umap[y].end() && *R > x)
                {
                    result++;
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Memorize the minimum and maximum Y at every X.
    Memorize the minimum and maximum X at every Y.

    Then for every point, check if there are Y points greater and lower for
    this current X.

    And vice verca. Check if there are "lefter" Xs than the current X for this
    Y and if there are "righter" Xs than the current X for this Y.


    It sounds complicated at first, but it's not. Just draw it out and it'll
    make sense.

    Make sure you don't mess up coordinates, as it is very easy to make a
    mistake.

*/

/* Time  Beats: 90.96% */
/* Space Beats: 91.43% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Simple {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings)
    {
        unordered_map<int, pair<int,int>> umap_x;
        unordered_map<int, pair<int,int>> umap_y;

        for (const auto& entry : buildings)
        {
            const int& x = entry[0];
            const int& y = entry[1];

            if (umap_x.find(x) == umap_x.end()) // x does NOT exist in umap_x
                umap_x[x] = {y, y};

            if (umap_y.find(y) == umap_y.end()) // y does NOT exist in umap_y
                umap_y[y] = {x, x};


            umap_x[x].first  = min(umap_x[x].first,  y);
            umap_x[x].second = max(umap_x[x].second, y);

            umap_y[y].first  = min(umap_y[y].first,  x);
            umap_y[y].second = max(umap_y[y].second, x);
        }

        int result = 0;

        for (const auto& entry : buildings)
        {
            const int& x = entry[0];
            const int& y = entry[1];

            if (umap_x[x].first < y && umap_x[x].second > y &&
                umap_y[y].first < x && umap_y[y].second > x)
            {
                result++;
            }
        }

        return result;
    }
};
