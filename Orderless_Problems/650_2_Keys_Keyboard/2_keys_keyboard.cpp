#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    650) 2 Keys Keyboard
    ===========================

    ============
    Description:
    ============

    There is only one character 'A' on the screen of a notepad. You can perform
    one of two operations on this notepad for each step:

        + Copy All: You can copy all the characters present on the screen (a
          partial copy is not allowed).

        + Paste: You can paste the characters which are copied last time.

    Given an integer n, return the minimum number of operations to get the
    character 'A' exactly n times on the screen.

    ===============================
    FUNCTION: int minSteps(int n);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3
    Output: 3
    Explanation: Initially, we have one character 'A'.
    In step 1, we use Copy All operation.
    In step 2, we use Paste operation to get 'AA'.
    In step 3, we use Paste operation to get 'AAA'.

    --- Example 2 ---
    Input: n = 1
    Output: 0


    *** Constraints ***
    1 <= n <= 1000

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 52.56% */
/* Space Beats: 41.13% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_DP {
public:
    int minSteps(int n)
    {
        if (n == 1)
            return 0;

        vector<int> min_operations(n + 1, INT_MAX);
        min_operations[1] = 0;

        for (int curr_count = 2; curr_count <= n; curr_count++)
        {
            for (int factor = 1; factor * factor <= curr_count; factor++)
            {
                if (curr_count % factor == 0)
                {
                    min_operations[curr_count] = min(min_operations[curr_count], min_operations[factor] + curr_count / factor);

                    if (factor != curr_count / factor)
                        min_operations[curr_count] = min(min_operations[curr_count], min_operations[curr_count / factor] + factor);
                }
            }
        }

        return min_operations[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 69.44% */
/* Space Beats: 72.78% */

/* Time  Complexity: O(√n) */ // O(sqrt(n))
/* Space Complexity: O(1) */
class Solution {
public:
    int minSteps(int n)
    {
        if (n == 1)
            return 0;

        int curr_As = 2;
        int count_operations = 2;
        int paste = 1;

        while (curr_As != n)
        {
            if (n % curr_As == 0)
            {
                paste = curr_As;    // Copy
                count_operations++;
            }

            curr_As += paste;
            count_operations++; // Paste
        }

        return count_operations;
    }
};
