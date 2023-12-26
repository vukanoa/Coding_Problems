#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    1856) Maximum Subarray Min-Product
    ==================================

    ============
    Description:
    ============

    The min-product of an array is equal to the minimum value in the array
    multiplied by the array's sum.

        For example, the array [3,2,5] (minimum value is 2) has a min-product
        of 2 * (3+2+5) = 2 * 10 = 20.

    Given an array of integers nums, return the maximum min-product of any
    non-empty subarray of nums. Since the answer may be large, return it modulo
    109 + 7.

    Note that the min-product should be maximized before performing the modulo
    operation. Testcases are generated such that the maximum min-product
    without modulo will fit in a 64-bit signed integer.

    A subarray is a contiguous part of an array.

    ==================================================
    FUNCTION: int maxSumMinProduct(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,2]
    Output: 14
    Explanation: The maximum min-product is achieved with the subarray [2,3,2]
    (minimum value is 2).  2 * (2+3+2) = 2 * 7 = 14.


    --- Example 2 ---
    Input: nums = [2,3,3,1,2]
    Output: 18
    Explanation: The maximum min-product is achieved with the subarray [3,3]
    (minimum value is 3).  3 * (3+3) = 3 * 6 = 18.


    --- Example 3 ---
    Input: nums = [3,1,5,6,4,2]
    Output: 60
    Explanation: The maximum min-product is achieved with the subarray [5,6,4]
    (minimum value is 4).  4 * (5+6+4) = 4 * 15 = 60.



    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^7

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 91.96% */
/* Space Beats: 29.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Neat {
public:
    int maxSumMinProduct(std::vector<int>& nums)
    {
        const int n = nums.size();
        long result = 0;

        std::vector<long> prefix = {0};

        for (int& num : nums)
            prefix.push_back(prefix.back() + num);

        std::stack<std::pair<int, int>> stack;

        for (int i = 0; i < n; i++)
        {
            int new_start_idx = i;

            while (!stack.empty() && stack.top().second > nums[i])
            {
                int start_idx = stack.top().first;
                int min_val   = stack.top().second;
                stack.pop();

                /*
                    Curr Subarray ==> [start_idx, i) ==> i.e. [start_idx, i-1]

                    However, since vector prefix have 1 extra element at the
                    beginning, we subtract prefix[start_idx] from prefix[i] and
                    not prefix[i-1]
                */
                long sum_of_curr_subarray     = prefix[i] - prefix[start_idx];
                long product_of_curr_subarray = sum_of_curr_subarray * min_val;

                result = std::max(result, product_of_curr_subarray);

                new_start_idx = start_idx;
            }

            stack.push( {new_start_idx, nums[i]} );
        }

        while (!stack.empty())
        {
            int start_idx = stack.top().first;
            int min_val   = stack.top().second;
            stack.pop();

            // prefix[n] is the sum of all the elements in vector nums
            long sum_of_curr_subarray     = prefix[n] - prefix[start_idx];
            long product_of_curr_subarray = sum_of_curr_subarray * min_val;

            result = std::max(result, product_of_curr_subarray);
        }

        return result % 1000000007;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.35% */
/* Space Beats: 67.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxSumMinProduct(std::vector<int>& nums)
    {
        const int n = nums.size();

        long result = 0;
        std::vector<long> prefix(nums.size() + 1);
        std::vector<long> stack;

        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + nums[i];

        for (int i = 0; i <= n; ++i)
        {
            while (!stack.empty() && (i == n || nums[stack.back()] > nums[i]))
            {
                int start_idx = stack.back();
                stack.pop_back();

                long sum = (prefix[i] - prefix[stack.empty() ? 0 : stack.back() + 1]);

                long product = nums[start_idx] * sum;
                result = std::max(result, product);
            }

            stack.push_back(i);
        }

        return result % 1000000007;
    }
};
