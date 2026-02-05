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

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    (Very Similar to LeetCode 875. Koko Eating Bananas)



    In this problem, it's not easy to figure out you should be doing a Binary
    Search because "weights" aren't sorted and you don't immediately see a
    range.

    Also you MUST NOT sort "weights" since in the Description it is said:
        "(in the order given by weights)"

    Therefore, you MUST NOT change the order of these packages.


    Now, since they've asked us to return the "least capacity" possible to be
    able to ship all the packages within "days" days, that indicates there,
    also, is:

        "greatest capacity"

    So, can we notice any "range" here?
    The LEAST possible capacity, in theory, can be and must be exactly 1.

    Why?

    Because the package has to have some weight, right? And since it is an
    integer it certainly cannot be 0, that would be nonsensical.

    Besides the "nonsensically", in the Constraints of this problem, they've
    told us this:

        1 <= weights[i] <= 500

    Therefore, The LEAST possibly capacity is 1.

    However, there's no point having 1 as the LEAST possible capacity if the
    MAXIMAL weight in "weights" vector is GREATER than 1.

    Meaning, our realistic MINIMAL capacity MUST BE at least of the LARGEST
    weight, otherwiwse we wouldn't be able to ship our maximal weight no matter
    how we split it.

    Consider this:

        weights = [3, 5, 7, 19, 24]

    If we have a ship with capacity < 24, we will NEVER be able to ship our
    last package that weighs 24, right?

    We cannot "split it up" or something like that. Therefore, no matter how
    many "days" we have, it's physically impossible.

    Therefore, even in theory, our MINIMAL capacity for our ship is the MAXIMUM
    weight of all of the packages.


    Okay, now let's focus on a GREATEST capacity.

    Is there a GREATEST capacity?
    Well, it could be Infinite(or 500 as they wrote in the Constraints),
    however that is a vast overexaggeration of our needs since we have to do it
    in "days" days.

    But, let's for the sake of the argument ask ourselves: How big would our
    capacity need to be in order to ship all the packages within a SINGLE day?

    That is easy, we'd need a total sum of all the packages.

    So, the GREATEST capacity is the total sum of all the packages because we
    cannot ship it in a less than a SINGLE day even if our capacity is
    INFINITE.

    It's completely irrelevant whether our capacity is:
        1. Total sum of all the packages, or
        2. INFINITE capacity

    We'd still need a whole, ONE, day to ship it.


    We are sure that our "result" will be somewhere between:

        maximum_weight_package   and   total_sum_of_all_packages.
                  ^                              ^
                  |                              |
                 low                            high


    Now we do a Binary Search and check if we can ship them within "days" days
    by using a ship with "mid" capacity.

    If we CANNOT:
        move "low"  pointer to: mid + 1, since [low, mid] is NOT an answer
    else
        move "high" pointer to: mid    , since "mid" still MIGHT be the answer

*/

/* Time  Beats: 66.39% */
/* Space Beats: 18.89% */

/* Time  Complexity: O(N * logM) */ // Where "M" is the MAXIMUM weight package
/* Space Complexity: O(1)        */
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days)
    {
        const int N = weights.size();

        long long low  = *max_element(weights.begin(), weights.end());    // O(N)
        long long high = accumulate(weights.begin(), weights.end(), 0LL); // O(N)

        while (low < high) // O(logM)
        {
            int mid_capacity = low + (high - low) / 2; // Left-leaning mid

            // How many days would we need in order to ship ALL packages with
            // a ship of capacity "mid_capacity"?
            int needed_days   = 0;
            int curr_capacity = 0;
            for (int i = N-1; i >= 0; i--) // O(N)
            {
                if (curr_capacity + weights[i] > mid_capacity)
                {
                    needed_days++;
                    curr_capacity = 0; // Reset
                }

                curr_capacity += weights[i];
            }
            needed_days++; // Count the last day we've been shipping in

            if (needed_days > days)
                low = mid_capacity + 1; // "mid_capacity" is way too small
            else
                high = mid_capacity;
        }

        return static_cast<int>(low);
    }
};
