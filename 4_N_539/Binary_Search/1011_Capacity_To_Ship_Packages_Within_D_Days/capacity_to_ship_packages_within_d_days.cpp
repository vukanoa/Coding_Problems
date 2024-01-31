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

    (Very Similar to LeetCode 875. Koko Eating Bananas)



    In this problem, it's not easy to figure out you should be doing a Binary
    Search because "weights" aren't sorted and you don't immediately see a
    range.

    Also you MUST NOT sort "weights" since in the Description it is said:
        "(in the order given by weights)"

    Therefore, you must NOT change the order of these packages.


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

    Now, is there a GREATEST capacity?
    Well, it could be Infinite(or 500 as they wrote), however that is a vast
    overexaggeration of our needs since we have to do it in "days" days.

    (It's an overexaggeration for most problem. There are certainly problems
    where the upper bound of 500 is not only optimal, but necessary.)

    But, let's for the sake of the argument(and finding the upper bound) ask
    ourselves - How big would our capacity need to be in order to ship all the
    packages within a SINGLE(1) day?

    That is easy, isn't it? We'd need a total sum of all the packages.

    So, the GREATEST capacity is the total sum of all the packages because we
    cannot ship it in a less than a single(1) day even if our capacity is
    INFINITE.

    It's the same whether our capacity is:
        1. Total sum of all the packages, or
        2. INFINITE capacity

    We'd still need a whole, one, day to ship it.

    Therefore it doesn't make sense to take the greater value out of these two
    options as our "upper bound" since both would produce the same result.

    However, if we want to find our "upper bound" in order to perform a Binary
    Search, then it makes sense to take the lower of the two options because
    our range is going to be shorter and we will not compromise on anything.

    Hence, our "upper bound" is a total sum of all the weights, instead of 500.
    (Sometimes the total sum of all the weights CAN be 500 and ONLY in that
     case will our "upper bound" be 500)

    We are sure that our "result" will be somewhere between 1 and total_sum.
    Now we do a Binary Search and check if we can ship them within "days" days
    with that "mid"(capacity)

    If yes:
        move "right" pointer to the left  and try with a lower  capacity.
    else
        move "left"  pointer to the right and try with a higher capacity.

*/

/* Time  Beats: 99.16% */
/* Space Beats: 12.35% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days)
    {
        int total_sum = std::accumulate(weights.begin(), weights.end(), 0);

        int left  = 1;
        int right = total_sum;

        int least_capacity = INT_MAX;

        while (left <= right)
        {
            int mid = left + (right - left) / 2; // mid <==> capacity

            if (possible_within_days_days(weights, days, mid))
            {
                least_capacity = std::min(least_capacity, mid);
                right = mid - 1;
            }
            else
                left  = mid + 1; // Try with greater capacity
        }

        return least_capacity;
    }

private:
    bool possible_within_days_days(std::vector<int>& weights, int& days, int& capacity)
    {
        int needed_days = 1;
        int curr_capacity = capacity;

        for (int& package_weight : weights)
        {
            if (curr_capacity < package_weight)
            {
                needed_days++;
                curr_capacity = capacity;

                /*
                    This is the exact reason we, in the Solution_2, start
                    our "left" pointer at:

                        *std::max_element(weights.begin(),weights.end())

                    and not at: 1, as in THIS Solution.

                    Our LEAST capacity certainly cannot be LESS THAN the
                    greatest weight of package we have to ship, right?

                    Otherwise, we wouldn't be able to EVER ship all packages
                    because no ship has enough capacity to transport that
                    single package no matter how many days pass.
                */
                if (capacity < package_weight)
                    return false;
            }

            curr_capacity -= package_weight;
        }

        return needed_days <= days;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we have a few changes from the above Solution.

    One change is a pure optimization, as stated in the commented part above.
    We don't have to start our "lower bound", i.e. our "left" pointer all the
    way at 1.

    Why?

    Well, since we are sure that our "upper bound" doesn't have to be 500, as
    specified in the Constraints since that is an overexaggeration, similarly
    we can notice that 1 is an UNDERESTIMATION.

    Consider this example:
        weights = [5, 3, 7, 6, 8, 4]

    Can you ship all these packages, one by one(one per day/ship) where the
    capacity is going to be less than max_element(weights), which is 8 in this
    case?

    Think about it.

    If you take a capacity of 5:
        1st day: package 5
        2nd day: package 3
        3rd day: ??? You CANNOT ship a package of weight 7 if capacity is 5

    No matter how many day passes, if your capacity is LESS THAN any of the
    packages, you won't be able to transport them all.

    Therefore, if you make sure your capacity is GREATER THAN OR EQUALS to the
    greatest package weight on the conveyor belt, you are making sure you can
    ship them all.

    In how many days is the other question, but you know it's possible to ship
    it at least one-by-one.

    Now that you know that, you can try different capacities(greater than that
    one you've just found is the minimum capacity) and see how many days you
    need.


    Also, the below Solution is implemented using Lambda function and a bit
    different coding and naming style.

*/

/* Time  Beats: 94.49% */
/* Space Beats: 13.27% */

/*
    Time  Complexity: O(N * log(max_element(weights)) )

    (N >> max_element(weights))
    N is MUCH GREATER than max_element(weights) therefore:

        O(N * log(max_element(weights)))

    is much better than:

        O(N * logN)
*/
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int shipWithinDays(std::vector<int>& weights, int days)
    {
        int left  = *std::max_element(weights.begin(), weights.end());
        int right = std::accumulate(weights.begin(), weights.end(), 0);

        int result = INT_MAX;

        std::function<bool(int)> possible_to_ship_within_days_days;

        possible_to_ship_within_days_days = [&](int capacity) -> bool
        {
            int needed_days = 1;
            int curr_capacity = capacity;

            for (int& w : weights)
            {
                if (curr_capacity - w < 0)
                {
                    needed_days++;
                    curr_capacity = capacity;
                }

                curr_capacity -= w;
            }

            return needed_days <= days;
        };

        while (left <= right)
        {
            int capacity = left + (right - left) / 2; // Aka "mid"

            if (possible_to_ship_within_days_days(capacity))
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
