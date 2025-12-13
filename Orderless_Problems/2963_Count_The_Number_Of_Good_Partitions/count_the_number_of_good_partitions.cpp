/*
    ============
    === HARD ===
    ============

    =========================================
    2963) Count the Number of Good Partitions
    =========================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums consisting of positive integers.

    A partition of an array into one or more contiguous subarrays is called
    good if no two subarrays contain the same number.

    Return the total number of good partitions of nums.

    Since the answer may be large, return it modulo 10^9 + 7.

    ========================================================
    FUNCTION: int numberOfGoodPartitions(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 8
    Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]),
                 ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2],
                 [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).

    --- Example 2 ---
    Input: nums = [1,1,1,1]
    Output: 1
    Explanation: The only possible good partition is: ([1,1,1,1]).

    --- Example 3 ---
    Input: nums = [1,2,1,3]
    Output: 2
    Explanation: The 2 possible good partitions are: ([1,2,1], [3]) and
                 ([1,2,1,3]).


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    From the Description of this problem we know that FIRST and the LAST
    occurence of some nums[i] number MUST BE(!!!) in the SAME partition.

        [i, rightmost_idx_of[nums[i]].
         ^             ^
         |             |
         |             |
        start         end


    Also, if (i < j && rightmost_idx_of(nums[i] > j) then:
        
        nums[j] MUST be in the SAME partition,

        i.e. [i, max(rightmost_idx_of[nums[i]],
              ^      rightmost_idx_of[nums[j]])]]
              |                 ^
              |                 |
              |                 |
             start             end


    Each NON-overlapping partition DOUBLES the total number of good partitions.

*/

/* Time  Beats: 55.12% */
/* Space Beats: 92.91% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums)
    {
        const int N = nums.size();
        const int MOD = 1e9 + 7;
        int result = 1;

        unordered_map<int, int> rightmost_idx_of;

        for (int i = N-1; i >= 0; i--)
        {
            if ( ! rightmost_idx_of.count(nums[i]))
                rightmost_idx_of.insert( {nums[i], i} );
        }

        int max_right = 0;
        for (int i = 0; i < N; i++)
        {
            if (max_right < i)
                result = result * 2 % MOD;

            max_right = max(max_right, rightmost_idx_of[nums[i]]);
        }

        return result;
    }
};
