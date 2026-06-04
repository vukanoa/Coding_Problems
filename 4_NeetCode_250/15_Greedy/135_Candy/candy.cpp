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

/* Time  Beats: 100.00% */
/* Space Beats:  77.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Greedy_Two_Pass {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_One_Pass {
public:
    int candy(vector<int>& ratings)
    {
        const int N = ratings.size();
        int result = N;

        int i = 1;
        while (i < N)
        {
            if (ratings[i-1] == ratings[i])
            {
                i++;
                continue;
            }

            int increment = 0;
            while (i < N && ratings[i-1] < ratings[i])
            {
                increment++;
                result += increment;

                i++;
            }

            int decrement = 0;
            while (i < N && ratings[i-1] > ratings[i])
            {
                decrement++;
                result += decrement;

                i++;
            }

            result -= min(increment, decrement);
        }

        return result;
    }
};
