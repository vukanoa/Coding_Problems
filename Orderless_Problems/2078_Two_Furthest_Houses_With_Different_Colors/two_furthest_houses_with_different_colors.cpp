/*
    ============
    === EASY ===
    ============

    ===============================================
    2078) Two Furthest Houses with Different Colors
    ===============================================

    ============
    Description:
    ============

    There are n houses evenly lined up on the street, and each house is
    beautifully painted. You are given a 0-indexed integer array colors of
    length n, where colors[i] represents the color of the ith house.

    Return the maximum distance between two houses with different colors.

    The distance between the ith and jth houses is abs(i - j), where abs(x) is
    the absolute value of x.

    ===============================================
    FUNCTION: int maxDistance(vector<int>& colors);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: colors = [1,1,1,6,1,1,1]
    Output: 3
    Explanation: In the above image, color 1 is blue, and color 6 is red.
    The furthest two houses with different colors are house 0 and house 3.
    House 0 has color 1, and house 3 has color 6. The distance between them is
    abs(0 - 3) = 3. Note that houses 3 and 6 can also produce the optimal
    answer.

    --- Example 2 ---
    Input: colors = [1,8,3,8,3]
    Output: 4
    Explanation: In the above image, color 1 is blue, color 8 is yellow, and
    color 3 is green. The furthest two houses with different colors are house 0
    and house 4. House 0 has color 1, and house 4 has color 3. The distance
    between them is abs(0 - 4) = 4.

    --- Example 3 ---
    Input: colors = [0,1]
    Output: 1
    Explanation: The furthest two houses with different colors are house 0 and
    house 1. House 0 has color 0, and house 1 has color 1. The distance between
    them is abs(0 - 1) = 1.

    *** Constraints ***
    n == colors.length
    2 <= n <= 100
    0 <= colors[i] <= 100
    Test data are generated such that at least two houses have different colors.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  40.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxDistance(vector<int>& colors)
    {
        const int N = colors.size();

        int i = 0;
        int j = N-1;
        while (i < N && j >= 0 && colors[0] == colors[j] && colors[i] == colors[N-1])
        {
            i++; // Increment
            j--; // Decrement
        }

        return max(abs(j - 0), abs(N-1 - i));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.97% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int maxDistance(vector<int>& colors)
    {
        const int N = colors.size();

        for (int i = 0; i < N; i++)
        {
            if ((colors[i] ^ colors[N-1]) | (colors[N-1 - i] ^ colors[0]))
                return N-1 - i;
        }

        return 0;
    }
};
