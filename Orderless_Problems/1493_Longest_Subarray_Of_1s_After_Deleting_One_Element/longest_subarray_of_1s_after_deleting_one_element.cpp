/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    1493) Longest Subarray of 1s After Deleting One Element
    =======================================================

    ============
    Description:
    ============

    Given a binary array nums, you should delete one element from it.

    Return the size of the longest non-empty subarray containing only 1's in
    the resulting array. Return 0 if there is no such subarray.

    =================================================
    FUNCTION: int longestSubarray(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,0,1]
    Output: 3
    Explanation: After deleting the number in position 2, [1,1,1] contains 3
                 numbers with value of 1's.

    --- Example 2 ---
    Input: nums = [0,1,1,1,0,1,1,0,1]
    Output: 5
    Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1]
                 longest subarray with value of 1's is [1,1,1,1,1].

    --- Example 3 ---
    Input: nums = [1,1,1]
    Output: 2
    Explanation: You must delete one element.


    *** Constraints ***
    1 <= nums.length <= 10^5
    nums[i] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.08% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int prev_len = 0;
        int leftmost_one_idx = -1;

        // Find the leftmost one
        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 1)
            {
                leftmost_one_idx = i;
                break;
            }
        }

        if (leftmost_one_idx == -1) // If all are 0s
            return 0;

        int curr_len = 0;
        for (int i = leftmost_one_idx; i < N; i++)
        {
            if (nums[i] == 1)
                curr_len++;
            else
            {
                curr_len -= prev_len;
                prev_len  = curr_len;
            }

            if (leftmost_one_idx > 0)
                result = max(result, curr_len);
            else
                result = max(result, prev_len == 0 ? curr_len-1 : curr_len);
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

/* Time  Beats: 25.82% */
/* Space Beats: 58.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
   int longestSubarray(vector<int>& nums)
   {
       const int N = nums.size();

       int result = 0;
       int prev_len = 0;
       int curr_len = 0;

       for (int i = 0; i < N; i++)
       {
           if (nums[i] == 0)
           {
               result = max(result, prev_len + curr_len);
               prev_len = curr_len;
               curr_len = 0;
           }
           else
               curr_len++;
       }

       if (nums[N-1] == 1)
            result = max(result, prev_len + curr_len);

       if (curr_len == N)
            return N-1;

       return result;
   }
};
