/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    1863) Sum of All Subset XOR Totals
    ==================================

    ============
    Description:
    ============

    The XOR total of an array is defined as the bitwise XOR of all its
    elements, or 0 if the array is empty.

        For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.

    Given an array nums, return the sum of all XOR totals for every subset of
    nums.

    Note: Subsets with the same elements should be counted multiple times.

    An array a is a subset of an array b if a can be obtained from b by
    deleting some (possibly zero) elements of b.

    ==============================================
    FUNCTION: int subsetXORSum(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3]
    Output: 6
    Explanation: The 4 subsets of [1,3] are:
    - The empty subset has an XOR total of 0.
    - [1] has an XOR total of 1.
    - [3] has an XOR total of 3.
    - [1,3] has an XOR total of 1 XOR 3 = 2.
    0 + 1 + 3 + 2 = 6

    --- Example 2 ---
    Input: nums = [5,1,6]
    Output: 28
    Explanation: The 8 subsets of [5,1,6] are:
    - The empty subset has an XOR total of 0.
    - [5] has an XOR total of 5.
    - [1] has an XOR total of 1.
    - [6] has an XOR total of 6.
    - [5,1] has an XOR total of 5 XOR 1 = 4.
    - [5,6] has an XOR total of 5 XOR 6 = 3.
    - [1,6] has an XOR total of 1 XOR 6 = 7.
    - [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
    0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

    --- Example 3 ---
    Input: nums = [3,4,5,6,7,8]
    Output: 480
    Explanation: The sum of all XOR totals for every subset is 480.


    *** Constraints ***
    1 <= nums.length <= 12
    1 <= nums[i] <= 20

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A Brute Force way.

    1. Generate all of the subsets.
    2. Go through each of the subsets and XOR all of its elements.
    3. Sum all of those XORed results.

*/

/* Time  Beats: 17.12% */
/* Space Beats: 14.59% */

/* Time  Complexity: O(2^n * n) */
/* Space Complexity: O(2^n * n) */
class Solution_Brute_Force {
public:
    int subsetXORSum(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> subsets;
        backtracking(nums, 0, {}, subsets); // Generate all Subsets

        /* XOR each subset and sum all of them */
        int total = 0;
        for (const std::vector<int>& subset : subsets)
        {
            int xors = 0;
            for (const int& num : subset)
                xors ^= num;

            total += xors;
        }

        return total;
    }

private:
    void backtracking(
                      std::vector<int>& nums,
                      int start_from,
                      std::vector<int> current,
                      std::vector<std::vector<int>>& subsets
                     )
    {
        subsets.push_back(current);

        for (int i = start_from; i < nums.size(); i++)
        {
            current.push_back(nums[i]);
            backtracking(nums, i + 1, current, subsets);
            current.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    However, we DON'T have to generate all the subsets first. There is a trick.

    The code calculates the sum of XOR totals for all subsets by accumulating
    the bitwise OR of all elements and then scaling it by 2 ^ (n−1) to account
    for each bit's contribution to the subsets. This leverages the property
    that each bit appears in half of all possible subsets.

    Approach

    Initialization:

        Initialize sumTotal to 0. This variable will be used to accumulate the
        bitwise OR of all elements in the list.


    Accumulation of Bitwise OR:

        + Iterate over each number in the list nums.

        + Use the bitwise OR operator (|=) to combine each number with
          sumTotal. This step ensures that sumTotal will contain all the bits
          set that are set in any of the numbers in the list.

        + Once the iteration is complete, left shift sumTotal by
              (len(nums) - 1) positions.
          This operation multiplies sumTotal by:
              2^(len(nums)−1).

        + The final value of sumTotal after the left shift is returned as the
          result.

    Example: nums = [1, 2, 3]

    sumTotal = 0

    For num = 1: sumTotal |= 1 results in sumTotal = 1 (binary 0001)
    For num = 2: sumTotal |= 2 results in sumTotal = 3 (binary 0011)
    For num = 3: sumTotal |= 3 results in sumTotal = 3 (binary 0011, unchanged)

    Left Shift: sumTotal << 2 (since len(nums) - 1 = 2) results in 3 << 2 which
                is 12 (binary 1100).

    Return: The result is 12.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    int subsetXORSum(vector<int>& nums)
    {
        int total = 0;

        for (const int& num : nums)
            total |= num;

        return total << (nums.size() - 1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Skeleton of a Memoization approach.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.82% */

/* Time  Complexity: O(2^n) */ // Since n <= 12, this is acceptable
/* Space Complexity: O(n)   */
class Solution_Skeleton_of_Memoization {
public:
    int subsetXORSum(vector<int>& nums)
    {
        int result = 0;
        solve(nums, 0, 0, result);

        return result;
    }

private:
    void solve(vector<int>& nums, int pos, int curr_xor, int& result)
    {
        if ((unsigned)pos == nums.size())
        {
            result += curr_xor;
            return;
        }

        solve(nums, pos+1, curr_xor ^ nums[pos], result); // Take
        solve(nums, pos+1, curr_xor            , result); // Skip
    }
};
