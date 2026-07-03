/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    3961) Maximize Sum of Device Ratings
    ====================================

    ============
    Description:
    ============


    You are given a 2D integer array units of size m × n where units[i][j]
    represents the capacity of the jth unit in the ith device. Each device
    contains exactly n units.

    The rating of a device is the minimum capacity among all its units.

    You may perform the following operation any number of times (including
    zero):

        + Choose a device i that has not been used as a source before.

        + Remove exactly one unit from device i and add it to any different
          device.

        + Then mark device i as used, so it cannot be chosen again as a source.

    Return the maximum possible sum of the ratings of all devices after any
    number of such operations.

    =====
    Note: Devices can receive units from multiple devices, regardless of
          whether they have been selected. 

          The rating of an empty device is 0.
    =====

    ===========================================================
    FUNCTION: long long maxRatings(vector<vector<int>>& units);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: units = [[1,3],[2,2]]
    Output: 4
    Explanation:
        Select device i = 0 and transfer units[0][0] = 1 to device i = 1.
        After the transfer, the ratings are:
            Device 0 = [3]: rating[0] = 3
            Device 1 = [2, 2, 1]: rating[1] = 1
        Thus, the sum of ratings is 3 + 1 = 4.


    --- Example 2 ---
    Input: units = [[1,2,3],[4,5,6]]
    Output: 6
    Explanation:
        Select device i = 1 and transfer units[1][0] = 4 to device i = 0.
        After the transfer, the ratings are:
            Device 0 = [1, 2, 3, 4]: rating[0] = 1
            Device 1 = [5, 6]: rating[1] = 5
        Thus, the sum of ratings is 1 + 5 = 6.


    --- Example 3 ---
    Input: units = [[5,5,5],[1,1,1]]
    Output: 6
    Explanation:
        No transfers increase the sum of ratings. Thus, the sum of ratings is 5
        + 1 = 6.


    *** Constraints ***
    1 <= m == units.length <= 10^5
    1 <= n == units[i].length <= 10^5
    m * n <= 2 * 10^5
    1 <= units[i][j] <= 10.5

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    So, the rating of a device is the MINIMUM capacity among all of its units.

    If we choose some device as a source, then THE BEST unit to remove is
    ALWAYS its SMALLEST UNIT because:

        + Removing any other unit does NOT increase the device's rating.

        + Removing the smallest unit changes the rating from the smallest
          element to the second smallest element, thus potentially increasing
          the rating (in case first smallest and second smallest are NOT the
          same unit value)

    Therefore, for every device we ONLY care about:

        curr_first_smallest
        curr_second_smallest


    Now suppose EVERY device contributes it SECOND SMALLEST element to the
    "result", meaning--We remove the FIRST SMALLEST unit from EVERY device.

    However, we MUST transfer all of those FIRST SMALLEST elements somewhere,
    right?

    In order to MAXIMIZE the "result"(i.e. the sum of the ratings), we should
    be GREEDY.

    We should transfer ALL of those FIRST SMALLEST units to a SINGLE device.
    Which device should be that receiving one?

    The one device that containts the GLOBALLY SMALLEST unit.

    Why do we transfer all of the FIRST SMALLEST units specifically to THAT
    device and not some other device?

    Becase by adding FIRST SMALLEST units from other devices is GUARANTEED NOT
    to DECREASE the rating of that receiving device.

    Why?
    Well, because it already has the smallest unit among ALL of the units on
    ALL of the devices. Thus, anything we put there is CERTAINLY NOT going to
    be smaller than the GLOBALLY SMALLEST unit it already has.


    That means that ALL BUT ONE device will contribute to the result with its
    SECOND SMALLEST unit, while EXACTLY ONE will contribute with its FIRST
    SMALLEST(that's the receiving device).

    So the final formula is:

        global_first_smallest + sum_of_ALL_second_smallest_units - global_second_smallest;

*/

/* Time  Beats: 92.73% */
/* Space Beats: 46.29% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maxRatings(vector<vector<int>>& units)
    {
        const int N = units.size();

        if (N == 1)
            return *min_element(units[0].begin(), units[0].end());

        long long sum_of_all_units = 0;
        bool each_device_has_exactly_one_unit = true;

        for (int i = 0; i < N; i++)
        {
            if (units[i].size() == 1)
            {
                sum_of_all_units += units[i][0];
            }
            else
            {
                each_device_has_exactly_one_unit = false;
                break;
            }
        }

        if (each_device_has_exactly_one_unit)
            return sum_of_all_units;

        long long sum_of_ALL_second_smallest_units = 0;
        int global_first_smallest  = INT_MAX;
        int global_second_smallest = INT_MAX;

        for (int i = 0; i < N; i++)
        {
            int curr_first_smallest  = INT_MAX;
            int curr_second_smallest = INT_MAX;

            const int UNITS_ON_CURR_DEVICE = units[i].size();

            for (int unit_idx = 0; unit_idx < UNITS_ON_CURR_DEVICE; unit_idx++)
            {
                if (units[i][unit_idx] < curr_first_smallest)
                {
                    curr_second_smallest = curr_first_smallest;
                    curr_first_smallest  = units[i][unit_idx];
                }
                else if (units[i][unit_idx] < curr_second_smallest)
                {
                    curr_second_smallest = units[i][unit_idx];
                }
            }

            sum_of_ALL_second_smallest_units += curr_second_smallest;

            global_first_smallest  = min(global_first_smallest,  curr_first_smallest);
            global_second_smallest = min(global_second_smallest, curr_second_smallest);
        }

        return global_first_smallest + sum_of_ALL_second_smallest_units - global_second_smallest;
    }
};
