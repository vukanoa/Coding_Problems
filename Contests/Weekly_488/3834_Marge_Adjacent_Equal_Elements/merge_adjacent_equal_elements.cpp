/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    3834) Merge Adjacent Equal Elements
    ===================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You must repeatedly apply the following merge operation until no more
    changes can be made:

        + If any two adjacent elements are equal, choose the leftmost such
          adjacent pair in the current array and replace them with a single
          element equal to their sum.

    After each merge operation, the array size decreases by 1. Repeat the
    process on the updated array until no more changes can be made.

    Return the final array after all possible merge operations.

    =============================================================
    FUNCTION: vector<long long> mergeAdjacent(vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,1,2]
    Output: [3,4]
    Explanation:
        The middle two elements are equal and merged into 1 + 1 = 2, resulting in [3, 2, 2].
        The last two elements are equal and merged into 2 + 2 = 4, resulting in [3, 4].
        No adjacent equal elements remain. Thus, the answer is [3, 4].

    --- Example 2 ---
    Input: nums = [2,2,4]
    Output: [8]
    Explanation:
        The first two elements are equal and merged into 2 + 2 = 4, resulting in [4, 4].
        The first two elements are equal and merged into 4 + 4 = 8, resulting in [8].

    --- Example 3 ---
    Input: nums = [3,7,5]
    Output: [3,7,5]
    Explanation:
    There are no adjacent equal elements in the array, so no operations are performed.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.96% */
/* Space Beats: 87.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<long long> mergeAdjacent(vector<int>& nums)
    {
        const int N = nums.size();

        vector<long long> stack;
        stack.push_back(nums[0]);

        for (int i = 1; i < N; i++)
        {
            if (stack.back() == nums[i])
                stack.back() += nums[i];
            else
                stack.push_back(nums[i]);

            while (stack.size() >= 2 && *(prev(stack.end() - 1)) == stack.back())
            {
                *(prev(stack.end() - 1)) += stack.back();
                stack.pop_back();
            }
        }

        return stack;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, implemented a bit more elegantnly.

*/

/* Time  Beats: 95.49% */
/* Space Beats: 97.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    vector<long long> mergeAdjacent(vector<int>& nums)
    {
        const int N = nums.size();

        vector<long long> stack;
        stack.reserve(N);

        for (long long nmber : nums)
        {
            while ( ! stack.empty() && stack.back() == nmber)
            {
                nmber += stack.back();
                stack.pop_back();
            }

            stack.push_back(nmber);
        }

        return stack;
    }
};
