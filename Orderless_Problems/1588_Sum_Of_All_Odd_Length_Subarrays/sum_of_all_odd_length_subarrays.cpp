/*
    ============
    === EASY ===
    ============

    =====================================
    1588) Sum of All Odd Length Subarrays
    =====================================

    ============
    Description:
    ============

    Given an array of positive integers arr, return the sum of all possible
    odd-length subarrays of arr.

    A subarray is a contiguous subsequence of the array.

    ---------------
    -- Follow Up --
    ---------------

        Could you solve this problem in O(n) time complexity?


    ======================================================
    FUNCTION: int sumOddLengthSubarrays(vector<int>& arr);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,4,2,5,3]
    Output: 58
    Explanation: The odd-length subarrays of arr and their sums are:
    [1] = 1
    [4] = 4
    [2] = 2
    [5] = 5
    [3] = 3
    [1,4,2] = 7
    [4,2,5] = 11
    [2,5,3] = 10
    [1,4,2,5,3] = 15
    If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

    --- Example 2 ---
    Input: arr = [1,2]
    Output: 3
    Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their
                 sum is 3.

    --- Example 3 ---
    Input: arr = [10,11,12]
    Output: 66


    *** Constraints ***
    1 <= arr.length <= 100
    1 <= arr[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    See number of times every position occurs in all the odd length subarray.
    Multiply the contribution of position with element at that position.

    How to calculate contribution?

    Every element will contribute:
        size of array to its right (n-i) * size of array to its left(i+1)

    Since here we only consider odd length divide it by two (ceil divison)


    Example 
    Given array: arr = [1, 2, 3, 4, 5] (n = 5) and formula (i + 1) * (n - i)

        i = 0, contribution = 1 * 5 = 5
        i = 1, contribution = 2 * 4 = 8
        i = 2, contribution = 3 * 3 = 9
        i = 3, contribution = 4 * 2 = 8
        i = 4, contribution = 5 * 1 = 5




    It took me a while to figure out what it means for Every element will
    contribute:

        size of array to its right (n-i) * size of array to its left(i+1)

    For people who are still confused, please refer to the following
    explanation:

    Given array: arr = [1, 2, 3, 4, 5] (n = 5) and formula (i + 1) * (n - i)

        i = 0, contribution = 1 * 5 = 5
        i = 1, contribution = 2 * 4 = 8
        i = 2, contribution = 3 * 3 = 9
        i = 3, contribution = 4 * 2 = 8
        i = 4, contribution = 5 * 1 = 5

    How to understand the above?

    i + 1 means how many start indices there are to the left  of arr[i] (incl.)
    n - i means how many end   indices there are to the right of arr[i] (incl.)

    Example:
        i     = 2 -> i + 1 = 3
        n - i = 3

        There are 3 start indices to the left of arr[2] (incl.),
        they are:

            i = 0, 1, 2


        There are 3 end index to the right of arr[2] (included),
        they are:

            i = 2, 3, 4

        so there are 3 * 3 = 9 in total subarrays that contains arr[2]
        if we choose start = 0, end = 2, we get [1, 2, 3]
        if we choose start = 2, end = 2, we get [3]
        if we choose start = 2, end = 4, we get [3, 4, 5]

    i     = 4 -> i + 1 = 5
    n - i = 1

    There are 5 start index to the left of arr[4] (incl.),
    they are:

        i = 0, 1, 2, 3, 4

    There are 1 end index to the right of arr[4] (included),
    they are:

        i = 4

    So there are 5 * 1 = 5 in total subarrays that contains arr[4]

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr)
    {
        const int N = arr.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int contribution = ((i + 1) * (N - i) + 1) / 2.0;
            result += contribution * arr[i];
        }

        return result;
    }
};
