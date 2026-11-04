/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3733) Minimum Time to Complete All Deliveries
    =============================================

    ============
    Description:
    ============

    You are given two integer arrays of size 2: d = [d1, d2] and r = [r1, r2].

    Two delivery drones are tasked with completing a specific number of
    deliveries. Drone i must complete di deliveries.

    Each delivery takes exactly one hour and only one drone can make a delivery
    at any given hour.

    Additionally, both drones require recharging at specific intervals during
    which they cannot make deliveries. Drone i must recharge every ri hours
    (i.e. at hours that are multiples of ri).

    Return an integer denoting the minimum total time (in hours) required to
    complete all deliveries.

    ================================================================
    FUNCTION: long long minimumTime(vector<int>& d, vector<int>& r);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: d = [3,1], r = [2,3]
    Output: 5
    Explanation:
        The first drone delivers at hours 1, 3, 5 (recharges at hours 2, 4).
        The second drone delivers at hour 2 (recharges at hour 3).

    --- Example 2 ---
    Input: d = [1,3], r = [2,2]
    Output: 7
    Explanation:
        The first drone delivers at hour 3 (recharges at hours 2, 4, 6).
        The second drone delivers at hours 1, 5, 7 (recharges at hours 2, 4, 6)

    --- Example 3 ---
    Input: d = [2,1], r = [3,4]
    Output: 3
    Explanation:
        The first drone delivers at hours 1, 2 (recharges at hour 3).
        The second drone delivers at hour 3.


    *** Constraints ***
    d = [d1, d2]
    1 <= di <= 10^9
    r = [r1, r2]
    2 <= ri <= 3 * 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.87% */
/* Space Beats: 61.07% */

/* Time  Complexity: O(log(D) + log(min(r[0], r[1]))) */
/* Space Complexity: O(1)                             */
class Solution {
public:
    long long minimumTime(vector<int>& d, vector<int>& r)
    {
        long long lcm = my_lcm(r[0], r[1]);

        long long start = 0;
        long long end   = 2LL * (d[0] + d[1]);

        while (start < end)
        {
            long long mid = start + (end - start) / 2;

            if (is_possible(mid, d, r, lcm))
                end = mid;
            else
                start = mid + 1;
        }

        return start;
    }

private:
    long long my_gcd(int a, int b)
    {
        while (b > 0)
        {
            int tmp = b;

            b = a % b;
            a = tmp;
        }

        return a;
    }

    long long my_lcm(int a, int b)
    {
        return 1LL * (a / my_gcd(a, b)) * b;
    }

    bool is_possible(long long total_time, vector<int>& d, vector<int>& r, long long lcm)
    {
        long long available_0 = total_time - total_time / r[0];
        long long available_1 = total_time - total_time / r[1];

        long long available_total = total_time - total_time / lcm;

        return (available_0     >= 1LL * d[0]       ) &&
               (available_1     >= 1LL * d[1]       ) &&
               (available_total >= 1LL * d[0] + d[1]);
    }
};
