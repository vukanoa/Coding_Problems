#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    89) Gray Code
    ===========================

    ============
    Description:
    ============

    An n-bit gray code sequence is a sequence of 2n integers where:

        + Every integer is in the inclusive range [0, 2n - 1],

        + The first integer is 0,

        + An integer appears no more than once in the sequence,

        + The binary representation of every pair of adjacent integers differs
          by exactly one bit, and

        + The binary representation of the first and last integers differs by
          exactly one bit.

    Given an integer n, return any valid n-bit gray code sequence.

    ======================================
    FUNCTION: vector<int> grayCode(int n);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: [0,1,3,2]
    Explanation:
    The binary representation of [0,1,3,2] is [00,01,11,10].
    - 00 and 01 differ by one bit
    - 01 and 11 differ by one bit
    - 11 and 10 differ by one bit
    - 10 and 00 differ by one bit
    [0,2,3,1] is also a valid gray code sequence, whose binary representation
    is [00,10,11,01].
    - 00 and 10 differ by one bit
    - 10 and 11 differ by one bit
    - 11 and 01 differ by one bit
    - 01 and 00 differ by one bit


    --- Example 2 ---
    Input: n = 1
    Output: [0,1]


    *** Constraints ***
    1 <= n <= 16

*/

/*
    ------------
    --- IDEA ---
    ------------

    Standard dfs/backtracking approach.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.77% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> grayCode(int n)
    {
        std::vector<int> result;
        int curr_num = 0;

        result.push_back(curr_num);
        for(int i = 0; i < n; i++)
            dfs(result, curr_num, i);

        return result;
    }

    void dfs(std::vector<int>& result, int& curr_num, int n)
    {
        curr_num ^= 1 << n;
        result.push_back(curr_num);

        for(int i = 0; i < n; i++)
            dfs(result, curr_num, i);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using bitsets and this feels much more like a standard Backtracking
    Solution.

*/

/* Time  Beats: 84.60% */
/* Space Beats: 14.70% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution_Bitset_Backtracking {
public:
    std::vector<int> grayCode(int n)
    {
        std::bitset<32> bits;
        std::vector<int> result;

        backtracking(bits, result, n);

        return result;
    }

private:
    void backtracking(std::bitset<32>& bits, std::vector<int>& result, int k)
    {
        if (k == 0)
            result.push_back(bits.to_ulong());
        else
        {
            backtracking(bits, result, k-1);
            bits.flip(k-1);
            backtracking(bits, result, k-1);
        }
    }
};
