/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2594) Minimum Time to Repair Cars
    =================================

    ============
    Description:
    ============

    You are given an integer array ranks representing the ranks of some
    mechanics. ranksi is the rank of the ith mechanic. A mechanic with a rank
    r can repair n cars in r * n2 minutes.

    You are also given an integer cars representing the total number of cars
    waiting in the garage to be repaired.

    Return the minimum time taken to repair all the cars.

    =====
    Note: All the mechanics can repair the cars simultaneously.
    =====

    =============================================================
    FUNCTION: long long repairCars(vector<int>& ranks, int cars);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ranks = [4,2,3,1], cars = 10
    Output: 16
    Explanation:
    - The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
    - The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
    - The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
    - The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
    It can be proved that the cars cannot be repaired in less than 16 minutes.

    --- Example 2 ---
    Input: ranks = [5,1,8], cars = 6
    Output: 16
    Explanation:
    - The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
    - The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
    - The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
    It can be proved that the cars cannot be repaired in less than 16 minutes.


    *** Constraints ***
    1 <= ranks.length <= 10^5
    1 <= ranks[i] <= 100
    1 <= cars <= 10^6

*/

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.80% */
/* Space Beats: 11.11% */

/* Time  Complexity: O(n + max_rank * log(m * max_rank)) */
/* Space Complexity: O(max_rank)                         */
class Solution {
public:
    long repairCars(vector<int>& ranks, int cars)
    {
        int min_rank = *min_element(ranks.begin(), ranks.end());
        int max_rank = *max_element(ranks.begin(), ranks.end());

        // Frequency array to count mechanics with each rank
        vector<int> freq(max_rank + 1);
        for (const int& rank : ranks)
            freq[rank]++;

        long long L = 1;                            // Min possible time
        long long R = 1LL * min_rank * cars * cars; // Max possible time

        // Perform binary search to find the minimum time required
        while (L < R)
        {
            long long mid = L + (R - L) / 2;

            long long cars_repaired = 0;

            // Calc the total number of cars that can be repaired in 'mid' time
            for (int rank = 1; rank <= max_rank; rank++)
                cars_repaired += freq[rank] * static_cast<long long>(sqrt(mid / static_cast<long long>(rank)));

            if (cars_repaired >= cars)
                R = mid;
            else
                L = mid + 1;
        }

        return L;
    }
};
