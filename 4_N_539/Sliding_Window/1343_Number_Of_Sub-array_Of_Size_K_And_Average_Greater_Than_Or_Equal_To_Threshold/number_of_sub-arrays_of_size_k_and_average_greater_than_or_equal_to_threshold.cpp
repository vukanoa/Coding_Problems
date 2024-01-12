#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================================
    1343) Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
    ===================================================================================

    ============
    Description:
    ============

    Given an array of integers arr and two integers k and threshold, return the
    number of sub-arrays of size k and average greater than or equal to
    threshold.

    =====================================================================
    FUNCTION: int numOfSubarrays(vector<int>& arr, int k, int threshold);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
    Output: 3
    Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and
                 6 respectively. All other sub-arrays of size 3 have averages
                 less than 4 (the threshold).


    --- Example 2 ---
    Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
    Output: 6
    Explanation: The first 6 sub-arrays of size 3 have averages greater than 5.
                 Note that averages are not integers.


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i] <= 10^4
    1 <= k <= arr.length
    0 <= threshold <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Basic Sliding Window technique.

*/

/* Time  Beats: 82.02% */
/* Space Beats: 77.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numOfSubarrays(std::vector<int>& arr, int k, int threshold)
    {
        int result = 0;
        int sum = 0;

        for (int i = 0; i < arr.size(); i++) // Sliding Window
        {
            sum += arr[i];
            int average = sum / k;

            if (i - k + 1 >= 0)
            {
                if (average >= threshold)
                    result++;

                sum -= arr[i - k + 1];
            }
        }

        return result;
    }
};




/* Time  Beats: 83.23% */
/* Space Beats: 60.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold)
    {
        int result = 0;

        int left  = 0;
        int right = 0;

        int sum = 0;
        while (right < arr.size())
        {
            if (right < k-1)
            {
                sum += arr[right];
                right++;
                continue;
            }

            sum += arr[right];
            right++;

            if (sum / k >= threshold)
                result++;

            sum -= arr[left];
            left++;
        }

        return result;
    }
};
