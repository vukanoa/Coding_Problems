#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1518) Water Bottles
    ===========================

    ============
    Description:
    ============

    There are numBottles water bottles that are initially full of water. You
    can exchange numExchange empty water bottles from the market with one full
    water bottle.

    The operation of drinking a full water bottle turns it into an empty
    bottle.

    Given the two integers numBottles and numExchange, return the maximum
    number of water bottles you can drink.

    ===============================================================
    FUNCTION: int numWaterBottles(int numBottles, int numExchange); 
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numBottles = 9, numExchange = 3
    Output: 13
    Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
    Number of water bottles you can drink: 9 + 3 + 1 = 13.

    --- Example 2 ---
    Input: numBottles = 15, numExchange = 4
    Output: 19
    Explanation: You can exchange 4 empty bottles to get 1 full water bottle. 
    Number of water bottles you can drink: 15 + 3 + 1 = 19.

    *** Constraints ***
    1 <= numBottles <= 100
    2 <= numExchange <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive.

*/

/* Time  Beats: 53.84% */
/* Space Beats: 72.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        int result = 0;
        int emptyBottles = 0;

        while (numBottles > 0)
        {
            result += numBottles;

            int totalEmpty = numBottles + emptyBottles;

            emptyBottles = totalEmpty % numExchange;
            numBottles   = totalEmpty / numExchange;
        }

        return result;
    }
};
