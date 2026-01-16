/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    3) Longest Substring Without Repeating Characters
    =================================================

    ============
    Description:
    ============

    Given a string s, find the length of the longest substring(not a
    subsequence) without a repeating characters.

    ======================================================
    FUNCTION: int lengthOfLongestSubstring(string s);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.

    --- Example 2 ---
    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

    --- Example 3 ---
    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the lenght of 3.

    --- Example 4 ---
    Input: s = "svesvhjzhwwj"
    Output: 6
    Explanation: The answer is "esvhjz", with the length of 6.

    *** Constraints ***
    0 <= s.length <= 5 * 10^4
    s consists of English letters, digits, symbols and spaces.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We can use a basic HashSet to check, in O(1), if a certain character exists
    in a current window.

    If it does, move the left boundary to the right and remove that leftmost
    character from the Set.
    Do that until we end up with a valid window(substring).

    Insert the current character to the set(if it doesn't already exist).
    Current character is pointed to by our "R" pointer.

    Do that until "current character", i.e. "R" pointer goes out of bounds.

*/

/* Time  Beats: 40.53% */
/* Space Beats: 19.60% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Set {
public:
    int lengthOfLongestSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        unordered_set<char> uset;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            while (uset.find(s[R]) != uset.end())
            {
                uset.erase(s[L]);
                L++;
            }
            uset.insert(s[R]);

            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even better implementation

    Since it is said:
        "s consists of English letters, digits, symbols and spaces."

    that means that we can have a:
        vector<int> ascii(128, -1);

    instead of a Hash Set.

*/

/* Time  Beats: 98.50% */
/* Space Beats: 85.65% */

/* Time  Complexity: O(N) */
/*
    Space Complexity: O(128) ==> O(1)
    Since it is said that s consists of English letters, digits, symbols and
    spaces.
*/
class Solution_Using_Array {
public:
    int lengthOfLongestSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        // -1 designates that certan symbol didn't appear yet
        int ascii_char_last_appeared_at_idx[128] = {-1};

        int L = 0;
        int R = 0;
        while (R < N)
        {
            int index = ascii_char_last_appeared_at_idx[s[R]];

            if (index != -1 && L <= index && index < R)
                L = index + 1;
            
            ascii_char_last_appeared_at_idx[s[R]] = R;

            // Current_window_length = R - L + 1
            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 97.47% */
/* Space Beats: 90.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_HashMap {
public:
    int lengthOfLongestSubstring(string s)
    {
        const int N = s.length();
        int result = 0;

        int ascii[128] = {0};

        int L = 0;
        int R = 0;
        while (R < N)
        {
            ascii[s[R]]++;

            while (ascii[s[R]] > 1)
                ascii[s[L++]]--;

            // Current_window_length = R - L + 1
            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};
