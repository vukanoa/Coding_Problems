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
class Solution_Monotonic_Stack {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.79% */
/* Space Beats: 17.86% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class FenwickTree {
    vector<int> BIT;
    int len;

public:
    FenwickTree(int size)
    {
        len = size;
        BIT.assign(size + 2, 0);
    }

    void mark(int idx, int val)
    {
        idx++;

        while (idx <= len)
        {
            BIT[idx] += val;
            idx += (idx & -idx);
        }
    }

    int sum(int idx)
    {
        idx++;
        int result = 0;

        while (idx > 0)
        {
            result += BIT[idx];
            idx -= (idx & -idx);
        }

        return result;
    }

    int range_count(int left, int right)
    {
        if (left > right)
            return 0;

        return sum(right) - sum(left - 1);
    }
};


class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int peak = 0;

        for (const int& num : nums)
        {
            if (num > peak)
                peak = num;
        }

        vector<vector<int>> groups(peak + 6);
        group_idx(groups, nums);

        FenwickTree zero_tracker(N);
        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 0)
                zero_tracker.mark(i, 1);
        }

        int result = 0;
        for (int val = 1; val <= peak; val++)
        {
            if ( ! groups[val].empty())
                result += count_operations(groups[val], zero_tracker);
        }

        return result;
    }

private:
    void group_idx(vector<vector<int>>& groups, const vector<int>& vals)
    {
        const int N = vals.size();

        for (int idx = 0; idx < N; idx++)
        {
            if (vals[idx] > 0)
                groups[vals[idx]].push_back(idx);
        }
    }

    int count_operations(const vector<int>& positions, FenwickTree& tracker)
    {
        const int M = positions.size();

        int operations = 0;
        int last_idx = -2;

        for (int it = 0; it < M; it++)
        {
            int curr = positions[it];
            if (last_idx == -2 || tracker.range_count(last_idx + 1, curr - 1) > 0)
                operations++;

            last_idx = curr;
        }

        for (int j = 0; j < M; j++)
            tracker.mark(positions[j], 1);

        return operations;
    }
};
