#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    875) Koko Eatings Bananas
    ===========================

    ============
    Description:
    ============

    Koko loves to eat bananas. There are n piles of bananas, the ith pile has
    piles[i] bananas. The guards have gone and will come back in h hours.

    Koko can decide her bananas-per-hour eating speed of k. Each hour, she
    chooses some pile of bananas and eats k bananas from that pile. If the pile
    has less than k bananas, she eats all of them instead and will not eat any
    more bananas during this hour.

    Koko likes to eat slowly but still wants to finish eating all the bananas
    before the guards return.

    Return the minimum integer k such that she can eat all the bananas within h
    hours.

    ========================================================
    FUNCTION: int minEatingSpeed(vector<int>& piles, int h);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: piles = [3,6,7,11], h = 8
    Output: 4

    --- Example 2 ---
    Input: piles = [30,11,23,4,20], h = 5
    Output: 30

    --- Example 3 ---
    Input: piles = [30,11,23,4,20], h = 6
    Output: 23


    *** Constraints ***
    1 <= piles.length <= 10^4
    piles.length <= h <= 10^9
    1 <= piles[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Think about what would be a Brute Force for this Problem and then try to
    optimize it.

    It would be to start from k=1 and try to eat all the bananas in given 'h'.
    The first 'k' that successfully does this is the Solution.

    Consider the very first example:
    Input:  piles = [3, 6, 7, 11], h = 8
    Output: 4

    We can start from k=1. How many bananas can we eat in h=8?
    Before:       piles = [3, 6, 7, 11]

    Hour 1: 1     piles = [2, 6, 7, 11]
    Hour 2: 1     piles = [1, 6, 7, 11]
    Hour 3: 1     piles = [0, 6, 7, 11]
    Hour 4: 1     piles = [0, 5, 7, 11]
    Hour 5: 1     piles = [0, 4, 7, 11]
    Hour 6: 1     piles = [0, 3, 7, 11]
    Hour 7: 1     piles = [0, 2, 7, 11]
    Hour 8: 1     piles = [0, 1, 7, 11]

    We can see that we didn't eat all of them, so we have to increase our k and
    repeat this until we find our 'k' that would result in all eaten bananas.

    However, there is a simpler way to check if we can eat all the bananas in
    a given 'h'.
    We can try to divide each pile with current 'k' and round up.
    Add all those rounded up values and you'll get the amount of hours you need
    for that k value, to eat all the bananas.

    Let's see it in action:

    ### OLD WAY ###
    Start from k=2. How many bananas can we eat in h=8?
    Before:       piles = [3, 6, 7, 11]

    Hour 1: 2     piles = [1, 6, 7, 11]
    Hour 2: 2     piles = [0, 6, 7, 11]
    Hour 3: 2     piles = [0, 4, 7, 11]
    Hour 4: 2     piles = [0, 2, 7, 11]
    Hour 5: 2     piles = [0, 0, 5, 11]
    Hour 6: 2     piles = [0, 0, 3, 11]
    Hour 7: 2     piles = [0, 0, 1, 11]
    Hour 8: 2     piles = [0, 0, 0, 11]


    ### NEW WAY ###
    Start from k=2. How many bananas can we eat in h=8?
    piles = [3,6,7,11]

    In how many hours can we eat all the bananas if k=2?
    piles = [3, 6, 7, 11]
             |  |  |  |
    ----------  |  |  ---------
    |       ____|  |____      |
    |       |          |      v
    |       |          |    ceil(11/2) = 6 hours to eat the fourth(3rd) pile.
    |       |          v
    |       |      ceil(7/2) = 4 hours to eat the third(2nd) pile.
    |       v
    |    ceil(6/2) = 3 hours to eat the second(1st) pile.
    V
    ceil(3/2) = 2 hours to eat the first(0-th) pile.

    So: 2 + 3 + 4 + 6 = 15 hours

    Is 15 <= h=8?
    No.

    They told us an important thing in the Description and that is:
    piles.length() <= h

    Which means that it is guaranteed that piles.length() is smaller than or
    equal than the 'h'.

    Why is that important?

    It's important because that helps us know what is the upper bound up to
    which our 'k' can go to.

    Obviously, we can start k from 1, but what is the upper bound?
    The upper bound of value of k must be such that we can eat all the bananas
    in exactly piles.length() steps.

    Now ask yourself - What is that k value?
    It's the maximum value in the vector "piles".

    Okay, so now we know both the lower and the upper bound. Can we use that to
    our advantage somehow?

    Do we really need to go from 1 to max_element(piles) and try each k until
    we find which k results in all bananas being eaten?

    Obviously not.
    Do you see it now?

    Since we have a range [1, 11](in this case) and we know that the result of
    k is in that inclusive range. How can we optimize this Solution?

    Since we've agreed that we don't need to try every possible k, starting
    from 1, we can try using a Binary Search.

    Each time we fail to eat all the bananas, or each time the number of needed
    hours to eat all the bananas is greater than 'h', we're going to cut all
    the options of 'k' that are less than or equal to the current 'k' value.

    'k' value is "mid" in a Binary Search.
*/

/* Time  Beats: 76.01% */
/* Space Beats: 14.52% */

/* Time  Complexity: O(log( max_element(piles) ) * N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, int h)
    {
        int left  = 1;
        int right = *std::max_element(piles.begin(), piles.end());

        int result = right;

        while (left <= right)
        {
            int k = left + (right - left) / 2;

            unsigned hours = 0; // It cannot fit into "int"
            for (int& pile : piles)
                hours += std::ceil(1.0 * pile / k);

            if (hours <= h)
            {
                result = k; // We don't have to do std::min, k will be smaller
                right = k - 1;
            }
            else
                left = k + 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent to the above Solution, just named and implemented a
    tiny bit different. I think this one is easier to read and grasp.

*/

/* Time  Beats: 61.58% */
/* Space Beats: 19.49% */

/* Time  Complexity: O(log( max_element(piles) ) * N) */
/* Space Complexity: O(1) */
class Solution_Verbose {
public:
    int minEatingSpeed(std::vector<int>& piles, int h)
    {
        if (piles.size() == h)
            return *std::max_element(piles.begin(), piles.end());

        int left  = 1;
        int right = *std::max_element(piles.begin(), piles.end());

        int result = right;

        while (left <= right)
        {
            int k = left + (right - left) / 2;

            if (can_eat_all_bananas(piles, h, k))
            {
                result = k; // We don't have to do std::min, k will be smaller
                right = k - 1;
            }
            else
                left  = k + 1;
        }

        return result;
    }

private:
    bool can_eat_all_bananas(std::vector<int>& piles, int&h, int& k)
    {
        unsigned hours = 0;
        for (int i = 0; i < piles.size(); i++)
            hours += std::ceil(1.0 * piles[i] / k);

        return hours <= h;
    }
};
