/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3702) Longest Subsequence With Non-Zero Bitwise XOR
    ===================================================

    ============
    Description:
    ============


    You are given an integer array nums.

    Return the length of the longest subsequence in nums whose bitwise XOR is
    non-zero. If no such subsequence exists, return 0.

    ===============================
    FUNCTION: `
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 2
    Explanation:
    One longest subsequence is [2, 3]. The bitwise XOR is computed as
    2 XOR 3 = 1, which is non-zero.

    --- Example 2 ---
    Input: nums = [2,3,4]
    Output: 3
    Explanation:
    The longest subsequence is [2, 3, 4]. The bitwise XOR is computed as
    2 XOR 3 XOR 4 = 5, which is non-zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9

*/

#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.93% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int total_xor    = 0;
        int zeroes_count = 0;

        for (const int& num : nums)
        {
            if (num == 0)
                zeroes_count++;

            total_xor ^= num;
        }

        if (zeroes_count == N) // All zeroes
            return 0;
        
        return total_xor == 0 ? N-1 : N;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   4.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();

        int total_xor = accumulate(nums.begin(), nums.end(), 0, bit_xor<>());
        if (total_xor != 0)
            return N;

        unordered_set<int> uset(nums.begin(), nums.end());

        return (uset.size() == 1 && *uset.begin() == 0) ? 0 : N-1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way to impleent it. More explicit.

*/

/* Time  Beats: 43.09% */
/* Space Beats: 22.70% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_3 {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();

        int total_xor = accumulate(nums.begin(), nums.end(), 0, bit_xor<>());
        if (total_xor != 0)
            return N;

        unordered_set<int> uset(nums.begin(), nums.end());
        for (const int& num : uset)
        {
            if ((total_xor ^ num) != 0)
                return N-1;
        }

        return 0; // All zeroes
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    
    The XOR of all elements is either zero or non-zero.

        Case 1: If total XOR != 0:

            + Array nums is already valid, we simply take all elements, then
                return N;


        Case 2: If total XOR == 0:

            nums is currently invalid, therefore we must remove SOME element.

            + Subcases:
                1) At least one NON-ZERO element exists in nums, thus we remove
                   this one NON-ZERO element and return N-1;

                2) All elements are 0, thus we return 0;



    If the total XOR=0 and at least a single non-zero value exists, then
    Excluding a non-zero value, also produces a non-zero XOR.

        nums = [0, 0, 9, 0, 2, 1]

                                                exclude one non-zero number

          +---------+                               +---------+
        0 | 0 0 0 0 |                             0 | 0 0 0 0 |
          +---------+                               +---------+
        0 | 0 0 0 0 |                             0 | 0 0 0 0 |
          +---------+                               +---------+
        9 | 1 0 0 1 |                        -----9-|-#-#-#-#-|---- (crossed)
          +---------+                               +---------+
        0 | 0 0 0 0 |                             0 | 0 0 0 0 |
          +---------+                               +---------+
        2 | 0 0 1 0 |                             2 | 0 0 1 0 |
          +---------+                               +---------+
       11 | 1 0 1 1 |  XOR                       11 | 1 0 1 1 |  XOR
          +---------+                               +---------+
  total=0 | 0 0 0 0 |                       total=9 | 1 0 0 1 |
          +---------+                               +---------+


    Since we want the longest subsequence, it is optimal to exclude only one
    number.

*/

/* Time  Beats: 11.18% */
/* Space Beats: 88.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    int longestSubsequence(vector<int>& nums)
    {
        const int N = nums.size();

        int total_xor = 0;
        int at_least_one_positive = 0;

        for (const int& num : nums)
        {
            at_least_one_positive |= num > 0;
            total_xor ^= num;
        }

        return at_least_one_positive * (N - !total_xor);
    }
};
