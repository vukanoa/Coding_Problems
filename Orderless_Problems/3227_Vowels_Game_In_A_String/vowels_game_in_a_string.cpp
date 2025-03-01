/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3227) Vowels Game in a String
    =============================

    ============
    Description:
    ============

    Alice and Bob are playing a game on a string.

    You are given a string s, Alice and Bob will take turns playing the
    following game where Alice starts first:

        On Alice's turn, she has to remove any non-empty

    from s that contains an odd number of vowels.
    On Bob's turn, he has to remove any non-empty

        from s that contains an even number of vowels.

    The first player who cannot make a move on their turn loses the game. We
    assume that both Alice and Bob play optimally.

    Return true if Alice wins the game, and false otherwise.

    The English vowels are: a, e, i, o, and u.

    ======================================
    FUNCTION: bool doesAliceWin(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcoder"
    Output: true
    Explanation:
    Alice can win the game as follows:
        Alice plays first, she can delete the underlined substring in s = "leetcoder" which contains 3 vowels. The resulting string is s = "der".
        Bob plays second, he can delete the underlined substring in s = "der" which contains 0 vowels. The resulting string is s = "er".
        Alice plays third, she can delete the whole string s = "er" which contains 1 vowel.
        Bob plays fourth, since the string is empty, there is no valid play for Bob. So Alice wins the game.

    --- Example 2 ---
    Input: s = "bbcd"
    Output: false
    Explanation:
    There is no valid play for Alice in her first turn, so Alice loses the game.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of lowercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If BOTH are playing optimally, think about when is Alice going to lose?
    If and only if there is not a single vowel present.

    In all the other cases, Alice will win.

    1) If there's an ODD  number of vowels that is greater than 0, Alice takes
       all of the vowels.

    2) If there's an EVEN number of vowels that is greater than 0, Alice takes
       all of the vowels BUT ONE. Leaves only one vowel.

       Since Bob cam remove only if there's an EVEN number of vowels, he loses.

*/

/* Time  Beats: 26.67% */
/* Space Beats:  6.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool doesAliceWin(string s)
    {
        const int N = s.length();

        unordered_set<int> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < N; i++)
        {
            if (vowels.count(s[i]))
                return true;
        }

        return false;
    }
};
