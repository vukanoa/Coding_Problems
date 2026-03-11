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

#include <vector>
#include <algorithm>
using namespace std;

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

    1.
        If the sum of the current combination is greater than target, then even
        if we move forward with this combination, the sum will only increase.
        So there is no point moving further because we will never be able to
        reach the target. Backtrack from this by breaking the for loop.

    2.
        If the current combination is equal to the target, then store it in the
        result vector and Backtrack from this since we have the same situations
        as in case 1. We certainly won't be able to reach the target again if
        we continue down this path.

    3.
        If the current combination is still less than our target, then:

        i)
            Consider all possible options into this combination, one at a time.

        ii)
            Check if current option can be == target with current combination.

        iii)
            When this options backtracks to this place again, remove this
            option and try another option, e.fl [2, 2, ...], we have 3 options
            to

        fill the 3rd place i.e [2, 3, 5].
        So firstly we will go on with [2, 2, 2]. Then when this backtracks to
        this place again, remove last 2, and try next option which is "3", that
        means [2, 2, 3].

        When this also backtracks remove 3 to try 5, that means [2, 2, 5].
        Now, as all options are exhausted for [2, 2, ...], now backtrack to its
        previous state which is [2, 2], and so on...


    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~ Analysis of the Time complexity ~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Why is the Time Complexity this weird: O(2^(target / min_value)).

        Consider this example:

            candidates = [2, 3, 5], target = 10


             ^                                  .
             |                                /   \
             |                               /     \
             |                       take 2 /       \ skip 2
             |                             /         \
             |                            /           \
             |                          [2]            []
             |                         /   \           ...
             |                        /     \          ...
             | H              take 2 /       \ skip 2  ...
             |                      /         \
             |                     /           \
             |                  [2,2]          [2]
             |                  ...            ...
             |                  ...            ...
             |                  ...            ...
             |                [2]
             |               /   \
             |              /     \
             |      take 2 /       \ skip 2
             |            /         \
             |           /           \
             v     [2,2,2,2,2]      [2,2,2,2]



     This height "H" is going to be the deepest for the leaf where we
     repeatedly take the MINIMUM value in "candidates".

     Think about it.

     In this case we'll have H be 5 because the target we're trying to sum up
     to is 10 and the "step" is 2. Therefore: 10 / 2 is 5.


     So the total Time Complexity is O(2^H) i.e. O(2^(target / min_value)).

*/

/* Time  Beats: 58.19% */
/* Space Beats: 29.91% */

/* Time  Complexity: O(2^(target  / min_value)) */
/* Space Complexity: O(2^(target  / min_value)) */
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        const int N = candidates.size();
        vector<vector<int>> result;

        /*
           Sort.

           It's important to sort because we want to avoid counting the same
           combination more than once.

           [2,2,3] and [2,3,2] are the same.

           Therefore, in order to prevent counting them twice, we can simply
           sort and once we move onto the next candidate, we're sure that its
           a unique one.
        */
        sort(candidates.begin(), candidates.end());

        backtracking(0, {}, 0, candidates, target, result);

        return result;
    }

private:
    void backtracking(int idx, vector<int> curr_comb, int curr_sum, vector<int>& candidates, int& target, vector<vector<int>>& result)
    {
        if (curr_sum == target)
        {
            result.push_back(curr_comb);
            return;
        }

        const int N = candidates.size();
        for (int i = idx; i < N; i++)
        {
            if (curr_sum + candidates[i] > target)
                break;

            curr_comb.push_back(candidates[i]);
            backtracking(i, curr_comb, curr_sum + candidates[i], candidates, target, result);
            curr_comb.pop_back();
        }
    }
};
