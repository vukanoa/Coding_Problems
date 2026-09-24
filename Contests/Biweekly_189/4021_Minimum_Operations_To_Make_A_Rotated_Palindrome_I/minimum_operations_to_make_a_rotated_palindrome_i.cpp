/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    4021) Minimum Operations to Make a Rotated Palindrome I
    =======================================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    You can perform the following operations any number of times (including
    zero) and in any order:

        + Increment: Choose any index i and replace s[i] with the next
                     lowercase English letter. The letter after 'z' is 'a'.

        + Left rotate: Move the first character of the string to the end.

    Return the minimum number of operations required to make s a .

    ======================================
    FUNCTION: int minOperations(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc"
    Output: 2
    Explanation:
    One optimal solution:
        Left rotate the string: "abc" -> "bca".
        Increment 'a' to 'b': "bca" -> "bcb".
        "bcb" is a palindrome. Thus, the answer is 2.

    --- Example 2 ---
    Input: s = "yb"
    Output: 3
    Explanation:
        Increment the first character three times: "yb" -> "zb" -> "ab" -> "bb"
        "bb" is a palindrome. Thus, the answer is 3.


    *** Constraints ***
    2 <= s.length <= 2000
    s consists only of lowercase English letters.

*/

#include <climits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the Constraints are small enough we can try to find the best answer
    using only "Increment" operation but for EVERY possible rotation.

    It would be complicated to actually remove the first character and then
    append, thus we use a common stirng trick where we concatenate the original
    string to itself and then simply work with a fixed length of N.

*/

/* Time  Beats: 85.67% */
/* Space Beats: 35.36% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int minOperations(string s)
    {
        const int N = s.size();
        int result = INT_MAX;

        s += s;

        for (int rotation = 0; rotation < N; rotation++)
        {
            int start = rotation;
            int end   = start + N-1;

            int needed_operations = 0;
            while (start < end)
            {
                int smaller_idx = s[start] - 'a';
                int bigger_idx  = s[end]   - 'a';

                if (smaller_idx > bigger_idx)
                    swap(smaller_idx, bigger_idx);

                if (s[start] != s[end])
                    needed_operations += min( abs(smaller_idx - bigger_idx     ),
                                              abs(smaller_idx - bigger_idx + 26) );

                ++start;
                --end;
            }

            result = min(result, rotation + needed_operations);
        }

        return result;
    }
};
