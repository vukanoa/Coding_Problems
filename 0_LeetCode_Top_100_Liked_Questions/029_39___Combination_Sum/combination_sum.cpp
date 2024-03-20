#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    39) Combination Sum
    ===========================

    ============
    Description:
    ============

    Given an array of distinct integers "candidates" and a target integer
    "target", return a list of all unique combinations of "candidates" where
    the chosen numbers sum to "target". You may return the combinations in any
    order.

    The same number may be chosen from "candidates" an unlimited number of
    times. Two combinations are unique if the frequency of at least one of the
    chosen numbers is different.

    The test cases are generated such that the number of unique combinations
    that sum up to "target" is less than 150 combinations for the given input.

    ==================================================================================
    FUNCTION: vector<vector<int>> combinationSum(vector<int>& candidates, int target);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  candidates = [2, 3, 6, 7], target = 7
    Output: [[2, 2, 3], [7]]

    --- Example 2 ---
    Input:  candidates = [2, 3, 5], target = 8
    Output: [[2, 2, 2, 2], [2, 3, 3], [3, 5]]

    --- Example 3 ---
    Input:  candidates = [2], target = 1
    Output: []

    *** Constraints ***
    1 <= candidates.lenght <= 30
    2 <= candidates[i] <= 40
    All elements of candidates are distinct
    1 <= target <= 40

*/


/*
    ------------
    --- IDEA ---
    ------------

    For questions where it says:"Find every possible" we generally use
    backtracking.

    State Space Tree:

    _________________________________________________________________________________________[]_______________________________________________________________________________
    ____________________________________________________________[2]_______________________________________________________[3]____________________________________[5]__________
    ______________________________________[2, 2]___________________________[2, 3]_______________[2, 5]__________[3,5]______________[3,5]___________[5,5]______________________
    _______________[2,2,2]_________________[2,2,3]_____[2,2,5]_________[2,3,3]___[2,3,5]______[2, 5, 5]____[3,3,3]___[3,3,5]______sum=target_________NOT______________________
    [2,2,2,2]_[2,2,2,3]_[2,2,2,5]__[2_3_3_3]__[2,2,3,5]_NOT_________sum=target_____NOT__________NOT_________NOT_______NOT_____________________________________________________
    sum=target____NOT______NOT_______NOT________NOT___________________________________________________________________________________________________________________________

    So how does this Algorithm work?
    1. If the sum of the current combination is greater than target, then even
    if we move forward with this combination, the sum will only increase. So
    there is no point moving further for we will never be able to reach the
    target. Backtrack from this.

    2. If the current combination is equal to the target, then store the
    solution and Backtrack from this since we have the same situations as in
    case 1. We certainly won't be able to reach the target again with greater
    values.

    3. If the current combination is still less than our target, then:
        i) Consider all possible options into this combination, one at a time.

        ii) Check if current option can be == target with current combination.

        iii) When this options backtracks to this place again, remove this
        option and try another option, e.fl [2, 2, ...], we have 3 options to
        fill the 3rd place i.e [2, 3, 5].
        So firstly we will go on with [2, 2, 2]. Then when this backtracks to
        this place again, remove last 2, and try next option which is "3", that
        means [2, 2, 3].
        When this also backtracks remove 3 to try 5, that means [2, 2, 5].
        Now, as all options are exhausted for [2, 2, ...], now backtrack to its
        previous state which is [2, 2], and so on...

*/

/* Time  Beats: 78.14% */
/* Space Beats: 48.43% */

/*
    Time  Complexity: O(2^n)

    The worst-case scenario is when all combinations of "candidates" sum up to
    "target".
*/
/*
    Space Complexity: O(2^n)

    The worst-case scenario is when all combinations of "candidates" sum up to
    "target".
*/
class Solution_Combination_Sum {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        // Sorting won't make the Time Complexity worse, so make sure to sort
        std::sort(candidates.begin(), candidates.end());

        std::vector<std::vector<int>> results;
        backtracking(candidates, target, 0, {}, 0, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& candidates,
                      int target,
                      int start,
                      std::vector<int> curr_comb,
                      int curr_sum,
                      std::vector<std::vector<int>>& results)
    {
        /* Backtrack */
        if (curr_sum == target)
        {
            results.push_back(curr_comb);
            return;
        }

        for (int i = start; i < candidates.size(); i++)
        {
            /* Backtrack */
            if (curr_sum + candidates[i] > target)
                return;

            curr_comb.push_back(candidates[i]);
            int new_sum = curr_sum + candidates[i];
            backtracking(candidates, target, i, curr_comb, new_sum, results);
            curr_comb.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Solution is almost equivalent to the one above, the only difference is
    that here, instead of passing another argument in "backtracking" function
    we can just decrement the "target" instead.

    Target is passed by value, so it won't mess up anything.

    Since we now decrement "target" and since we don't have "curr_sum" variable
    anymore, we have to change to snippets in the code(two if statements):


    1.
        ***********                                 ***********
        *** Old ***                                 *** New ***
        ***********                                 ***********

        if (curr_sum == target)                     if (target == 0)


    2.
        ***********                                 ***********
        *** Old ***                                 *** New ***
        ***********                                 ***********

        if (curr_sum + candidates[i] > target)      if (target - candidates[i] < 0)

*/

/* Time  Beats: 35.08% */
/* Space Beats: 42.44% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(2^n) */
class Solution_Target_Decrement {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        // Sorting won't make the Time Complexity worse, so make sure to sort
        std::sort(candidates.begin(), candidates.end());

        std::vector<std::vector<int>> results;
        backtracking(candidates, target, 0, {}, results);

        return results;
    }

private:
    void backtracking(std::vector<int>& candidates,
                      int target,
                      int start,
                      std::vector<int> curr_comb,
                      std::vector<std::vector<int>>& results)
    {
        /* Backtrack */
        if (target == 0) // Since we are subtracting from target every time
        {
            results.push_back(curr_comb);
            return;
        }

        for (int i = start; i < candidates.size(); i++)
        {
            /* Backtrack */
            if (target - candidates[i] < 0)
                return;

            curr_comb.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i, curr_comb, results);
            curr_comb.pop_back();
        }
    }
};


int
main()
{
    Solution_Combination_Sum   sol_comb_sum;
    Solution_Target_Decrement  sol_targ_dec;

    /* Example 1 */
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    /* Example 2 */
    // std::vector<int> candidates = {2, 3, 5};
    // int target = 8;

    /* Example 3 */
    // std::vector<int> candidates = {2};
    // int target = 1;

    /* Example 4 */
    // std::vector<int> candidates = {2, 5, 6, 7, 9, 11};
    // int target = 14;

    /* Example 5 */
    // std::vector<int> candidates = {1, 2, 3, 4, 7, 9};
    // int target = 5;

    /* Example 6 */
    // std::vector<int> candidates = {4, 5, 8, 9, 12};
    // int target = 22;

    /* Example 7 */
    // std::vector<int> candidates = {5, 6, 8};
    // int target = 32;

    /* Example 8 */
    // std::vector<int> candidates = {1, 5, 8};
    // int target = 6;

    std::cout << "\n\t=======================";
    std::cout << "\n\t=== COMBINATION SUM ===";
    std::cout << "\n\t=======================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tCandidates: [";
    for (auto x: candidates)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
    std::cout << "\tTarget: " << target << "\n\n";


    /* Solution */
    // std::vector<std::vector<int>> results = sol_comb_sum.combinationSum(candidates, target);
    std::vector<std::vector<int>> results = sol_targ_dec.combinationSum(candidates, target);


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
