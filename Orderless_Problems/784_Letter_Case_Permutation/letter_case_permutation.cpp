/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    784) Letter Case Permutation
    ============================

    ============
    Description:
    ============

    Given a string s, you can transform every letter individually to be
    lowercase or uppercase to create another string.

    Return a list of all possible strings we could create. Return the output in
    any order.

    =========================================================
    FUNCTION: vector<string> letterCasePermutation(string s);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a1b2"
    Output: ["a1b2","a1B2","A1b2","A1B2"]

    --- Example 2 ---
    Input: s = "3z4"
    Output: ["3z4","3Z4"]


    *** Constraints ***
    1 <= s.length <= 12
    s consists of lowercase English letters, uppercase English letters, and
    digits.

*/

#include <queue>
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
/* Space Beats:  63.30% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution {
public:
    vector<string> letterCasePermutation(string S)
    {
        if (S.empty())
            return {};

        const int N = S.size();

        queue<string> queue;
        queue.push(S);

        for (int i = 0; i < N; i++)
        {
            if (isdigit(S[i]))
                continue;

            int level_size = queue.size();

            for (int j = 0; j < level_size; j++)
            {
                string node = queue.front();
                queue.pop();

                node[i] = toupper(node[i]);
                queue.push(node);

                node[i] = tolower(node[i]);
                queue.push(node);
            }
        }

        vector<string> result;
        while ( ! queue.empty())
        {
            result.push_back(queue.front());
            queue.pop();
        }

        return result;
    }
};
