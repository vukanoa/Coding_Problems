#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    47) Permutations II
    ===========================

    ============
    Description:
    ============

    Given a collection of numbers, nums, that might contain duplicates, return
    all possible unique permutations in any order.

    ===============================================================
    FUNCTION: vector<vector<int>> permuteUnique(vector<int>& nums);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2]
    Output:[[1,1,2],[1,2,1],[2,1,1]]


    --- Example 2 ---
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


    *** Constraints ***

    1 <= nums.length <= 8
    -10 <= nums[i] <= 10

*/

/* Time  Beats: 74.66% */
/* Space Beats: 42.08% */

/*
    Time  Complexity: O(N!)

    Time Complexity : O(N!), In worst case when all element of Array(nums) will
    different then there will be N!  permutations and N! function calls. Where
    N is the size of the array(nums) and ! stands for factorial.
*/
/*
    Space Complexity: O(N! * N)

    Space Complexity: O(N!*N), In worst case when all element of Array(nums)
    will different, since we have to store all the possible solutions which are
    N! in size where N is the size of the array and ! stands for factorial.
*/
class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> result;
        std::vector<int> tmp;
        std::vector<bool> visited(nums.size(), false);

        backtracking(nums, result, tmp, visited);

        return result;
    }

private:
    void backtracking(
                      std::vector<int>& nums,
                      std::vector<std::vector<int>>& result,
                      std::vector<int> tmp,
                      std::vector<bool>& visited
                     )
    {
        if(tmp.size() == nums.size())
        {
            result.push_back(tmp);
            return;
        }

        for(int i = 0; i < nums.size(); i++)
        {
            if(visited[i] || (i>0 && nums[i] == nums[i-1] && !visited[i-1]))
                continue;

            visited[i] = true;
            tmp.push_back(nums[i]);

            backtracking(nums, result, tmp, visited);

            tmp.pop_back();
            visited[i] = false;
        }
    }
};
