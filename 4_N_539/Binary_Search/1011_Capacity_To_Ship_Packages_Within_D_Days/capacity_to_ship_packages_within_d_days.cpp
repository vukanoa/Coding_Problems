#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1011) Capacity to Ship Packages Within D Days
    =============================================

    ============
    Description:
    ============

    A conveyor belt has packages that must be shipped from one port to another
    within days days.

    The ith package on the conveyor belt has a weight of weights[i]. Each day,
    we load the ship with packages on the conveyor belt (in the order given by
    weights). We may not load more weight than the maximum weight capacity of
    the ship.

    Return the least weight capacity of the ship that will result in all the
    packages on the conveyor belt being shipped within days days.

    =============================================================
    FUNCTION: int shipWithinDays(vector<int>& weights, int days);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
    Output: 15
    Explanation: A ship capacity of 15 is the minimum to ship all the packages
                 in 5 days like this:
    1st day: 1, 2, 3, 4, 5
    2nd day: 6, 7
    3rd day: 8
    4th day: 9
    5th day: 10

    Note that the cargo must be shipped in the order given, so using a ship of
    capacity 14 and splitting the packages into parts like:
    (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.



    --- Example 2 ---
    Input: weights = [3,2,2,4,1,4], days = 3
    Output: 6
    Explanation: A ship capacity of 6 is the minimum to ship all the packages
                 in 3 days like this:
    1st day: 3, 2
    2nd day: 2, 4
    3rd day: 1, 4



    --- Example 3 ---
    Input: weights = [1,2,3,1,1], days = 4
    Output: 3
    Explanation:
    1st day: 1
    2nd day: 2
    3rd day: 3
    4th day: 1, 1



    *** Constraints ***
    1 <= days <= weights.length <= 5 * 10^4
    1 <= weights[i] <= 500

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Very Similar to LeetCode 875. Koko Eating Bananas)

*/

/* Time  Beats: 94.49% */
/* Space Beats: 13.27% */

// N >> max_element(weights) therefore it's much better than O(N * logN)

/* Time  Complexity: O(N * log(max_element(weights)) ) */
/* Space Complexity: O(N) */
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days)
    {
        int left  = *std::max_element(weights.begin(), weights.end());
        int right = std::accumulate(weights.begin(), weights.end(), 0);

        int result = INT_MAX;

        std::function<bool(int)> can_ship;

        can_ship = [&](int capacity) -> bool
        {
            int ships = 1; // Or days. It's easier to think of more ships imo.
            int curr_capacity = capacity;

            for (int& w : weights)
            {
                if (curr_capacity - w < 0)
                {
                    ships++;
                    curr_capacity = capacity;
                }

                curr_capacity -= w;
            }

            return ships <= days;
        };

        while (left <= right)
        {
            int capacity = left + (right - left) / 2; // Aka "mid"

            if (can_ship(capacity))
            {
                result = std::min(result, capacity);
                right = capacity - 1;
            }
            else
                left  = capacity + 1;
        }

        return result;
    }
};
