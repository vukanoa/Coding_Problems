/*
    ============
    === HARD ===
    ============

    =====================================
    2528) Maximize the Minimum Power City
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array stations of length n, where
    stations[i] represents the number of power stations in the ith city.

    Each power station can provide power to every city in a fixed range. In
    other words, if the range is denoted by r, then a power station at city i
    can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n
    - 1.

    Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10|
    = 7.

    The power of a city is the total number of power stations it is being
    provided power from.

    The government has sanctioned building k more power stations, each of which
    can be built in any city, and have the same range as the pre-existing ones.

    Given the two integers r and k, return the maximum possible minimum power
    of a city, if the additional power stations are built optimally.

    =====
    Note: that you can build the k power stations in multiple cities. 
    =====

    ==================================================================
    FUNCTION: long long maxPower(vector<int>& stations, int r, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stations = [1,2,4,5,0], r = 1, k = 2
    Output: 5
    Explanation: 
    One of the optimal ways is to install both the power stations at city 1. 
    So stations will become [1,4,4,5,0].
    - City 0 is provided by 1 + 4 = 5 power stations.
    - City 1 is provided by 1 + 4 + 4 = 9 power stations.
    - City 2 is provided by 4 + 4 + 5 = 13 power stations.
    - City 3 is provided by 5 + 4 = 9 power stations.
    - City 4 is provided by 5 + 0 = 5 power stations.
    So the minimum power of a city is 5.
    Since it is not possible to obtain a larger power, we return 5.

    --- Example 2 ---
    Input: stations = [4,4,4,4], r = 0, k = 3
    Output: 4
    Explanation: 
    It can be proved that we cannot make the minimum power of a city greater
    than 4.


    *** Constraints ***
    n == stations.length
    1 <= n <= 10^5
    0 <= stations[i] <= 10^5
    0 <= r <= n - 1
    0 <= k <= 10^9

*/

#include <numeric>
#include <vector>
using namespace std;



#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.17% */
/* Space Beats: 77.29% */

/* Time  Complexity: O(N * log(sum(stations) + k)) */
/* Space Complexity: O(N)                          */
class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k)
    {
        const int N = stations.size();

        long long low  = 0;
        long long high = accumulate(stations.begin(), stations.end(), 0LL) + k + 1;

        while (low < high)
        {
            long long mid = low + (high - low) / 2; // Left-leaning mid

            if (check(mid, stations, r, k, N))
                low = mid + 1; // mid is feasible -> move right
            else
                high = mid;    // mid is infeasible -> keep left
        }

        return low - 1; // Last feasible value
    }

    bool check(long long minPower, vector<int> stations, int r, long long k, const int& N)
    {
        // Compute initial power for index 0: sum of stations[0 .. min(N-1, r)]
        int end = min(N, r + 1);
        long long power = accumulate(stations.begin(), stations.begin() + end, 0LL);

        for (int i = 0; i < N; ++i)
        {
            if (power < minPower)
            {
                long long need = minPower - power;
                if (need > k)
                    return false;

                k -= need;

                int idx = min(N - 1, i + r);
                stations[idx] += need; // Greedy add on the right end

                power += need;
            }

            if (i >= r)
                power -= stations[i - r];        // Remove left leaving element

            if (i + r + 1 < N)
                power += stations[i + r + 1];    // Add new right entering element
        }

        return true;
    }
};
