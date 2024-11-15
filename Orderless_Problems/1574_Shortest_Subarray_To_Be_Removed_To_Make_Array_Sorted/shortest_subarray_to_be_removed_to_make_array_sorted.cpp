#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1574) Shortest Subarray to be Removed to Make Array Sorted
    ==========================================================

    ============
    Description:
    ============

    Given an integer array arr, remove a subarray (can be empty) from arr such
    that the remaining elements in arr are non-decreasing.

    Return the length of the shortest subarray to remove.

    A subarray is a contiguous subsequence of the array.

    =============================================================
    FUNCTION: int findLengthOfShortestSubarray(vector<int>& arr);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,10,4,2,3,5]
    Output: 3
    Explanation: The shortest subarray we can remove is [10,4,2] of length 3.
                 The remaining elements after that will be [1,2,3,3,5] which
                 are sorted. Another correct solution is to remove the subarray
                 [3,10,4].


    --- Example 2 ---
    Input: arr = [5,4,3,2,1]
    Output: 4
    Explanation: Since the array is strictly decreasing, we can only keep a
                 single element. Therefore we need to remove a subarray of
                 length 4, either [5,4,3,2] or [4,3,2,1].


    --- Example 3 ---
    Input: arr = [1,2,3]
    Output: 0
    Explanation: The array is already non-decreasing. We do not need to remove
                 any elements.


    *** Constraints ***
    1 <= arr.length <= 10^5
    0 <= arr[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one requires a lengthy explanation)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.98% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr)
    {
        const int n = arr.size();

        if (strictly_decreasing(arr)) // O(n)
            return n-1;
        else if (non_decreasing(arr)) // O(n)
            return 0;

        int result = 0;

        // O(n)
        /* From which Idx from the back, is the rest of the array sorted? */
        int sorted_from_idx = n; // Out of bounds currently
        for (int i = n-2; i >= 0; i--)
        {
            if (arr[i] > arr[i+1])
            {
                sorted_from_idx = i+1;

                // Or result = sorted_from_idx-1 - 0 + 1
                result = sorted_from_idx; // i.e. we removed elements from [0 to sorted_from_idx-1]
                break;
            }
        }

        // O(n)
        /* Up to which idx is the array in non-decreasing order? */
        int sorted_to_idx = -1; // Out of bounds currently
        for (int i = 1; i < n; i++)
        {
            if (arr[i-1] > arr[i])
            {
                sorted_to_idx = i;
                break;
            }
        }

        // O(n * logn)
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && arr[i-1] > arr[i])
                break;

            if (arr[i] <= arr[sorted_from_idx])
                result = min(result, sorted_from_idx - (i+1));
            else
            {
                // Searching for the leftmost value that is EQUALS TO OR GREATER THAN the target=arr[i]
                auto it = std::lower_bound(arr.begin() + sorted_from_idx, arr.end(), arr[i]); // O(log n)
                if (it == arr.end())
                {
                    result = min(result, n - (i+1));
                    continue;
                }

                int idx = it - arr.begin();

                result = min(result, idx - (i+1));
            }
        }

        result = min(result, n - sorted_to_idx);

        return result;
    }

private:
    // ***************************
    // *** STRICTLY DECREASING ***
    // ***************************
    bool strictly_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] <= arr[i])
                return false;
        }

        return true;
    }


    // **********************
    // *** NON-DECREASING ***
    // **********************
    bool non_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] > arr[i])
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Slight, but VERY important, optimization on the above Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Optimized {
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr)
    {
        const int n = arr.size();

        if (strictly_decreasing(arr)) // O(n)
            return n-1;
        else if (non_decreasing(arr)) // O(n)
            return 0;

        int result = INT_MAX;

        // O(n)
        /* From which Idx from the back, is the rest of the array sorted? */
        int sorted_from_idx = n; // Out of bounds currently
        for (int i = n-2; i >= 0; i--)
        {
            if (arr[i] > arr[i+1])
            {
                sorted_from_idx = i+1;
                break;
            }
        }
        result = min(result, sorted_from_idx); // i.e. we removed elements from [0 to sorted_from_idx-1]
        cout << "\n\t\t\t---Result: " << result;

        // O(n)
        /* Up to which idx is the array in non-decreasing order? */
        int sorted_up_to_idx = -1; // Out of bounds currently
        for (int i = 1; i < n; i++)
        {
            if (arr[i-1] > arr[i])
            {
                sorted_up_to_idx = i;
                break;
            }
        }
        result = min(result, n - sorted_up_to_idx);

        // O(n)
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && arr[i-1] > arr[i])
                break;

            while (sorted_from_idx < n && arr[i] > arr[sorted_from_idx])
                sorted_from_idx++;

            if (sorted_from_idx == n)
                break;

            result = min(result, sorted_from_idx - (i+1));
        }

        return result;
    }

private:
    // ***************************
    // *** STRICTLY DECREASING ***
    // ***************************
    bool strictly_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] <= arr[i])
                return false;
        }

        return true;
    }


    // **********************
    // *** NON-DECREASING ***
    // **********************
    bool non_decreasing(vector<int>& arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i-1] > arr[i])
                return false;
        }

        return true;
    }
};
