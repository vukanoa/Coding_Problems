#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    60) Permute Sequence
    ===========================

    ============
    Description:
    ============

    The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

    By listing and labeling all of the permutations in order, we get the
    following sequence for n = 3:

        "123"
        "132"
        "213"
        "231"
        "312"
        "321"

    Given n and k, return the kth permutation sequence.

    ==============================================
    FUNCTION: string getPermutation(int n, int k);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 3
    Output: "213"

    --- Example 2 ---
    Input: n = 4, k = 9
    Output: "2314"

    --- Example 3 ---
    Input: n = 3, k = 1
    Output: "123"


    *** Constraints ***
    1 <= n <= 9
    1 <= k <= n!

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  22.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string getPermutation(int n, int k)
    {
        int fact = 1;
        std::vector<int> nums;

        for(int i = 1; i < n; i++)
        {
            fact = fact * i;
            nums.push_back(i);
        }

        nums.push_back(n);
        k = k-1;
        std::string result = "";

        while(true)
        {
            result = result + std::to_string(nums[k/fact]);
            nums.erase(nums.begin() + k/fact);

            if(nums.size() == 0)
                break;

            k = k % fact;
            fact = fact / nums.size();
        }

        return result;
    }
};
