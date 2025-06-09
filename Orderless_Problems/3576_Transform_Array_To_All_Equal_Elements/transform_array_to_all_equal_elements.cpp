/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3576) Transform Array to All Equal Elements
    ===========================================

    ============
    Description:
    ============

    You are given an integer array nums of size n containing only 1 and -1, and
    an integer k.

    You can perform the following operation at most k times:

        + Choose an index i (0 <= i < n - 1), and multiply both nums[i] and
          nums[i + 1] by -1.

    Note that you can choose the same index i more than once in different
    operations.

    Return true if it is possible to make all elements of the array equal after
    at most k operations, and false otherwise.

    ======================================================
    FUNCTION: bool canMakeEqual(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-1,1,-1,1], k = 3
    Output: true
    Explanation:
    We can make all elements in the array equal in 2 operations as follows:
        Choose index i = 1, and multiply both nums[1] and nums[2] by -1. Now nums = [1,1,-1,-1,1].
        Choose index i = 2, and multiply both nums[2] and nums[3] by -1. Now nums = [1,1,1,1,1].


    --- Example 2 ---
    Input: nums = [-1,-1,-1,1,1,1], k = 5
    Output: false
    Explanation:
    It is not possible to make all array elements equal in at most 5 operations.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    nums[i] is either -1 or 1.
    1 <= k <= n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Formal proof of the correctness of this Greedy Algorithm is needed, but not
    really.

    After you lay out examples in front of yourself you'll quickly realize that
    the greedy flip at the first index where nums[i] != target ensures that
    you're always making the minimum necessary change and that it's the most
    optimal way of doing it if it can be done at all.

    Again, lay a few examples in front of yourself and try to think of an
    example that crushes that hypothesis--Hint hint, you won't find one.

    Therefore, you can conclude with a high level of probability that this is
    indeed the most optimal way.

*/

/* Time  Beats: 62.50% */
/* Space Beats:  6.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool canMakeEqual(vector<int>& nums, int k)
    {
        return can_be(1, nums, k) || can_be(-1, nums, k);
    }

private:
    bool can_be(int target, vector<int> nums_copy, int& k)
    {
        const int N = nums_copy.size();

        int count  = 0;
        for (int i = 0; i < N-1; i++)
        {
            if (nums_copy[i] != target)
            {
                nums_copy[i  ] *= -1;
                nums_copy[i+1] *= -1;

                count++;
            }
        }

        return nums_copy.back() == target && count <= k;
    }
};
