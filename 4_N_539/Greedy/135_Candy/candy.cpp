#include <iostream>
#include <vector>
#include <numeric>

/*
    ============
    === HARD ===
    ============

    ===========================
    135) Candy
    ===========================

    ============
    Description:
    ============

    There are n children standing in a line. Each child is assigned a rating
    value given in the integer array ratings.

    You are giving candies to these children subjected to the following
    requirements:

        Each child must have at least one candy.  Children with a higher rating
        get more candies than their neighbors.

    Return the minimum number of candies you need to have to distribute the
    candies to the children.

    ==========================================
    FUNCTION: int candy(vector<int>& ratings);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ratings = [1,0,2]
    Output: 5
    Explanation: You can allocate to the first, second and third child with 2,
                 1, 2 candies respectively.


    --- Example 2 ---
    Input: ratings = [1,2,2]
    Output: 4
    Explanation: You can allocate to the first, second and third child with 1,
                 2, 1 candies respectively.  The third child gets 1 candy
                 because it satisfies the above two conditions.


    *** Constraints ***
    n == ratings.length
    1 <= n <= 2 * 10^4
    0 <= ratings[i] <= 2 * 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.89% */
/* Space Beats: 41.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int candy(std::vector<int>& ratings)
    {
        const int n = ratings.size();
        std::vector<int> candies(n, 1);

        for (int i = 0; i < n; i++)
        {
            if (i-1 >= 0 && ratings[i-1] < ratings[i])
                candies[i] = candies[i-1] + 1;
        }

        for (int i = n-1; i >= 0; i--)
        {
            if (i+1 < n && ratings[i] > ratings[i+1] && candies[i] <= candies[i+1])
                candies[i] = candies[i+1] + 1;
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};
