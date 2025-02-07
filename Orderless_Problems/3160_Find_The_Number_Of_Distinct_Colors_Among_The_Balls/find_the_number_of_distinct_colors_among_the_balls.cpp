/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3160) Find the Number of Distinct Colors Among the Balls
    ========================================================

    ============
    Description:
    ============

    You are given an integer limit and a 2D array queries of size n x 2.

    There are limit + 1 balls with distinct labels in the range [0, limit].
    Initially, all balls are uncolored. For every query in queries that is of
    the form [x, y], you mark ball x with the color y. After each query, you
    need to find the number of distinct colors among the balls.

    Return an array result of length n, where result[i] denotes the number of
    distinct colors after ith query.

    Note that when answering a query, lack of a color will not be considered as
    a color.

    ===========================================================================
    FUNCTION: vector<int> queryResults(int limit, vector<vector<int>>& queries)
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
    Output: [1,2,2,3]
    Explanation:
    After query 0, ball 1 has color 4.
    After query 1, ball 1 has color 4, and ball 2 has color 5.
    After query 2, ball 1 has color 3, and ball 2 has color 5.
    After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color
    4.


    --- Example 2 ---
    Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
    Output: [1,2,2,3,4]
    Explanation:
    After query 0, ball 0 has color 1.
    After query 1, ball 0 has color 1, and ball 1 has color 2.
    After query 2, ball 0 has color 1, and balls 1 and 2 have color 2.
    After query 3, ball 0 has color 1, balls 1 and 2 have color 2, and ball 3
    has color 4.
    After query 4, ball 0 has color 1, balls 1 and 2 have color 2, ball 3 has
    color 4, and ball 4 has color 5.


    *** Constraints ***
    1 <= limit <= 10^9
    1 <= n == queries.length <= 10^5
    queries[i].length == 2
    0 <= queries[i][0] <= limit
    1 <= queries[i][1] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Use of two HashMaps. Once you look at them, the approach reveals itself:

    Example:
        Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4],[4,3]]

    (This is the state of both HashMaps AFTER we've processed all queries)

         Hash Map                             Hash Map
    |  ball :  color  |                  | color :  counter |
    | (key)   (value) |                  | (key)    (value) |
    +-----------------+                  +------------------+
    |   1   :    3    |                  |   4   :    1     |
    +-----------------+                  +------------------+
    |   2   :    5    |                  |   2   :    1     |
    +-----------------+                  +------------------+
    |   3   :    4    |                  |   3   :    2     |
    +-----------------+                  +------------------+

    Read the code and I'm sure you'll get it. That's the easiest way.

*/

/* Time  Beats: 72.35% */
/* Space Beats: 66.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries)
    {
        const int N = queries.size();
        vector<int> results(N, 0);

        unordered_map<int,int> ball_color;
        unordered_map<int,int> color_counter;

        int distinct = 0;
        for (int i = 0; i < N; i++)
        {
            int ball  = queries[i][0];
            int color = queries[i][1];

            if (ball_color.count(ball))
            {
                int prev_color = ball_color[ball];

                color_counter[prev_color]--;
                if (color_counter[prev_color] == 0)
                {
                    color_counter.erase(prev_color);
                    distinct--;
                }
            }

            if (color_counter.count(color) == 0) // Not used
                distinct++;

            ball_color[ball] = color;
            color_counter[color]++;

            results[i] = distinct;
        }

        return results;
    }
};
