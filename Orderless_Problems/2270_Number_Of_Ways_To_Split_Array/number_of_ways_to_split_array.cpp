/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    2270) Number of Ways to Split Array
    ===================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums of length n.

    nums contains a valid split at index i if the following are true:

        The sum of the first i + 1 elements is greater than or equal to the
        sum of the last n - i - 1 elements.

        There is at least one element to the right of i. That is, 0 <= i < n-1

    Return the number of valid splits in nums.

    ==================================================
    FUNCTION: int waysToSplitArray(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,4,-8,7]
    Output: 2
    Explanation:
    There are three ways of splitting nums into two non-empty parts:
    - Split nums at index 0. Then, the first part is [10], and its sum is 10.
      The second part is [4,-8,7], and its sum is 3. Since 10 >= 3, i = 0 is a
      valid split.

    - Split nums at index 1. Then, the first part is [10,4], and its sum is 14.
      The second part is [-8,7], and its sum is -1. Since 14 >= -1, i = 1 is a
      valid split.

    - Split nums at index 2. Then, the first part is [10,4,-8], and its sum
      is 6. The second part is [7], and its sum is 7. Since 6 < 7, i = 2 is not
      a valid split. Thus, the number of valid splits in nums is 2.


    --- Example 2 ---
    Input: nums = [2,3,1,0]
    Output: 2
    Explanation:
    There are two valid splits in nums:
    - Split nums at index 1. Then, the first part is [2,3], and its sum is 5.
      The second part is [1,0], and its sum is 1. Since 5 >= 1, i = 1 is a
      valid split.

    - Split nums at index 2. Then, the first part is [2,3,1], and its sum is 6.
      The second part is [0], and its sum is 0. Since 6 >= 0, i = 2 is a valid
      split.


    *** Constraints ***
    2 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Standard "Prefix" problem. If you're not familiar with this, try solving
    easier ones, but this is one of the most fundamental techniques and
    Buildling Block.

*/

/* Time  Beats: 21.30% */
/* Space Beats: 17.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int waysToSplitArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<long long> prefix(N);
        prefix[0] = nums[0];

        for (int i = 1; i < N; i++)
            prefix[i] = prefix[i - 1] + nums[i];

        for (int i = 0; i < N-1; i++)
        {
            long long left_sum  = prefix[i];
            long long right_sum = prefix[N - 1] - prefix[i];

            if (left_sum >= right_sum)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however here we only use to variables and we are Sliding and
    update left_sum and right_sum each time, making our Space Complexity O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int waysToSplitArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        long long left_sum  = 0;
        long long right_sum = 0;

        for (int num : nums)
            right_sum += num;

        for (int i = 0; i < N - 1; i++)
        {
            left_sum  += nums[i];
            right_sum -= nums[i];

            if (left_sum >= right_sum)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but for some reason, it makes more sense to go backwards
    at least for me.

*/

/* Time  Beats: 58.82% */
/* Space Beats: 87.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_3 {
public:

    int waysToSplitArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        long long  left_sum  = 0;
        long long  right_sum = 0;

        for (int num : nums)
            left_sum += num;

        for (int i = N-2; i >= 0; i--)
        {
            left_sum  -= nums[i+1];
            right_sum += nums[i+1];

            if (left_sum >= right_sum)
                result++;
        }

        return result;
    }
};
