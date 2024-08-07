#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1701) Average Waiting Time
    ===========================

    ============
    Description:
    ============

    There is a restaurant with a single chef. You are given an array customers,
    where customers[i] = [arrival_i, time_i]:

        + arrival_i is the arrival time of the ith customer. The arrival times
          are sorted in non-decreasing order.

        + time_i is the time needed to prepare the order of the ith customer.

    When a customer arrives, he gives the chef his order, and the chef starts
    preparing it once he is idle. The customer waits till the chef finishes
    preparing his order. The chef does not prepare food for more than one
    customer at a time. The chef prepares food for customers in the order they
    were given in the input.

    Return the average waiting time of all customers. Solutions within 10-5
    from the actual answer are considered accepted.

    ====================================================================
    FUNCTION: double averageWaitingTime(vector<vector<int>>& customers);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: customers = [[1,2],[2,5],[4,3]]
    Output: 5.00000
    Explanation:
    1) The first customer arrives at time 1, the chef takes his order and
       starts preparing it immediately at time 1, and finishes at time 3, so
       the waiting time of the first customer is 3 - 1 = 2.

    2) The second customer arrives at time 2, the chef takes his order and
       starts preparing it at time 3, and finishes at time 8, so the waiting
       time of the second customer is 8 - 2 = 6.

    3) The third customer arrives at time 4, the chef takes his order and
       starts preparing it at time 8, and finishes at time 11, so the waiting
       time of the third customer is 11 - 4 = 7.

    So the average waiting time = (2 + 6 + 7) / 3 = 5.



    --- Example 2 ---
    Input: customers = [[5,2],[5,4],[10,3],[20,1]]
    Output: 3.25000
    Explanation:
    1) The first customer arrives at time 5, the chef takes his order and
       starts preparing it immediately at time 5, and finishes at time 7, so
       the waiting time of the first customer is 7 - 5 = 2.

    2) The second customer arrives at time 5, the chef takes his order and
       starts preparing it at time 7, and finishes at time 11, so the waiting
       time of the second customer is 11 - 5 = 6.

    3) The third customer arrives at time 10, the chef takes his order and
       starts preparing it at time 11, and finishes at time 14, so the waiting
       time of the third customer is 14 - 10 = 4.

    4) The fourth customer arrives at time 20, the chef takes his order and
       starts preparing it immediately at time 20, and finishes at time 21, so
       the waiting time of the fourth customer is 21 - 20 = 1.

    So the average waiting time = (2 + 6 + 4 + 1) / 4 = 3.25




    *** Constraints ***
    1 <= customers.length <= 10^5
    1 <= arrivali, timei <= 10^4
    arrival_i <= arrival_i+1

*/

/*
    ------------
    --- IDEA ---
    ------------

    It's literally just the most intuitive approach you can come up to.

    It doesn't make sense to calculate the waiting time if the customer has not
    yet arrived, therefore if chef is LESS than arrival time of the i-th
    customer, then make chef be aligned with customer's arrival and use that
    time to calculate the waiting time.

    If, on the other hand, chef is busy while some customer came, then,
    obviously, use that time to count the total waiting time.

    That's literally it. I have no idea why is this a MEDIUM problem.

*/

/* Time  Beats: 79.41%  */
/* Space Beats: 100.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers)
    {
        double result = 0;

        int chef = 1;
        for (auto& one_customer : customers)
        {
            int arrival = one_customer[0];
            int time    = one_customer[1];

            if (chef < arrival)
                chef = arrival;

            result += (chef + time) - arrival;
            chef   += time;
        }

        return result / customers.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Basically the same approach, but using Recursion.

*/

/* Time  Beats: 84.12% */
/* Space Beats: 17.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursive {
public:
    double averageWaitingTime(vector<vector<int>>& customers)
    {
        const int n = customers.size();

        return sum(0, 0, customers) / n;
    }

private:
    double sum(int i, double prepare, vector<vector<int>>& customers)
    {
        const int n = customers.size();

        if (i >= n)
            return 0;

        auto& one_customer = customers[i];

        int arrival = one_customer[0];
        int time    = one_customer[1];

        prepare = std::max(prepare, (double)arrival) + time;

        return prepare - arrival + sum(i+1, prepare, customers);
    }
};
