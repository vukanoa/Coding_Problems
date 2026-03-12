/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    78) Subsets
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums" of unique elements, return all possible
    subsets(the power set).

    The solution set MUST NOT contain duplicate subsets. Return the solution in
    any order.

    =========================================================
    FUNCTION: vector<vector<int>> subsets(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [1, 2, 3]
    Output: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]

    --- Example 2 ---
    Input:  nums = [0]
    Output: [[], [0]]

    *** Constraints ***
    1 <= nums.length <= 10
    -10 <= nums[i] <= 10
    All the numbers of "nums" are UNIQUE

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let's start from empty subset in output list. At each step one takes new
    integer into consideration and generates new subsets from the existing
    ones.

    nums: 1 2 3

    1. Start from empty subset:
        {}

    2. Take "1" into consideration and add new subsets by updating existing
       ones:
        {}, {1}

    3. Take 2 into consideration and add new subsets by updating existing ones:
        {}, {1}, {2}, {1, 2}

    4. Take 3 into consideration and add new subsets by updating existing ones:
        {}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.12% */

/*
    Time  Complexity: O(N * 2^N)

    This is because for each element in nums, the algorihtm makes a choice of
    either including or excluding that element, resulting in a total of 2^N
    possible subsets.

    For each subset, the algorithm copies the current subset(which takes O(N)
    time) and appends or removes an element from it(which takes O(1) time).
    Therefore, the overall Time Complexity is O(N * 2^N).
*/
/*
    Space Complexity: O(N * 2^N)

    The algorithm generates all possible subsets, which in the worst case can
    be 2^N subsets. Each subset has an average length of N/2, so the total
    space required to store all subsets is O(N/2 * 2^N), which simplifies to
    O(N * 2^N).

    Additionally, the algorithm uses recursion to generate the subsets, which
    can result in a maximum depth of N in the call stack. Therefore, the space
    complexity is O(N * 2^N) due to the subsets generated and O(n) due to the
    recursion call stack, for a total of O(N * 2^N + N).
*/
class Solution_Iterative_trick {
public:
    vector<vector<int>> subsets(vector<int>& nums)
    {
        const int N = nums.size();
        vector<vector<int>> subsets = {{}};

        for (int i = 0; i < N; i++)
        {
            const int SUBSETS_SIZE = subsets.size();
            for (int j = 0; j < SUBSETS_SIZE; j++)
            {
                vector<int> new_subset = subsets[j];
                new_subset.push_back(nums[i]);

                subsets.push_back(new_subset);
            }
        }

        return subsets;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Basic Backtracking.

    This Solution will produce output in a different order than in the previous
    example.

    It's possible that they were looking for the above Solution since that
    matches the output order, however in the Description of this Problem it is
    noted that we can return solution in any order.

    So, this is an additional approach.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.45% */

/*
    Time  Complexity: O(N * 2^N)

    This is because for each element in nums, the algorihtm makes a choice of
    either including or excluding that element, resulting in a total of 2^N
    possible subsets.

    For each subset, the algorithm copies the current subset(which takes O(N)
    time) and appends or removes an element from it(which takes O(1) time).
    Therefore, the overall Time Complexity is O(N * 2^N).
*/
/*
    Space Complexity: O(N * 2^N)

    The algorithm generates all possible subsets, which in the worst case can
    be 2^N subsets. Each subset has an average length of N/2, so the total
    space required to store all subsets is O(N/2 * 2^N), which simplifies to
    O(N * 2^N).

    Additionally, the algorithm uses recursion to generate the subsets, which
    can result in a maximum depth of N in the call stack. Therefore, the space
    complexity is O(N * 2^N) due to the subsets generated and O(n) due to the
    recursion call stack, for a total of O(N * 2^N + N).
*/
class Solution_Backtracking {
private:
    void backtracking(int start_from, vector<int>& nums, vector<int> curr_subset, vector<vector<int>>& results)
    {
        results.push_back(curr_subset);

        const int N = nums.size();
        for (int i = start_from; i < nums.size(); i++)
        {
            curr_subset.push_back(nums[i]);
            backtracking(i+1, nums, curr_subset, results);
            curr_subset.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums)
    {
        vector<vector<int>> results;

        backtracking(0, nums, {}, results);

        return results;
    }
};
