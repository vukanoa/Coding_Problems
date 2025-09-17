/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    2607) Make K-Subarray Sums Equal
    ================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array arr and an integer k. The array arr
    is circular. In other words, the first element of the array is the next
    element of the last element, and the last element of the array is the
    previous element of the first element.

    You can do the following operation any number of times:

        + Pick any element from arr and increase or decrease it by 1.

    Return the minimum number of operations such that the sum of each subarray
    of length k is equal.

    A subarray is a contiguous part of the array.

    ==============================================================
    FUNCTION: long long makeSubKSumEqual(vector<int>& arr, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,4,1,3], k = 2
    Output: 1
    Explanation: we can do one operation on index 1 to make its value equal to 3.
    The array after the operation is [1,3,1,3]
    - Subarray starts at index 0 is [1, 3], and its sum is 4 
    - Subarray starts at index 1 is [3, 1], and its sum is 4 
    - Subarray starts at index 2 is [1, 3], and its sum is 4 
    - Subarray starts at index 3 is [3, 1], and its sum is 4 

    --- Example 2 ---
    Input: arr = [2,5,5,7], k = 3
    Output: 5
    Explanation: we can do three operations on index 0 to make its value equal
    to 5 and two operations on index 3 to make its value equal to 5.
    The array after the operations is [5,5,5,5]
    - Subarray starts at index 0 is [5, 5, 5], and its sum is 15
    - Subarray starts at index 1 is [5, 5, 5], and its sum is 15
    - Subarray starts at index 2 is [5, 5, 5], and its sum is 15
    - Subarray starts at index 3 is [5, 5, 5], and its sum is 15 


    *** Constraints ***
    1 <= k <= arr.length <= 10^5
    1 <= arr[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.35% */
/* Space Beats: 91.12% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long makeSubKSumEqual(vector<int>& arr, int k)
    {
        long long N = arr.size();
        long long result = 0LL;

        for (int i = 0; i < k; i++)
        {
            vector<int> curr_cycle;

            for (int j = i; arr[j] != 0; j = (j + k) % N)
            {
                curr_cycle.push_back(arr[j]);
                arr[j] = 0; // Mark visited
            }

            if ( ! curr_cycle.empty())
            {
                const int median_position = curr_cycle.size() / 2;

                // nth_element(first,
                //             nth,
                //             last)
                nth_element(curr_cycle.begin(),
                            curr_cycle.begin() + median_position,
                            curr_cycle.end());

                const int median_value = curr_cycle[median_position];

                for (const int curr_value : curr_cycle)
                    result += abs(curr_value - median_value);

            }
        }

        return result;
    }
};
