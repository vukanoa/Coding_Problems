/*
    ============
    === HARD ===
    ============

    ===========================
    753) Cracking the Safe
    ===========================

    ============
    Description:
    ============

    There is a safe protected by a password. The password is a sequence of n
    digits where each digit can be in the range [0, k - 1].

    The safe has a peculiar way of checking the password. When you enter in a
    sequence, it checks the most recent n digits that were entered each time
    you type a digit.

        + For example, the correct password is "345" and you enter in "012345":
            + After typing 0, the most recent 3 digits is "0", which is incorrect.
            + After typing 1, the most recent 3 digits is "01", which is incorrect.
            + After typing 2, the most recent 3 digits is "012", which is incorrect.
            + After typing 3, the most recent 3 digits is "123", which is incorrect.
            + After typing 4, the most recent 3 digits is "234", which is incorrect.
            + After typing 5, the most recent 3 digits is "345", which is correct and the safe unlocks.

    Return any string of minimum length that will unlock the safe at some point
    of entering it.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1, k = 2
    Output: "10"
    Explanation: The password is a single digit, so enter each digit. "01"
                 would also unlock the safe.

    --- Example 2 ---
    Input: n = 2, k = 2
    Output: "01100"
    Explanation: For each possible password:
    - "00" is typed in starting from the 4th digit.
    - "01" is typed in starting from the 1st digit.
    - "10" is typed in starting from the 3rd digit.
    - "11" is typed in starting from the 2nd digit.
    Thus "01100" will unlock the safe. "10011", and "11001" would also unlock
    the safe.


    *** Constraints ***
    1 <= n <= 4
    1 <= k <= 10
    1 <= kn <= 4096

*/

#include <cmath>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Skip over this problem, trust me.

*/

/* Time  Beats: 58.01% */
/* Space Beats: 66.47% */

/* Time  Complexity: O(k^n) */
/* Space Complexity: O(k^n) */
class Solution {
public:
    string crackSafe(int n, int k)
    {
        string result;
        int total = static_cast<int>(pow(k, n));

        // Initialize with n zeros
        for (int i = 0; i < n; ++i)
            result.push_back('0');

        unordered_set<string> visited;
        visited.insert(result);

        dfs(result, total, visited, n, k);

        return result;
    }

private:
    bool dfs(string& result,
             int goal,
             unordered_set<string>& visited,
             int n,
             int k)
    {
        if (static_cast<int>(visited.size()) == goal)
            return true;

        // Last n - 1 characters
        string prev = result.substr(result.size() - n + 1);

        for (int digit = 0; digit < k; digit++)
        {
            string next = prev + static_cast<char>('0' + digit);

            if (visited.count(next) == 0)
            {
                visited.insert(next);
                result.push_back(static_cast<char>('0' + digit));

                if (dfs(result, goal, visited, n, k))
                    return true;

                // Backtrack
                visited.erase(next);
                result.pop_back();
            }
        }

        return false;
    }
};
