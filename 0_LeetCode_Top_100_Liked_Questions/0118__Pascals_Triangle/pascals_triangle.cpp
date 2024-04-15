#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    118) Pascal's Triangle
    ===========================

    ============
    Description:
    ============

    Given an integer "numRows", return the first numRows of Pascal's Triangle.

    In Pascal's Triangle, each number is the sum of the two numbers directly
    above it as shown:

        1
       1 1
      1 2 1
     1 3 3 1
    1 4 6 4 1


    ====================================================
    FUNCTION: vector<vector<int>> generate(int numRows);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  numRows = 5
    Output: [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]

    --- Example 2 ---
    Input:  numRows = 1
    Output: [[1]]

    *** Constraints ***
    1 <= numRows <= 30

*/


/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory as well, though this one is a bit more easier to grasp in
    my opinion.

*/

/* Time  Beats: 100% */
/* Space Beats: 6.93% */

/*
    Time  Complexity: O(numRows/2 * (numRows + 1)) ==> O(numRows^2)

    It's sum of first "n" numbers: N/2 * (N + 1)
*/
/*
    Space Complexity: O(numRows^2)
*/
class Solution_Intuitive {
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        std::vector<std::vector<int>> results;

        for (int i = 0; i < numRows; i++)
        {
            std::vector<int> vec(i+1, 1);
            results.push_back(vec);
        }

        for (int i = 2; i < numRows; i++)
        {
            for (int j = 1; j < results[i].size() - 1; j++)
                results[i][j] = results[i-1][j-1] + results[i-1][j];
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is better than the above one, though it isn't as intuitive to
    write this.

    The whole idea is that for every row we're initializing a vector to have
    exactly the right amount of elements and we assign them all to 1.

    The main part about this Solution is this line:
            for (int j = 1; j < i; j++)

    Why is the boundary "i"?

    Since we're initializing a vector with all 1's for each row, we can notice
    that we don't have to change anything to row=0 and row=1.

    However, for all the other rows, we can notice that 0th and last element in
    a current row are always going to be 1.

    So this way, by starting a "j" from 1 and going until j < i, and "i" is the
    current row, we're making sure to only do the middle ones.

    For numRows = 5, we'll only be processing "X" ones in the picture below:

          1
         1 1
        1 X 1
       1 X X 1
      1 X X X 1

*/

/* Time  Beats:  100% */
/* Space Beats: 95.1% */

/*
    Time  Complexity: O(numRows/2 * (numRows + 1)) ==> O(numRows^2)

    It's sum of first "n" numbers: N/2 * (N + 1)
*/
/*
    Space Complexity: O(numRows^2)
*/
class Solution_Efficient {
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        std::vector<std::vector<int>> results;

        for (int i = 0; i < numRows; i++)
        {
            std::vector<int> row(i + 1, 1);

            for (int j = 1; j < i; j++)
                row[j] = results[i - 1][j - 1] + results[i - 1][j];

            results.push_back(row);
        }

        return results;
    }
};


int
main()
{
    Solution_Intuitive sol_intuitive;
    Solution_Efficient sol_eff;

    /* Example 1 */
    int numRows = 5;

    /* Example 2 */
    // int numRows = 1;

    /* Example 3 */
    // int numRows = 2;

    /* Example 4 */
    // int numRows = 3;

    /* Example 5 */
    // int numRows = 4;

    std::cout << "\n\t=========================";
    std::cout << "\n\t=== PASCAL'S TRIANGLE ===";
    std::cout << "\n\t=========================\n";


    /* Write Input */
    std::cout << "\n\tPascal's Triangle of SIZE = " << numRows << "\n";


    /* Solution */
    // std::vector results = sol_read.generate(numRows);
    std::vector results = sol_eff.generate(numRows);


    /* Write Output */
    bool first = true;
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
