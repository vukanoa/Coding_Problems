/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3100) Water Bottles II
    ===========================

    ============
    Description:
    ============

    You are given two integers numBottles and numExchange.

    numBottles represents the number of full water bottles that you initially
    have. In one operation, you can perform one of the following operations:

        Drink any number of full water bottles turning them into empty bottles.
        Exchange numExchange empty bottles with one full water bottle. Then,
        increase numExchange by one.

    Note that you cannot exchange multiple batches of empty bottles for the
    same value of numExchange. For example, if numBottles == 3 and
    numExchange == 1, you cannot exchange 3 empty water bottles for 3 full
    bottles.

    Return the maximum number of water bottles you can drink.

    ===============================================================
    FUNCTION: int maxBottlesDrunk(int numBottles, int numExchange);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numBottles = 13, numExchange = 6
    Output: 15
    Explanation: The table above shows the number of full water bottles, empty
                 water bottles, the value of numExchange, and the number of
                 bottles drunk.

    --- Example 2 ---
    Input: numBottles = 10, numExchange = 3
    Output: 13
    Explanation: The table above shows the number of full water bottles, empty
                 water bottles, the value of numExchange, and the number of
                 bottles drunk.


    *** Constraints ***
    1 <= numBottles <= 100
    1 <= numExchange <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 40.40% */
/* Space Beats: 98.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange)
    {
        int result = 0;
        int empty  = 0;

        while (numBottles != 0 || empty >= numExchange)
        {
            result += numBottles;
            empty  += numBottles;

            numBottles = 0;

            while (empty >= numExchange)
            {
                numBottles++;
                empty -= numExchange;
                numExchange++;
            }
        }

        return result;
    }
};
