/*
    ============
    === HARD ===
    ============

    ====================================================
    3539) Find Sum of Array Product of Magical Sequences
    ====================================================

    ============
    Description:
    ============

    You are given two integers, m and k, and an integer array nums.
    A sequence of integers seq is called magical if:

        + seq has a size of m.

        + 0 <= seq[i] < nums.length

        + The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1]
          has k set bits.

    The array product of this sequence is defined as
    prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).

    Return the sum of the array products for all valid magical sequences.

    Since the answer may be large, return it modulo 109 + 7.

    A set bit refers to a bit in the binary representation of a number that has
    a value of 1.

    ==========================================================
    FUNCTION: int magicalSum(int m, int k, vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
    Output: 991600007
    Explanation:
    All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an
    array product of 1013.

    --- Example 2 ---
    Input: m = 2, k = 2, nums = [5,4,3,2,1]
    Output: 170
    Explanation:
    The magical sequences are
    [0, 1], [0, 2], [0, 3], [0, 4], [1, 0], [1, 2], [1, 3], [1, 4], [2, 0],
    [2, 1], [2, 3], [2, 4], [3, 0], [3, 1], [3, 2], [3, 4], [4, 0], [4, 1],
    [4, 2], and [4, 3].

    --- Example 3 ---
    Input: m = 1, k = 1, nums = [28]
    Output: 28
    Explanation:
    The only magical sequence is [0].


    *** Constraints ***
    1 <= k <= m <= 30
    1 <= nums.length <= 50
    1 <= nums[i] <= 108

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Not worth your time, trust me)

*/

/* Time  Beats:  8.57% */
/* Space Beats: 40.0% */

/* Time  Complexity: O(N * M^3 * K) */
/* Space Complexity: O(N * M^2 * K) */
class Solution {
private:
    const int MOD = 1e9 + 7;

    long long memo[55][35][35][35];

    bool visited[55][35][35][35];
    vector<vector<long long>> power_of_number;
    vector<vector<long long>> combination_table;
    int total_elements;
    int total_m;
    int total_k;

    long long compute_recursive(int position, int carry, int used, int ones)
    {
        if (position == total_elements)
        {
            int additional_ones = 0;
            int current_carry = carry;

            while (current_carry)
            {
                if (current_carry & 1)
                {
                    additional_ones++;
                }
                current_carry >>= 1;
            }

            return (used == total_m && ones + additional_ones == total_k) ? 1 : 0;
        }

        if (visited[position][carry][used][ones])
        {
            return memo[position][carry][used][ones];
        }

        visited[position][carry][used][ones] = true;
        long long result = 0;

        for (int count = 0; count + used <= total_m; count++)
        {
            int total_sum = carry + count;
            int bit_value = total_sum & 1;
            int next_carry = total_sum >> 1;
            int updated_ones = ones + bit_value;

            long long sub_result = compute_recursive(position + 1, next_carry, used + count, updated_ones);
            if (sub_result == 0)
            {
                continue;
            }

            long long ways_to_choose = combination_table[total_m - used][count];
            long long multiplied_power = power_of_number[position][count];

            result = (result + sub_result * ways_to_choose % MOD * multiplied_power) % MOD;
        }

        memo[position][carry][used][ones] = result;
        return result;
    }

public:
    int magicalSum(int m, int k, vector<int>& nums)
    {
        total_elements = nums.size();
        total_m = m;
        total_k = k;

        power_of_number.assign(total_elements, vector<long long>(m + 1, 1));

        for (int i = 0; i < total_elements; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                power_of_number[i][j] = (power_of_number[i][j - 1] * nums[i]) % MOD;
            }
        }

        combination_table.assign(m + 1, vector<long long>(m + 1, 0));
        for (int i = 0; i <= m; i++)
        {
            combination_table[i][0] = combination_table[i][i] = 1;
            for (int j = 1; j < i; j++)
            {
                combination_table[i][j] = (combination_table[i - 1][j - 1] + combination_table[i - 1][j]) % MOD;
            }
        }

        /* Memset */
        memset(visited, 0, sizeof(visited));

        return static_cast<int>(compute_recursive(0, 0, 0, 0));
    }
};
