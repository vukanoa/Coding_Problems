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

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Think about what would be a Brute Force for this Problem and then try to
    optimize it.

    Since 'h' is GREATER THAN OR EQUALS to N(i.e. piles.size()) that means that
    Koko would be able to eat all of the bananas within 'h' hours if he eats
    in such a speed that he can eat ANY pile with speed 'k'.

    What is the 'k' value with with which Koko can eat ANY pile?

    Beucase, again, he we know what that value is, then we're certain he can
    finish ALL of the piles within 'h' hours.

    The 'k' value with which we're CERTAIN that Koko would eat ALL of the
    bananas is the maximum-sized pile.

    Think about it. If Koko can eat the BIGGEST pile within 1 hour, then he
    can CERTAINLY eat all of the other piles within 1 hours.

    And since N <= h, we know that if we eat a pile per hour, we'll be able to
    eat all of them.

    It may not be the smallest 'k' value, but it is certainly a 'k' value that
    is a possible result.


    Let's try Brute Force way, iteratively.

    Let's start from k=1 and try to eat all the bananas--How many hours would
    it take?

        Consider the very first example:
        Input:  piles = [3, 6, 7, 11], h = 8
        Output: 4

    We can start from k=1. How many bananas can we eat in h=8?
        Before:     piles = [3, 6, 7, 11]
        Hour 1:     piles = [2, 6, 7, 11] // Eat 1 banana
        Hour 2:     piles = [1, 6, 7, 11] // Eat 1 banana
        Hour 3:     piles = [0, 6, 7, 11] // Eat 1 banana
        Hour 4:     piles = [0, 5, 7, 11] // Eat 1 banana
        Hour 5:     piles = [0, 4, 7, 11] // Eat 1 banana
        Hour 6:     piles = [0, 3, 7, 11] // Eat 1 banana
        Hour 7:     piles = [0, 2, 7, 11] // Eat 1 banana
        Hour 8:     piles = [0, 1, 7, 11] // Eat 1 banana

    We can see that we didn't eat all of them, so we have to increase our k and
    repeat this until we find our 'k' that would result in all eaten bananas.

    Can we optimize this?

    Do we really need to check every single possible 'k' until we find it?
    Is there a more efficient way?

    Yes, there is. Instead of doing a Linear pass for each 'k', we know that
    we can certainly eat all of the bananas with k = max_sized pile.

    Can you se it know?

    We have a range of possible answers:

        1, 2, 3, 4, ... max_sized_pile

    So why would we try each pile Linearly when we can use a Binary Search on
    this answer-space and optimize it by an order of O(log(max_sized_pile)).


    But how do we know how many hours do we need in order to eat all of the
    bananas with a given k_speed value?

    Let's say k = 3. How many bananas can we eat in h = 8?

        piles = [3,6,7,11]

    In how many hours can we eat all the bananas if k = 3?


    piles = [3, 6, 7, 11]
             |  |  |  |
    ----------  |  |  ---------
    |       ____|  |____      |
    |       |          |      v
    |       |          |    ceil(11/3) = 4 hours to eat the fourth(3rd) pile.
    |       |          v
    |       |      ceil(7/3) = 3 hours to eat the third(2nd) pile.
    |       v
    |    ceil(6/2) = 2 hours to eat the second(1st) pile.
    V
    ceil(3/3) = 1 hour to eat the first(0-th) pile.


    Therefore, we need:

        1 + 2 + 3 + 4 = 10 hours

    Is 10 <= h?
    Is 10 <= 8?

    No. That means that if k_speed is 3, we CANNOT eat ALL of the banans within
    h=8 Hours.

    So we don't even need to try k = 1 or k = 2.
    If we can't do it with k = 3, we CERTAINLY CANNOT eat all of them with a
    slower k_speed.

    Therefore we "cut_off" everything left of currently tried k_speed,
    including current k_speed.

    Otherwise, we move our "high" pointer to current k_speed and keep trying
    until we're left with a single element which is GUARANTEED to be the result
    we need.
*/

/* Time  Beats: 71.42% */
/* Space Beats: 76.71% */

/* Time  Complexity: O(N * log(max_element(piles))) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        const int N = piles.size();

        int low  = 1;
        int high = *max_element(piles.begin(), piles.end());

        /* Lower Bound */
        while (low < high)
        {
            // k_speed <==> mid
            int k_speed = low + (high - low) / 2;

            int hours_needed = 0; // To eat all bananas with k_speed
            for (int i = 0; i < N; i++)
                hours_needed += static_cast<int>(ceil(1.0 * piles[i] / k_speed));

            if (hours_needed <= h)
                high = k_speed;    // k_speed still MIGHT be the final answer
            else
                low = k_speed + 1; // Cut-off all [low, k_speed], inclusive
        }

        return low; // Or "high", it does NOT matter
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent to the above Solution, just named and implemented a
    tiny bit different. I think this one is easier to read and grasp.

*/

/* Time  Beats: 71.42% */
/* Space Beats: 76.71% */

/* Time  Complexity: O(N * log(max_element(piles))) */
/* Space Complexity: O(1)                           */
class Solution_Verbose {
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        const int N = piles.size();

        int low  = 1;
        int high = *max_element(piles.begin(), piles.end());

        /* Lower Bound */
        while (low < high)
        {
            // k_speed <==> mid
            int k_speed = low + (high - low) / 2;

            if (can_eat_all_bananas(k_speed, piles, h))
                high = k_speed;    // k_speed still MIGHT be the final answer
            else
                low = k_speed + 1; // Cut-off all [low, k_speed], inclusive
        }

        return low; // Or "high", it does NOT matter
    }

private:
    bool can_eat_all_bananas(int& k_speed, vector<int>& piles, int& h)
    {
        const int N = piles.size();

        int hours_needed = 0; // To eat all bananas with k_speed
        for (int i = 0; i < N; i++)
            hours_needed += static_cast<int>(ceil(1.0 * piles[i] / k_speed));

        return hours_needed <= h;
    }
};
