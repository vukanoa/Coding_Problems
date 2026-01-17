/*
    ============
    === EASY ===
    ============

    ================================
    1678) Goal Parser Interpretation
    ================================

    ============
    Description:
    ============

    You own a Goal Parser that can interpret a string command. The command
    consists of an alphabet of "G", "()" and/or "(al)" in some order. The Goal
    Parser will interpret "G" as the string "G", "()" as the string "o", and
    "(al)" as the string "al". The interpreted strings are then concatenated in
    the original order.

    Given the string command, return the Goal Parser's interpretation of
    command.

    ===========================================
    FUNCTION: string interpret(string command);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: command = "G()(al)"
    Output: "Goal"
    Explanation: The Goal Parser interprets the command as follows:
    G -> G
    () -> o
    (al) -> al
    The final concatenated result is "Goal".

    --- Example 2 ---
    Input: command = "G()()()()(al)"
    Output: "Gooooal"

    --- Example 3 ---
    Input: command = "(al)G(al)()()G"
    Output: "alGalooG"

    *** Constraints ***
    1 <= command.length <= 100
    command consists of "G", "()", and/or "(al)" in some order.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Simulation problem.

*/

/* Time  Beats: 41.32% */
/* Space Beats: 16.07% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string interpret(string command)
    {
        const int N = command.size();
        string result;
        result.reserve(N); // At worst we'll need O(N) Space if all are Gs

        int i = 0;
        while (i < N)
        {
            if (command[i] == 'G')
            {
                result += 'G';
                i++;
            }
            else
            {
                if (command[i+1] == ')')
                {
                    result += 'o';
                    i += 2;
                }
                else
                {
                    result += "al";
                    i += 4;
                }
            }
        }

        return result;
    }
};
