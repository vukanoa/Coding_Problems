#include <iostream>

/*
    ============
    === HARD ===
    ============

    ============================
    1095) Find In Mountain Array
    ============================

    ============
    Description:
    ============

    (This problem is an interactive problem.)

    You may recall that an array arr is a mountain array if and only if:

        arr.length >= 3
        There exists some i with 0 < i < arr.length - 1 such that:
            arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
            arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

    Given a mountain array mountainArr, return the minimum index such that
    mountainArr.get(index) == target. If such an index does not exist, return
    -1.

    You cannot access the mountain array directly. You may only access the
    array using a MountainArray interface:

        + MountainArray.get(k) returns the element of the array at index k
          (0-indexed).

        + MountainArray.length() returns the length of the array.

    Submissions making more than 100 calls to MountainArray.get will be judged
    Wrong Answer. Also, any solutions that attempt to circumvent the judge will
    result in disqualification.

    ==========================================================================
    FUNCTION: int findInMountainArray(int target, MountainArray &mountainArr);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: array = [1,2,3,4,5,3,1], target = 3
    Output: 2
    Explanation: 3 exists in the array, at index=2 and index=5. Return the
                 minimum index, which is 2.

    --- Example 2 ---
    Input: array = [0,1,2,4,2,1], target = 3
    Output: -1
    Explanation: 3 does not exist in the array, so we return -1.


    *** Constraints ***
    3 <= mountain_arr.length() <= 10%4
    0 <= target <= 109
    0 <= mountain_arr.get(index) <= 10^9

*/

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.55% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = mountainArr.length();
        int left  = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            int mid_val  = mountainArr.get(mid);
            int next_val = mountainArr.get(mid + 1);

            if (mid_val < next_val)
                left = mid + 1;
            else
                right = mid;
        }

        int peak_index = left;

        if (mountainArr.get(peak_index) == target)
            return peak_index;

        int left_result = binarySearch(target, mountainArr, 0, peak_index, true);
        if (left_result != -1)
            return left_result;

        int right_result = binarySearch(target, mountainArr, peak_index, n - 1, false);
        return right_result;
    }

    int binarySearch(int target, MountainArray &mountainArr, int left, int right, bool increasing)
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int mid_val = mountainArr.get(mid);

            if (mid_val == target)
            {
                return mid;
            }
            else if (mid_val < target)
            {
                if (increasing)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            else
            {
                if (increasing)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }

        return -1;
    }
};
