/*
    ============
    === EASY ===
    ============

    ============================
    1748) Sum of Unique Elements
    ============================

    ============
    Description:
    ============

    You are given an integer array nums. The unique elements of an array are
    the elements that appear exactly once in the array.

    Return the sum of all the unique elements of nums.

    =============================================
    FUNCTION: int sumOfUnique(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,2]
    Output: 4
    Explanation: The unique elements are [1,3], and the sum is 4.

    --- Example 2 ---
    Input: nums = [1,1,1,1,1]
    Output: 0
    Explanation: There are no unique elements, and the sum is 0.

    --- Example 3 ---
    Input: nums = [1,2,3,4,5]
    Output: 15
    Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.49% */
/* Space Beats: 40.87% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int sumOfUnique(vector<int>& nums)
    {
        unordered_map<int, bool> umap;
        int result = 0;

        for (const auto& num : nums)
        {
            auto it = umap.find(num);

            if (it != end(umap))
            {
                result -= it->second ? 0 : num;
                it->second = true;
            }
            else
            {
                umap.insert( {num, false} );
                result += num;
            }
        }

        return result;
    }
};
