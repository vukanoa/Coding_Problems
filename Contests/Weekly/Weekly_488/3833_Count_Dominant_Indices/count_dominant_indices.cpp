/*
    ============
    === EASY ===
    ============

    ============================
    3833) Count Dominant Indices
    ============================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    An element at index i is called dominant if: nums[i] > average(nums[i + 1],
    nums[i + 2], ..., nums[n - 1])

    Your task is to count the number of indices i that are dominant.

    The average of a set of numbers is the value obtained by adding all the
    numbers together and dividing the sum by the total number of numbers.

    =====
    Note: The rightmost element of any array is not dominant. 
    =====

    =================================================
    FUNCTION: int dominantIndices(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,4,3]
    Output: 2
    Explanation:
        At index i = 0, the value 5 is dominant as 5 > average(4, 3) = 3.5.
        At index i = 1, the value 4 is dominant over the subarray [3].
        Index i = 2 is not dominant as there are no elements to its right.
        Thus, the answer is 2.

    --- Example 2 ---
    Input: nums = [4,1,2]
    Output: 1
    Explanation:
        At index i = 0, the value 4 is dominant over the subarray [1, 2].
        At index i = 1, the value 1 is not dominant.
        Index i = 2 is not dominant as there are no elements to its right.
        Thus, the answer is 1.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int dominantIndices(vector<int>& nums)
    {
        const int N = nums.size();

        if (N <= 1)
            return 0;

        int result = 0;
        vector<double> suffix_avg(N, 0.0);
        suffix_avg[N-1] = nums.back();

        int elems = 1;
        int sum   = nums.back();
        for (int i = N-2; i >= 0; i--)
        {
            sum += nums[i];
            ++elems;

            suffix_avg[i] = 1.0 * sum / elems;
        }

        for (int i = N-2; i >= 0; i--)
        {
            if (1.0 * nums[i] > suffix_avg[i])
                ++result;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    WIthout using extra space.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int dominantIndices(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            int count = i;

            int number = nums[N-1 - i]; // ith index from the OPPOSITE side
            if (number * count > sum) 
                ++result;

            sum += number;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but some people may find this more useful.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int dominantIndices(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int sum = 0;
        for (int i = N-1; i >= 0; i--)
        {
            int count = N-1 - i;

            int number = nums[i];
            if (number * count > sum)
                ++result;

            sum += number;
        }

        return result;
    }
};
