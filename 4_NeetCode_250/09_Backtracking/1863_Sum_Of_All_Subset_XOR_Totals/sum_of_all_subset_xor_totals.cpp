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

#include <numeric>
#include <vector>
using namespace std;


/*
   I highly recommend you read ALL of the Solutions in this file, IN ORDER!

   I've purposefully included many Brute-Forces so that you can see all the
   little optimizations we can do in "Backtracking" problems.

*/

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

/* Time  Complexity: O(2^N * N) */
/* Space Complexity: O(2^N * N) */
class Solution_Brute_Force {
public:
    int subsetXORSum(vector<int>& nums)
    {
        vector<vector<int>> subsets;
        backtracking(nums, 0, {}, subsets); // Generate all Subsets

        /* XOR each subset and sum all of them */
        int total = 0;
        for (const vector<int>& subset : subsets)
        {
            int xors = 0;
            for (const int& num : subset)
                xors ^= num;

            total += xors;
        }

        return total;
    }

private:
    void backtracking(vector<int>& nums, int start, vector<int> curr_subset, vector<vector<int>>& subsets)
    {
        subsets.push_back(curr_subset);

        const int N = nums.size();
        for (int i = start; i < N; i++)
        {
            curr_subset.push_back(nums[i]);
            backtracking(nums, i + 1, curr_subset, subsets);
            curr_subset.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is SLIGHTLY better than the above Brute Force. It's only better in
    terms of Space.

*/

/* Time  Beats: 10.30% */
/* Space Beats: 12.55% */

/* Time  Complexity: O(2^N * N) */
/* Space Complexity: O(N)       */
class Solution_Better_Brute_Force {
public:
    int subsetXORSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        backtracking(0, {}, result, nums);

        return result;
    }

private:
    // O(2^N * N) (entire function)
    void backtracking(int start, vector<int> subset, int& result, vector<int>& nums)
    {
        // O(N)
        result += accumulate(subset.begin(), subset.end(), 0, bit_xor<int>());

        const int N = nums.size();
        if (start == N)
            return;   

        // O(2^N) (entire block)
        for (int i = start; i < N; i++)
        {
            subset.push_back(nums[i]);
            backtracking(i + 1, subset, result, nums);
            subset.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a classic, standard, Backtracking Solution. This was probably the
    point and the "desired" solution for this EASY problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.00% */

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(N)   */
class Solution_Classic_Backtracking {
public:
    int subsetXORSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        backtracking(0, 0, result, nums);

        return result;
    }

private:
    // O(2^N) (entire function)
    void backtracking(int start, int xor_value, int& result, vector<int>& nums)
    {
        result += xor_value;

        const int N = nums.size();
        if (start == N)
            return;

        // O(2^N) (entire block)
        for (int i = start; i < N; i++)
        {
            xor_value ^= nums[i];
            backtracking(i + 1, xor_value, result, nums);
            xor_value ^= nums[i];
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Skeleton of a Memoization approach.

    Even tough this is effectively producing the same result as the above
    "Classic Bactracking" Solution, it is conceptually different.

    This approach here is the standard "Memoization" approach, however since
    N is very small in this problem and since we're told we actually need to
    compute all of the states, we can't really "Memoize", however this is
    really the classic "skeleton" of the "Memoization" technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.82% */

/* Time  Complexity: O(2^N) */ // Since N <= 12, this is acceptable
/* Space Complexity: O(N)   */
class Solution_Skeleton_of_Memoization {
public:
    int subsetXORSum(vector<int>& nums)
    {
        int result = 0;

        solve(0, 0, result, nums);

        return result;
    }

private:
    // O(2^N) (entire function)
    void solve(int idx, int curr_xor, int& result, vector<int>& nums)
    {
        const int N = nums.size();
        if (idx == N)
        {
            result += curr_xor;
            return;
        }

        solve(idx+1, curr_xor ^ nums[idx], result, nums); // Take
        solve(idx+1, curr_xor            , result, nums); // Skip
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a standard "trick" to generate all of the subsets WITHOUT using
    Backtracking.

    However, this produces unnecessarily high Space Complexity, but it's
    beneficial to be aware of this "trick" for other Backtracking problems
    where "subsets" are required.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.14% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(2^N)     */
class Solution_Non_Backtracking_Subset_Trick {
public:
    int subsetXORSum(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> subset_xor_values;
        subset_xor_values.reserve(1 << N); // To prevent reallocations

        for (int i = 0; i < N; i++)
        {
            vector<int> additional_xor_values = {nums[i]};

            for (const int& value : subset_xor_values)
                additional_xor_values.push_back(value ^ nums[i]);

            subset_xor_values.insert(subset_xor_values.end(), additional_xor_values.begin(), additional_xor_values.end());
        }

        return accumulate(subset_xor_values.begin(), subset_xor_values.end(), 0);
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
