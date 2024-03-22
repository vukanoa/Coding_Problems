#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    40) Combination Sum II
    ===========================

    ============
    Description:
    ============

    Given a collection of candidate numbers (candidates) and a target number
    (target), find all unique combinations in candidates where the candidate
    numbers sum to target.

    Each number in candidates may only be used once in the combination.

    =====
    Node: The solution set must not contain duplicate combinations.
    =====

    ====================================================================================
    FUNCTION: vector<vector<int>> combinationSum2(vector<int>& candidates, int& target);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: candidates = [10,1,2,7,6,1,5], target = 8
    Output:
    [
    [1,1,6],
    [1,2,5],
    [1,7],
    [2,6]
    ]


    --- Example 2 ---
    Input: candidates = [2,5,2,1,2], target = 5
    Output:
    [
    [1,2,2],
    [5]
    ]


    *** Constraints ***
    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30


*/

/*
    ------------
    --- IDEA ---
    ------------

    It's very similar to "Combination Sum". However, since duplicates are not
    allowed, we have to sort the vector "candidates"(since that won't worsen
    neither Time nor Space Complexity) and then, at first, we do the same
    thing, however once we "backtrack" because sum was >= target, now we do not
    want to begin with the same number, for it is possible to get duplicate
    combination. Therefore, we have to skip all the numbers that are the same
    as the one we've used to, successfully, go deeper down the backtracking tree.

    That's the whole idea.

    You should simulate the code on the three Examples I've listed below and
    I'm sure it will be even more clear.

*/

/* Time  Beats: 83.56% */
/* Space Beats: 45.75% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(2^n) */
class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target)
    {
        std::vector<std::vector<int>> results;
        std::sort(candidates.begin(), candidates.end());

        std::vector<int> curr_comb;
        backtracking(candidates, target, 0, curr_comb, 0, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& candidates,
                     int& target,
                     int start,
                     std::vector<int>& curr_comb,
                     int sum,
                     std::vector<std::vector<int>>& results)
    {
        if (sum > target)
            return;
        else if (sum == target)
        {
            results.push_back(curr_comb);
            return;
        }

        int i = start;
        while (i < candidates.size())
        {
            curr_comb.push_back(candidates[i]);
            backtracking(candidates, target, i+1, curr_comb, sum + candidates[i], results);
            curr_comb.pop_back();

            if (sum + candidates[i] > target)
                return;

            // Don't use duplicates
            i++;
            while (i < candidates.size() && candidates[i-1] == candidates[i])
                i++;
        }
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> candidates = {2, 5, 2, 1, 2};
    // int target = 5;

    /* Example 2 */
    // std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    // int target = 8;

    /* Example 3 */
    // 1 2 2 2 2 2 2 2 2 2 6 8
    std::vector<int> candidates = {2, 2, 2, 2, 6, 1, 2, 2, 2, 8, 2, 2};
    int target = 15;

    std::cout << "\n\t==========================";
    std::cout << "\n\t=== COMBINATION SUM II ===";
    std::cout << "\n\t==========================\n\n";

    /* Write Input */
    std::cout << "\n\tTarget: " << target;
    bool first = true;
    std::cout << "\n\tCandidates: [";
    for (auto x: candidates)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    std::vector<std::vector<int>> results = sol.combinationSum2(candidates, target);


    /* Write Output */
    first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
