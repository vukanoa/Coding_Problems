/*
    ============
    === HARD ===
    ============

    ===========================
    936) Stamping the Sequence
    ===========================

    ============
    Description:
    ============

    You are given two strings stamp and target. Initially, there is a string s
    of length target.length with all s[i] == '?'.

    In one turn, you can place stamp over s and replace every letter in the s
    with the corresponding letter from stamp.

        + For example, if stamp = "abc" and target = "abcba", then s is "?????"
          initially. In one turn you can:
            + place stamp at index 0 of s to obtain "abc??",
            + place stamp at index 1 of s to obtain "?abc?", or
            + place stamp at index 2 of s to obtain "??abc".

        Note that stamp must be fully contained in the boundaries of s in order
        to stamp (i.e., you cannot place stamp at index 3 of s).

    We want to convert s to target using at most 10 * target.length turns.

    Return an array of the index of the left-most letter being stamped at each
    turn. If we cannot obtain target from s within 10 * target.length turns,
    return an empty array.

    ================================================================
    FUNCTION: vector<int> movesToStamp(string stamp, string target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stamp = "abc", target = "ababc"
    Output: [0,2]
    Explanation: Initially s = "?????".
    - Place stamp at index 0 to get "abc??".
    - Place stamp at index 2 to get "ababc".
    [1,0,2] would also be accepted as an answer, as well as some other answers.

    --- Example 2 ---
    Input: stamp = "abca", target = "aabcaca"
    Output: [3,0,1]
    Explanation: Initially s = "???????".
    - Place stamp at index 3 to get "???abca".
    - Place stamp at index 0 to get "abcabca".
    - Place stamp at index 1 to get "aabcaca".


    *** Constraints ***
    1 <= stamp.length <= target.length <= 1000
    stamp and target consist of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Way too difficult, you should skip this one, trust me)

*/

/* Time  Beats: 5.08% */
/* Space Beats: 5.58% */

/* Time  Complexity: O(N^4) */
/* Space Complexity: O(N)   */
class Solution {
public:
    vector<int> movesToStamp(string stamp, string target)
    {
        const int N = stamp.size();
        vector<int> result;
        auto total_stamp = 0, turn_stamp = -1;

        while (turn_stamp)
        {
            turn_stamp = 0;

            for (int size = N; size > 0; size--) 
            {
                for (auto i = 0; i <= N - size; i++)
                {
                    auto new_stamp = string(i, '*') +
                                     stamp.substr(i, size) +
                                     string(N - size - i, '*');

                    auto idx = target.find(new_stamp);
                    while (idx != string::npos)
                    {
                        result.push_back(idx);
                        turn_stamp += size;

                        fill(begin(target) + idx, begin(target) + idx + N, '*');

                        idx = target.find(new_stamp);
                    }
                }
            }

            total_stamp += turn_stamp;
        }

        reverse(begin(result), end(result));

        return total_stamp == target.size() ? result : vector<int>();
    }
};
