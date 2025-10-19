/*
    ============
    === EASY ===
    ============

    =========================================================
    2011) Final Value of Variable After Performing Operations
    =========================================================

    ============
    Description:
    ============

    There is a programming language with only four operations and one variable
    X:

        ++X and X++ increments the value of the variable X by 1.
        --X and X-- decrements the value of the variable X by 1.

    Initially, the value of X is 0.

    Given an array of strings operations containing a list of operations,
    return the final value of X after performing all the operations.

    ====================================================================
    FUNCTION: int finalValueAfterOperations(vector<string>& operations);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: operations = ["--X","X++","X++"]
    Output: 1
    Explanation: The operations are performed as follows:
    Initially, X = 0.
    --X: X is decremented by 1, X =  0 - 1 = -1.
    X++: X is incremented by 1, X = -1 + 1 =  0.
    X++: X is incremented by 1, X =  0 + 1 =  1.

    --- Example 2 ---
    Input: operations = ["++X","++X","X++"]
    Output: 3
    Explanation: The operations are performed as follows:
    Initially, X = 0.
    ++X: X is incremented by 1, X = 0 + 1 = 1.
    ++X: X is incremented by 1, X = 1 + 1 = 2.
    X++: X is incremented by 1, X = 2 + 1 = 3.

    --- Example 3 ---
    Input: operations = ["X++","++X","--X","X--"]
    Output: 0
    Explanation: The operations are performed as follows:
    Initially, X = 0.
    X++: X is incremented by 1, X = 0 + 1 = 1.
    ++X: X is incremented by 1, X = 1 + 1 = 2.
    --X: X is decremented by 1, X = 2 - 1 = 1.
    X--: X is decremented by 1, X = 1 - 1 = 0.

    *** Constraints ***
    1 <= operations.length <= 100
    operations[i] will be either "++X", "X++", "--X", or "X--".

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations)
    {
        const int N = operations.size();
        int result = 0;

        for (const string& op : operations)
        {
            for (const char& chr : op)
            {
                if (chr == '-')
                {
                    result--;
                    break;
                }
                
                if (chr == '+')
                {
                    result++;
                    break;
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int finalValueAfterOperations(vector<string>& operations)
    {
        const int N = operations.size();
        int result = 0;

        for (const string& op : operations)
        {
            if (op[1] == '-') // Because X absolutely MUST be at idx:0 or idx:2
                result--;
            else
                result++;
        }

        return result;
    }
};
