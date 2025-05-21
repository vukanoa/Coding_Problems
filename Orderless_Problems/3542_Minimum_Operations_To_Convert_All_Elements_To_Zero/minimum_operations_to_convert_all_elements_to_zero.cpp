/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3542) Minimum Operations to Convert All Elements to Zero
    ========================================================

    ============
    Description:
    ============

    You are given an array nums of size n, consisting of non-negative integers.
    Your task is to apply some (possibly zero) operations on the array so that
    all elements become 0.

    In one operation, you can select a

    [i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum
    non-negative integer in that subarray to 0.

    Return the minimum number of operations required to make all elements in
    the array 0.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,2]
    Output: 1
    Explanation:
        Select the subarray [1,1] (which is [2]), where the minimum
        non-negative integer is 2. Setting all occurrences of 2 to 0 results in
        [0,0]. Thus, the minimum number of operations required is 1.


    --- Example 2 ---
    Input: nums = [3,1,2,1]
    Output: 3
    Explanation:
        Select subarray [1,3] (which is [1,2,1]), where the minimum
        non-negative integer is 1. Setting all occurrences of 1 to 0 results in
        [3,0,2,0]. Select subarray [2,2] (which is [2]), where the minimum
        non-negative integer is 2. Setting all occurrences of 2 to 0 results in
        [3,0,0,0]. Select subarray [0,0] (which is [3]), where the minimum
        non-negative integer is 3. Setting all occurrences of 3 to 0 results in
        [0,0,0,0]. Thus, the minimum number of operations required is 3.


    --- Example 3 ---
    Input: nums = [1,2,1,2,1,2]
    Output: 4
    Explanation:
        Select subarray [0,5] (which is [1,2,1,2,1,2]), where the minimum
        non-negative integer is 1. Setting all occurrences of 1 to 0 results in
        [0,2,0,2,0,2]. Select subarray [1,1] (which is [2]), where the minimum
        non-negative integer is 2. Setting all occurrences of 2 to 0 results in
        [0,0,0,2,0,2]. Select subarray [3,3] (which is [2]), where the minimum
        non-negative integer is 2. Setting all occurrences of 2 to 0 results in
        [0,0,0,0,0,2]. Select subarray [5,5] (which is [2]), where the minimum
        non-negative integer is 2. Setting all occurrences of 2 to 0 results in
        [0,0,0,0,0,0]. Thus, the minimum number of operations required is 4.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    0 <= nums[i] <= 10^5

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Monotonic-Stack. It's not the easiest thing in the world to figure
    out that you need to use it, but once you do, the problem becomes trivial.

*/

/* Time  Beats: 90.53% */
/* Space Beats: 99.35% */

/* Time  Complexity: O(N)       */
/* Space Complexity: O(MAX_NUM) */
class Solution {
public:
    inline int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        const     int MAX_NUM = 1e5 + 1;
        constexpr int SIZE    = MAX_NUM + 1;

        bool seen[SIZE]; // This number is found in the Constraints

        /* Allocate space on the Stack */
        memset(seen, 0, sizeof(seen));

        int monotonic_stack[200000];
        int top = 0;

        for (const int& curr_num : nums)
        {
            if (curr_num == 0)
            {
                while (top)
                    seen[monotonic_stack[--top]] = false;

                continue;
            }

            while (top && monotonic_stack[top - 1] > curr_num)
                seen[monotonic_stack[--top]] = false;

            if ( ! seen[curr_num])
            {
                result++;
                seen[curr_num] = true;
            }

            monotonic_stack[top++] = curr_num;
        }

        return result;
    }
};
