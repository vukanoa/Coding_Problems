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

#include <vector>
#include <numeric>
using namespace std;

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
    int candy(vector<int>& ratings)
    {
        const int N = ratings.size();
        vector<int> candies(N, 1);

        for (int i = 1; i < N; i++)
        {
            if (ratings[i-1] < ratings[i])
                candies[i] = candies[i-1] + 1;
        }

        for (int i = N-2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i+1] && candies[i] <= candies[i+1])
                candies[i] = candies[i+1] + 1;
        }

        return accumulate(candies.begin(), candies.end(), 0);
    }
};
