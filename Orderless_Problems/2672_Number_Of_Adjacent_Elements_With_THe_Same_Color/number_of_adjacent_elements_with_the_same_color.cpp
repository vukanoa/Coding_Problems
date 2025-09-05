/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    2672) Number of Adjacent Elements With the Same Color
    =====================================================

    ============
    Description:
    ============

    You are given an integer n representing an array colors of length n where
    all elements are set to 0's meaning uncolored. You are also given a 2D
    integer array queries where queries[i] = [indexi, colori]. For the ith query:

        + Set colors[indexi] to colori.

        + Count the number of adjacent pairs in colors which have the same
          color (regardless of colori).

    Return an array answer of the same length as queries where answer[i] is the
    answer to the ith query.

    =========================================================================
    FUNCTION: vector<int> colorTheArray(int n, vector<vector<int>>& queries);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
    Output: [0,1,1,0,2]
    Explanation:
    Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
    After the 1st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
    After the 2nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
    After the 3rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
    After the 4th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
    After the 5th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.


    --- Example 2 ---
    Input: n = 1, queries = [[0,100000]]
    Output: [0]
    Explanation:
    After the 1st query colors = [100000]. The count of adjacent pairs with the
    same color is 0.


    *** Constraints ***
    1 <= n <= 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 2
    0 <= indexi <= n - 1
    1 <=  colori <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.39% */
/* Space Beats: 98.53% */

/* Time  Complexity: O(Q)     */ // Where 'Q' is "QUERY_SIZE"
/* Space Complexity: O(N + Q) */
class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries)
    {
        const int QUERY_SIZE = queries.size();
        vector<int> result(QUERY_SIZE, 0);

        vector<int> color(n, 0);

        int adjacent = 0;
        for (int q_idx = 0; q_idx < QUERY_SIZE; q_idx++)
        {
            int idx       = queries[q_idx][0];
            int new_color = queries[q_idx][1];

            int prev_color = color[idx];

            if (idx > 0)
            {
                if (prev_color != 0 && color[idx - 1] == prev_color)
                    adjacent--;
            }

            if (idx < n - 1)
            {
                if (prev_color != 0 && prev_color == color[idx + 1])
                    adjacent--;
            }

            color[idx] = new_color;

            if (idx > 0)
            {
                if (color[idx - 1] == new_color)
                    adjacent++;
            }

            if (idx < n - 1)
            {
                if (new_color == color[idx + 1])
                    adjacent++;
            }

            result[q_idx] = adjacent;
        }

        return result;
    }
};
