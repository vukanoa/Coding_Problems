/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1358) Number of Substrings Containing All Three Characters
    ==========================================================

    ============
    Description:
    ============

    Given a string s consisting only of characters a, b and c.

    Return the number of substrings containing at least one occurrence of all
    these characters a, b and c.

    ===========================================
    FUNCTION: int numberOfSubstrings(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcabc"
    Output: 10
    Explanation: The substrings containing at least one occurrence of the
                 characters a, b and c are "abc", "abca", "abcab", "abcabc",
                 "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

    --- Example 2 ---
    Input: s = "aaacb"
    Output: 3
    Explanation: The substrings containing at least one occurrence of the
                 characters a, b and c are "aaacb", "aacb" and "acb".

    --- Example 3 ---
    Input: s = "abc"
    Output: 1


    *** Constraints ***
    3 <= s.length <= 5 x 10^4
    s only consists of a, b or c characters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window problem. When counting Substrings, do NOT forget the
    inter-substrings.

    That's precisely why, when we found a valid substring, we don't increment
    our "result" by one, but by: N - R. To take all the inter-substrings into
    account as well.

*/

/* Time  Beats:  9.68% */
/* Space Beats: 14.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSubstrings(string s)
    {
        const int N = s.length();
        int result = 0;

        int L = 0;
        int R = 0;
        unordered_map<char,int> counter;

        while (R < N)
        {
            char curr_chr = s[R];

            counter[curr_chr]++;

            while (counter.size() == 3)
            {
                result += N - R;

                char leftmost_chr = s[L];

                counter[leftmost_chr]--;
                if (counter[leftmost_chr] == 0)
                    counter.erase(leftmost_chr);

                // Slide-Window
                L++;
            }

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

    Consider this example:

        s = "a b c a b b b c b a b"
             0 1 2 3 4 5 6 7 8 9 10

    And let's say we're at this moment in our iteration:

        s = "a b c a b b b c b a b"
             0 1 2 3 4 5 6 7 8 9 10
                     i

    Our "rightmost_idx" which keeps track of the rightmost index for each of
    the three characters(-1 if it's not found yet), would look like this:

        s = "a b c a b b b c b a b"
             0 1 2 3 4 5 6 7 8 9 10
                 | | i
                 | | |
                 | | |_______
                 | |______  |
                 |       |______
                 |       /  |  |
                 |______/|  |  |
                         |  |  |
                         v  v  v
        rightmost_idx = [3, 4, 2]


    First, we add 1 because the substring from the beginning contains all 3.
    If it DID NOT, then we'd have -1 from the "min" function which would
    neutralize it.

    However, if it did INEED containt all three, then that means we've counted
    the substring that begins all the way at index 0 and ends at curr_idx 'i'.

    That is, we've counted substring:   "a b c a b"

    However, we DIDN'T count substring:   "b c a b"
                                            "c a b"

    But how do we do that?
    Do we, somehow, Slide the window?

    No, we just find(read this carefully) the rightmost_idx of the LEFTMOST
    REQUIRED character.

    Since all 3 are REQUIRED, LEFTMOST REQUIRED CHARACTER here is letter 'c'.
    Why?

    Because we need all three and both 'a' and 'b' can be found further to the
    right of this 'c', up until our current index 'i'(inclusively).

    However, we need precisely that index of letter 'c', that's why we keep
    rightmost_idx.

    Since rightmost_idx of 'c' is 2, that's exactly how many additional
    subtrings we shall take into account.


    So one more time:

        s = "a b c a b b b c b a b"
             0 1 2 3 4 5 6 7 8 9 10
                 | | i
                 | | |
                 | | |_______
                 | |______  |
                 |       |______
                 |       /  |  |
                 |______/|  |  |
                         |  |  |
                         v  v  v
        rightmost_idx = [3, 4, 2]


        result += 1 + min( {rightmost_idx[0], rightmost_idx[1], rightmost_idx[2]} );
                  ^
                  |
          --------|
          |
          |
    This one is counting the substring FROM THE BEGINNING, ie. "a b c a b".

    However, this is not all we need to count.
    Therefore, we add 2 more. Why 2?

    Becuase the rightmost_idx of the LEFTMOST REQURED CHARACTER is at index 2.

        "a b c a b ..."
         0 1 2 3 4
                 i

    Since we've counted the substring that BEGINS at 0, now if we add the
    rightmost_idx, that'll be exactly the amount we need.

    That will NOT include the substring from the beginning again.

*/

/* Time  Beats: 61.55% */
/* Space Beats: 57.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Last_Position_Tracking {
public:
    int numberOfSubstrings(string s)
    {
        const int N = s.length();
        int result = 0;

        // Track last position of a, b, c
        vector<int> rightmost_idx = {-1, -1, -1};

        for (int i = 0; i < N; i++)
        {
            // Update last position of current character
            rightmost_idx[s[i] - 'a'] = i;

            /*
                Add count of valid substrings ending at current position.

                If any character is missing,
                    min will be -1
                Else
                    min gives leftmost required character position
                              (rightmost idx of that leftmost required charac.)
            */
            result += 1 + min( {rightmost_idx[0], rightmost_idx[1], rightmost_idx[2]} );
        }

        return result;
    }
};
