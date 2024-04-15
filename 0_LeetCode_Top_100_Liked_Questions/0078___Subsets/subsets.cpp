#include <iostream>
#include <vector>


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

/* Time  Beats: 100% */
/* Space Beats: 73.12% */

/*
    Time  Complexity: O(2^n * n)

    Where n is the length of the input vector nums. The outer loop runs n
    times, iterating over each element of nums. The inner loop runs O(2^k)
    times, where k is the size of the subsets generated up to that point. Since
    each subset can have up to n elements, the total number of subsets
    generated is 2^0 + 2^1 + ... + 2^n-1, which equals 2^n. Therefore, the
    total time complexity is O(n * 2^n * n), which simplifies to O(2^n * n).

*/
/*
    Space Complexity: O(2^n * n)

    Where n is the length of the input vector nums. The algorithm generates all
    possible subsets, which in the worst case can be 2^n subsets. Each subset
    has an average length of n/2, so the total space required to store all
    subsets is O(2^n * n/2), which simplifies to O(2^n * n). Additionally, the
    algorithm uses a temporary vector to store each subset, which can have a
    length of up to n. THerefore, the space complexity is O(2^n * n) due to the
    subsets generated and O(n) due to the temporary vector used in the inner
    loop, for a total of O(2^n * n + n).
*/
class Solution_Pattern {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results = {{}};

        for (int i = 0; i < nums.size(); i++)
        {
            int results_size = results.size();
            for (int j = 0; j < results_size; j++)
            {
                std::vector<int> curr = results[j];
                curr.push_back(nums[i]);

                results.push_back(curr);
            }
        }

        return results;
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

    So, there's an additional approach.

*/


/* Time  Beats: 100% */
/* Space Beats: 58.45% */

/*
    Time  Complexity: O(2^n * n)

    Where n is the length of the input vector nums. This is because for each
    element in nums, the algorihtm makes a choice of either including or
    excluding that element, resulting in a total of 2&n possible subsets. For
    each subset, the algorithm copies the current subset(which takes O(n) time)
    and appends or removes an element from it(which takes O(1) time).
    Therefore, the overall Time Complexity is O(2^n * n).
*/
/*
    Space Complexity: O(2^n * n)

    The algorithm generates all possible subsets, which in the worst case can
    be 2^n subsets. Each subset has an average length of n/2, so the total
    space required to store all subsets is O(2^n * n/2), which simplifies to
    O(2^n * n). Additionally, the algorithm uses recursion to generate the
    subsets, which can result in a maximum depth of n in the call stack.
    Therefore, the space complexity is O(2^n * n) due to the subsets generated
    and O(n) due to the recursion call stack, for a total of O(2^n * n + n).
*/
class Solution_Backtracking {
private:
    void backtracking(
                      std::vector<int>& nums,
                      int start_from,
                      std::vector<int> current,
                      std::vector<std::vector<int>>& results
                     )
    {
        results.push_back(current);

        for (int i = start_from; i < nums.size(); i++)
        {
            current.push_back(nums[i]);
            backtracking(nums, i + 1, current, results);
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;

        backtracking(nums, 0, {}, results);

        return results;
    }
};


int
main()
{
    Solution_Pattern      sol_patt;
    Solution_Backtracking sol_back;

    /* Example 1 */
    std::vector<int> nums = {1, 2, 3};

    /* Example 2 */
    // std::vector<int> nums = {0};

    /* Example 3 */
    // std::vector<int> nums = {1, 2};

    /* Example 4 */
    // std::vector<int> nums = {1, 2, 3, 4};

    std::cout << "\n\t===============";
    std::cout << "\n\t=== SUBSETS ===";
    std::cout << "\n\t===============\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    std::vector<std::vector<int>> results = sol_patt.subsets(nums);
    // std::vector<std::vector<int>> results = sol_back.subsets(nums);


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
