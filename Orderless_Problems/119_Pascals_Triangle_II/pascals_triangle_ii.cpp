#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    119) Pascals Triangle II
    ===========================

    ============
    Description:
    ============

    Given an integer rowIndex, return the rowIndexth (0-indexed) row of the
    Pascal's triangle.

    In Pascal's triangle, each number is the sum of the two numbers directly
    above it as shown:

        1
       1 1
      1 2 1
     1 3 3 1
    1 4 6 4 1


    Follow up: Could you optimize your algorithm to use only O(rowIndex) extra
               space?


    ===========================================
    FUNCTION: vector<int> getRow(int rowIndex);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rowIndex = 3
    Output: [1,3,3,1]

    --- Example 2 ---
    Input: rowIndex = 0
    Output: [1]

    --- Example 3 ---
    Input: rowIndex = 1
    Output: [1,1]


    *** Constraints ***
    0 <= rowIndex <= 33

*/

/* Time  Beats: 38.42% */
/* Space Beats: 22.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> getRow(int rowIndex)
    {
        if (rowIndex == 0)
            return {1};
        else if (rowIndex == 1)
            return {1, 1};

        std::vector<int> vec_rowIndex = {1, 1};
        for (int i = 2; i <= rowIndex; i++)
        {
            std::vector<int> tmp = vec_rowIndex;

            for (int j = 1; j < vec_rowIndex.size(); j++)
                tmp[j] = vec_rowIndex[j-1] + vec_rowIndex[j];

            tmp.push_back(1);
            vec_rowIndex = tmp;
        }

        return vec_rowIndex;
    }
};
