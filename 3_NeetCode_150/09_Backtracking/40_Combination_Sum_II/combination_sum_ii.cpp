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

#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Using a HashSet to track duplicates "locally", i.e. duplicates for that
    specific position in curr_combination, but still allowing "global", i.e.
    duplicates withint the curr_combinations itself.


    The branching is 2^N of the entire backtracking since we have 2 options at
    every index:

        We can either TAKE or SKIP the curren element.

    And since there are N such elements, we can make 2^N choices.

    But where does the N in O(N * 2^N) come from?
    It comes from copying the elements from curr_combination to results.

    At worst, we'll copy every single "leaf" node in this branch-tree,
    therefore it's a O(N * 2^N).

*/

/* Time  Beats: 13.37% */
/* Space Beats:  9.49% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N)       */
class Solution_Hashset {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        const int N = candidates.size();
        vector<vector<int>> result;

        /* Sort */
        sort(candidates.begin(), candidates.end()); // O(N * logN)

        /* Backtracking */
        backtracking(0, {}, 0, candidates, target, result); // O(N * 2^N)

        return result;
    }

private:
    void backtracking(int start_from, vector<int> curr_combination, int sum, vector<int>& candidates, int& target, vector<vector<int>>& result)
    {
        if (sum == target)
        {
            result.push_back(curr_combination); // O(N)
            return;
        }

        unordered_set<int> used; // Used in position "start_from" of curr_combination

        const int N = candidates.size();
        for (int i = start_from; i < N; i++)
        {
            if (sum + candidates[i] > target)
                break;

            if (used.count(candidates[i]))
                continue;

            used.insert(candidates[i]);

            curr_combination.push_back(candidates[i]);
            backtracking(i+1, curr_combination, sum + candidates[i], candidates, target, result);
            curr_combination.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's very similar to "Combination Sum". However, since duplicates are not
    allowed, we have to sort the vector "candidates"(since that won't worsen
    neither Time nor Space Complexity) and then, at first, we do the same
    thing, however once we "backtrack" because sum was >= target, now we do not
    want to begin with the same number at that given position in
    curr_combination, because it is possible to get duplicate combination.

    Therefore, we have to skip all the numbers that are the same as the one
    we've just used to in this position of curr_combination, successfully, and
    go deeper down the backtracking tree.

    That's the whole idea.

    You should simulate the code on the three Examples I've listed below and
    I'm sure it will be even more clear.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 61.60% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N)       */
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        vector<vector<int>> results;

        /* Sort */
        sort(candidates.begin(), candidates.end());

        /* Backtracking */
        backtracking(0, {}, 0, candidates, target, results);

        return results;
    }

private:
    void backtracking(int start_from, vector<int> curr_combination, int sum, vector<int>& candidates, int& target, vector<vector<int>>& results)
    {
        if (sum == target)
        {
            results.push_back(curr_combination);
            return;
        }

        const int N = candidates.size();

        int i = start_from;
        while (i < N)
        {
            curr_combination.push_back(candidates[i]);
            backtracking(i+1, curr_combination, sum + candidates[i], candidates, target, results);
            curr_combination.pop_back();

            if (sum + candidates[i] > target)
                return;

            // Increment
            i++;

            // Don't use duplicates
            while (i < N && candidates[i-1] == candidates[i])
                i++;
        }
    }
};
