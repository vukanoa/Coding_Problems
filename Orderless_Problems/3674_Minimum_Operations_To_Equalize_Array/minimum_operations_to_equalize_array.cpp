/*
    ============
    === EASY ===
    ============

    ==========================================
    3674) Minimum Operations to Equalize Array
    ==========================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    In one operation, choose any subarray nums[l...r] (0 <= l <= r < n) and
    replace each element in that subarray with the bitwise AND of all elements.

    Return the minimum number of operations required to make all elements of
    nums equal. A subarray is a contiguous non-empty sequence of elements
    within an array.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2]
    Output: 1
    Explanation:
    Choose nums[0...1]: (1 AND 2) = 0, so the array becomes [0, 0] and all
    elements are equal in 1 operation.

    --- Example 2 ---
    Input: nums = [5,5,5]
    Output: 0
    Explanation:
    nums is [5, 5, 5] which already has all elements equal, so 0 operations are
    required.


    *** Constraints ***
    1 <= n == nums.length <= 100
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If NOT all elements are the same, then the answer is ALWAYS 1.
    Try to find an example where that is not true. You won't succeed.

    However, can I prove it?
    Yes!

    But since it is an EASY problem, if you notice something unusual like this
    it's almost always the answer.


    Proof:
    If NOT all elements are the same, then if you bitwise-AND all of the
    elements, you'll certainly get clear-bit(i.e. 0) at some bit.

    Therefore, you'll essentially change all of the elements to that value,
    which is 0, making the entire array have value 0.

    And we've that in a single operation by taking all of the elements in
    account.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            if (nums[0] != nums[i])
                return 1;
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but implemented using CPP's function "count".

    How does it work?
    Count how many times VALUES(i.e. nums[0]) occurrs in a vector.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_CPP_way {
public:
    int minOperations(vector<int>& nums)
    {
        return count(nums.begin(), nums.end(), nums[0]) != nums.size();
    }
};
