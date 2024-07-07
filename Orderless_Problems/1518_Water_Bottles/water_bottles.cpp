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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 30.43%  */

/* Time  Complexity: O(log(numExhange)) */
/* Space Complexity: O(log(numExchange)) */
class Solution_Recursion {
public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        return numBottles + exchange(numBottles, numExchange);
    }

private:
    int exchange(int numBottles, int numExchange)
    {
        if (numBottles < numExchange)
            return 0;

        auto [full, empty] = std::div(numBottles, numExchange);

        return full + exchange(full + empty, numExchange);
    }

};




/*
    ------------
    --- IDEA ---
    ------------

    As it turns out, we can calculate the number of bottles we can drink with
    just one formula in O(1) time.

        First of all as earlier you can immediately drink numBottles and get
        numBottles empty bottles.

        Every time you trade in numExchange bottles, you get one bottle back.
        Therefore you decrease your number of bottles by numExchange - 1 and
        increase result by 1.

        This suggests a simple division, where you can just divide numBottles
        by numExchange - 1. This doesn't work you can't end up with zero
        bottles. For example if you have 4 bottles and numExchange is 5, you
        can't trade and wind up with 0 bottles; you can't trade at all.

    The "price" of buying a refill is handing over numExchange - 1 empties.
    However, you must have your own empty bottle to receive the refill.

    Therefore after drinking the initial numBottles, you "keep aside" one empty
    for receiving the refills.
    (therefore in fact you use for exchange numBottles - 1) and trade in the
    remaining numBottles - 1 empties to get refills.

    So, you subtract one from each of the numbers you're given, and then
    divide. That says how many full bottles you can get by trading. Add to that
    the number of bottles you started with, and you have the answer

*/

/* Time  Beats: 53.84% */
/* Space Beats: 95.58% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        return numBottles + (numBottles - 1) / (numExchange - 1);
    }
};
