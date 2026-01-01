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
        std::vector<std::vector<int>> results;
        std::vector<bool> visited(nums.size(), false);

        // Sort the Input
        std::sort(nums.begin(), nums.end());

        backtracking(nums, {}, visited, results);

        return results;
    }

private:
    void backtracking(
                      std::vector<int>& nums,
                      std::vector<int> curr_permutation,
                      std::vector<bool>& visited,
                      std::vector<std::vector<int>>& result
                     )
    {
        if(curr_permutation.size() == nums.size())
        {
            result.push_back(curr_permutation);
            return;
        }

        for(int i = 0; i < nums.size(); i++)
        {
            if(visited[i] || (i > 0 && nums[i] == nums[i-1] && !visited[i-1]))
                continue;

            // Push
            visited[i] = true;
            curr_permutation.push_back(nums[i]);

            backtracking(nums, curr_permutation, visited, result);

            // Pop
            curr_permutation.pop_back();
            visited[i] = false;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is almost equivalent to the above Solution, however it is implemented
    a bit different. Different enough to deserve its on Implementation.

*/

/* Time  Beats: 77.93% */
/* Space Beats: 24.71% */

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
class Solution_2 {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;
        std::unordered_set<int> uset;

        // Sort the Input
        std::sort(nums.begin(), nums.end());

        backtracking(nums, {}, uset, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& nums,
                      std::vector<int> curr_permutation,
                      std::unordered_set<int>& uset,
                      std::vector<std::vector<int>>& results)
    {
        if (uset.size() == nums.size())
        {
            results.push_back(curr_permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            while (i > 0 && i < nums.size() && nums[i-1] == nums[i] && uset.count(i-1) == 0)
                i++;

            if (i == nums.size())
                break;

            if (uset.count(i))
                continue;

            // Push
            uset.insert(i);
            curr_permutation.push_back(nums[i]);

            backtracking(nums, curr_permutation, uset, results);

            // Pop
            curr_permutation.pop_back();
            uset.erase(i);
        }
    }
};
