#include <iostream>
#include <stack>

/*
    ============
    === EASY ===
    ============

    ===========================
    1598) Crawler Log Folder
    ===========================

    ============
    Description:
    ============

    The Leetcode file system keeps a log each time some user performs a change
    folder operation.

    The operations are described below:

        + "../" : Move to the parent folder of the current folder. (If you are
                  already in the main folder, remain in the same folder).

        + "./" : Remain in the same folder.

        "x/"   : Move to the child folder named x (This folder is guaranteed to
                 always exist).

    You are given a list of strings logs where logs[i] is the operation
    performed by the user at the ith step.

    The file system starts in the main folder, then the operations in logs are
    performed.

    Return the minimum number of operations needed to go back to the main
    folder after the change folder operations.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: logs = ["d1/","d2/","../","d21/","./"]
    Output: 2
    Explanation: Use this change folder operation "../" 2 times and go back to
                 the main folder.

    --- Example 2 ---
    Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
    Output: 3

    --- Example 3 ---
    Input: logs = ["d1/","../","../","../"]
    Output: 0


    *** Constraints ***
    1 <= logs.length <= 10^3
    2 <= logs[i].length <= 10
    logs[i] contains lowercase English letters, digits, '.', and '/'.
    logs[i] follows the format described in the statement.
    Folder names consist of lowercase English letters and digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    There is literally no explanation here. It's really obvious. If you were
    not sure that you should've used a Stack, then I'm not sure there is an
    easier problem that is more obvious for such use case.

    Maybe a famous Blind75 problem: 20 Valid Parentheses.

    Do that one and then come back and you'll see that it will be obvious.

*/

/* Time  Beats: 67.13% */
/* Space Beats: 17.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minOperations(std::vector<std::string>& logs)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        std::stack<std::string> stack;

        for (std::string& log : logs)
        {
            if (log == "./")
                continue;

            if (log == "../")
            {
                if ( ! stack.empty())
                    stack.pop();
            }
            else
                stack.push(log);
        }

        return stack.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 86.73% */
/* Space Beats: 41.82% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int minOperations(vector<string>& logs)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int level = 0;
        for (std::string& log: logs)
        {
            if (log == "../") 
                level -= (level > 0);
            else if (log!="./")
                level++;
        }

        return level;
    }
};
