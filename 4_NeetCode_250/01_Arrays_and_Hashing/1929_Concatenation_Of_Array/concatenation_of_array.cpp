/*
    ============
    === EASY ===
    ============

    ============================
    1929) Concatenation of Array
    ============================

    ============
    Description:
    ============

    Given an integer array nums of length n, you want to create an array ans of
    length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n
    (0-indexed).

    Specifically, ans is the concatenation of two nums arrays.

    Return the array ans.

    ==========================================================
    FUNCTION: vector<int> getConcatenation(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1]
    Output: [1,2,1,1,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
    - ans = [1,2,1,1,2,1]


    --- Example 2 ---
    Input: nums = [1,3,2,1]
    Output: [1,3,2,1,1,3,2,1]
    Explanation: The array ans is formed as follows:
    - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
    - ans = [1,3,2,1,1,3,2,1]


    *** Constraints ***
    n == nums.length
    1 <= n <= 1000
    1 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Most straightfoward Solution.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // result is usually not counted as EXTRA Space
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(2 * N);

        for (int i = 0; i < N; i++)
        {
            ans[i]     = nums[i];
            ans[i + N] = nums[i];
        }

        return ans;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If we're not allowed to modify input, but wish to solve it in a similar
    way, then:

        vector<int> ans;
        ans.insert(ans.end(), nums.begin(), nums.end());

        return ans;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.90% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // result is usually not counted as EXTRA Space
class Solution_If_Allowed_To_Modify_Input {
public:
    vector<int> getConcatenation(vector<int>& nums)
    {
        nums.insert(nums.end(), nums.begin(), nums.end());
        return nums;
    }
};
