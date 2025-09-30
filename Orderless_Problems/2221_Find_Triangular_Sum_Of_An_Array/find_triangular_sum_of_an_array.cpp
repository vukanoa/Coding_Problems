/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    2221) Find Triangular Sum of an Array
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums, where nums[i] is a digit
    between 0 and 9 (inclusive).

    The triangular sum of nums is the value of the only element present in nums
    after the following process terminates:

        + Let nums comprise of n elements. If n == 1, end the process.
          Otherwise, create a new 0-indexed integer array newNums of length
          n - 1.

        + For each index i, where 0 <= i < n - 1, assign the value of
          newNums[i] as (nums[i] + nums[i+1]) % 10, where % denotes modulo
          operator.

        + Replace the array nums with newNums.

        + Repeat the entire process starting from step 1.

    Return the triangular sum of nums.

    ===============================================
    FUNCTION: int triangularSum(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5]
    Output: 8
    Explanation: The above diagram depicts the process from which we obtain the
                 triangular sum of the array.

    --- Example 2 ---
    Input: nums = [5]
    Output: 5
    Explanation: Since there is only one element in nums, the triangular sum is
                 the value of that element itself.


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] <= 9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. The most easy "MEDIUM" problem on entire LeetCode.

*/

/* Time  Beats: 65.79% */
/* Space Beats: 60.31% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int triangularSum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int process_count = 1; // 1-indexed
        while (process_count < N)
        {
            for (int i = 0; i < N - process_count; i++)
                nums[i] = (nums[i] + nums[i+1]) % 10;

            process_count++;
        }

        return nums[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    This one requires extensive explanation, but essentially if you've solved:

        119. Pascal's Triangle II

    you should be well equipped to solve this one too. Just take it slowly.

*/

/* Time  Beats: 89.32% */
/* Space Beats: 44.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
static vector<int> modular_inverse(10, 0);
class Solution_Linear {
public:
    int triangularSum(vector<int> &nums)
    {
        const int total_elements = nums.size() - 1;

        initialize_modular_inverse();
        auto binomial_coefficients = compute_combinations(total_elements);

        int final_sum_mod_10 = 0;
        for (int i = 0; i <= total_elements; i++)
        {
            final_sum_mod_10 = (final_sum_mod_10 + binomial_coefficients[i] * nums[i]) % 10;
        }

        return final_sum_mod_10;
    }

private:
    // factor_triplet = {exponent of 2, exponent of 5, factor coprime to 2 and 5 mod 10}
    using factor_triplet = vector<int>;

    static void initialize_modular_inverse()
    {
        if (modular_inverse[1] == 1)
            return;

        modular_inverse[1] = 1;
        modular_inverse[3] = 7;
        modular_inverse[7] = 3;
        modular_inverse[9] = 9;
    }

    static factor_triplet factorize_integer(unsigned value)
    {
        int exponent_two = count_trailing_zeros(value);
        value >>= exponent_two;

        int exponent_five = 0;
        while (value % 5 == 0)
        {
            value /= 5;
            exponent_five++;
        }

        value %= 10;
        return {exponent_two, exponent_five, int(value)};
    }

    static factor_triplet multiply_triplets(const factor_triplet &lhs, const factor_triplet &rhs)
    {
        return {lhs[0] + rhs[0],
                lhs[1] + rhs[1],
                lhs[2] * rhs[2] % 10};
    }

    static factor_triplet divide_triplets(const factor_triplet &numerator, const factor_triplet &denominator)
    {
        return {numerator[0] - denominator[0],
                numerator[1] - denominator[1],
                numerator[2] * modular_inverse[denominator[2]] % 10};
    }

    static int compute_power(int base, int exponent)
    {
        if (exponent == 0)
            return 1;

        int result_if_odd = (exponent & 1) ? base : 1;
        return compute_power(base * base, exponent >> 1) * result_if_odd;
    }

    static int triplet_to_integer(const factor_triplet &triplet)
    {
        return (compute_power(5, triplet[1]) << triplet[0]) * triplet[2] % 10;
    }

    static vector<int> compute_combinations(int n)
    {
        vector<factor_triplet> combination_triplets(n + 1, factor_triplet(3, 0));
        vector<int> result(n + 1);

        combination_triplets[0] = {0, 0, 1};
        combination_triplets[n] = {0, 0, 1};
        result[0] = 1;
        result[n] = 1;

        for (int k = 1; k <= n / 2; k++)
        {
            combination_triplets[k] = divide_triplets(multiply_triplets(combination_triplets[k - 1],
                                                      factorize_integer(n - k + 1)),
                                                      factorize_integer(k));

            combination_triplets[n - k] = combination_triplets[k];

            result[k] = triplet_to_integer(combination_triplets[k]);
            result[n - k] = result[k];
        }

        return result;
    }

    static int count_trailing_zeros(unsigned value)
    {
        int count = 0;
        while ((value & 1) == 0 && value > 0)
        {
            value >>= 1;
            count++;
        }

        return count;
    }
};
