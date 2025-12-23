/*
    ============
    === HARD ===
    ============

    ===========================
    587) Erect the Fence
    ===========================

    ============
    Description:
    ============

    You are given an array trees where trees[i] = [xi, yi] represents the
    location of a tree in the garden.

    Fence the entire garden using the minimum length of rope, as it is
    expensive. The garden is well-fenced only if all the trees are enclosed.

    Return the coordinates of trees that are exactly located on the fence
    perimeter. You may return the answer in any order.

    =====================================================================
    FUNCTION: vector<vector<int>> outerTrees(vector<vector<int>>& trees);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
    Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
    Explanation: All the trees will be on the perimeter of the fence except the
                 tree at [2, 2], which will be inside the fence.

    --- Example 2 ---
    Input: trees = [[1,2],[2,2],[4,2]]
    Output: [[4,2],[2,2],[1,2]]
    Explanation: The fence forms a line that passes through all the trees.


    *** Constraints ***
    1 <= trees.length <= 3000
    trees[i].length == 2
    0 <= xi, yi <= 100
    All the given positions are unique.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.47% */
/* Space Beats: 54.23% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) 
    {
        vector<vector<int>> convex_hull;
        const int N = trees.size();

        auto cmp = [&](vector<int>& a, vector<int>& b) 
        {
            if (a[0] < b[0])
            {
                return true;
            }
            else if (a[0] == b[0] && a[1] < b[1])
            {
                return true;
            }

            return false;
        };

        /* Sort */
        sort(trees.begin(), trees.end(), cmp);

        // Lower hull
        for (int i = 0; i < N; i++) 
        {
            while (convex_hull.size() > 1 && !is_clockwise_turn(convex_hull[convex_hull.size() - 2], convex_hull[convex_hull.size() - 1], trees[i])) 
            {
                convex_hull.pop_back();
            }
            convex_hull.push_back(trees[i]);
        }

        // Upper hull
        for (int i = N - 1; i >= 0; i--) 
        {
            while (convex_hull.size() > 1 && !is_clockwise_turn(convex_hull[convex_hull.size() - 2], convex_hull[convex_hull.size() - 1], trees[i])) 
            {
                convex_hull.pop_back();
            }
            convex_hull.push_back(trees[i]);
        }

        convex_hull.pop_back(); 

        sort(convex_hull.begin(), convex_hull.end(), cmp);
        convex_hull.erase(unique(convex_hull.begin(), convex_hull.end()), convex_hull.end());

        return convex_hull;
    }

private:
    bool is_clockwise_turn(vector<int>& a, vector<int>& b, vector<int>& c) 
    {
        int xa = a[0];
        int xb = b[0];
        int xc = c[0];

        int ya = a[1];
        int yb = b[1];
        int yc = c[1];

        bool is_convex = (((yc - yb) * (xb - xa)) - ((yb - ya) * (xc - xb))) >= 0;

        return is_convex;
    }
};
