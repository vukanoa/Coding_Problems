/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    3143) Maximum Points Inside the Square
    ======================================

    ============
    Description:
    ============


    You are given a 2D array points and a string s where, points[i] represents
    the coordinates of point i, and s[i] represents the tag of point i.

    A valid square is a square centered at the origin (0, 0), has edges
    parallel to the axes, and does not contain two points with the same tag.

    Return the maximum number of points contained in a valid square.

    =====
    Note: A point is considered to be inside the square if it lies on or within
          the square's boundaries. The side length of the square can be zero.
    =====

    ===========================================================================
    FUNCTION: int maxPointsInsideSquare(vector<vector<int>>& points, string s);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
    Output: 2
    Explanation:
    The square of side length 4 covers two points points[0] and points[1].

    --- Example 2 ---
    Input: points = [[1,1],[-2,-2],[-2,2]], s = "abb"
    Output: 1
    Explanation:
    The square of side length 2 covers one point, which is points[0].

    --- Example 3 ---
    Input: points = [[1,1],[-1,-1],[2,-2]], s = "ccd"
    Output: 0
    Explanation:
    It's impossible to make any valid squares centered at the origin such that
    it covers only one point among points[0] and points[1].


    *** Constraints ***
    1 <= s.length, points.length <= 10^5
    points[i].length == 2
    -10^9 <= points[i][0], points[i][1] <= 10^9
    s.length == points.length
    points consists of distinct coordinates.
    s consists only of lowercase English letters.

*/

#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 9.62% */
/* Space Beats: 6.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s)
    {
        const int N = points.size();
        int result = 0;

        unordered_map<char,vector<vector<int>>> umap;
        for (int i = 0; i < N; i++)
            umap[s[i]].push_back(points[i]);

        // threshold.first  <==> Has to be BELOW OR EQUAL to threshold.first
        // threshold.second <==> This tag has ONE points that is BELOW OR EQUAL
        vector<pair<int,bool>> threshold(26, pair<int,bool>(-1, false));

        for (const auto& entry : umap) // O(26)
        {
            const char& chr                            = entry.first;
            const vector<vector<int>> vector_of_points = entry.second;

            // O(N)
            int min_larger_coord = INT_MAX;
            for (const vector<int>& point : vector_of_points)
            {
                min_larger_coord = min(min_larger_coord, max(abs(point[0]), abs(point[1])));
            }

            // O(N)
            int count = 0;
            for (const vector<int>& point : vector_of_points)
            {
                if (max(abs(point[0]), abs(point[1])) <= min_larger_coord)
                    count++;
            }

            if (count > 1)
            {
                threshold[chr - 'a'].first = min_larger_coord - 1;
            }
            else
            {
                threshold[chr - 'a'].first  = min_larger_coord;
                threshold[chr - 'a'].second = true;
            }
        }

        vector<int> expandable_up_to(26, INT_MAX);
        for (const auto& entry : umap) // O(26)
        {
            const char& chr                            = entry.first;
            const vector<vector<int>> vector_of_points = entry.second;

            // O(N)
            int maximum_expansion = INT_MAX;
            for (const vector<int>& point : vector_of_points)
            {
                if (max(abs(point[0]), abs(point[1])) <= threshold[chr - 'a'].first)
                    continue;

                maximum_expansion = min(maximum_expansion, max(abs(point[0]), abs(point[1])) - 1);
            }

            if (maximum_expansion < INT_MAX)
                expandable_up_to[chr - 'a'] = maximum_expansion;
        }

        // O(N)
        // "limit" <==> Max value for a/2(half of the side) to NOT contain two
        // points with the same tag
        int limit = *min_element(expandable_up_to.begin(), expandable_up_to.end());


        // O(26)
        for (int i = 0; i < 26; i++)
        {
            if (threshold[i].first > -1 && threshold[i].first <= limit)
                result += threshold[i].second ? 1 : 0;
        }

        return result;
    }
};
