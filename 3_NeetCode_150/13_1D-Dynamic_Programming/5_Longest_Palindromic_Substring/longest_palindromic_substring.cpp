/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    5) Longest Palindromic Substring
    ================================

    Given a string s, return the longest palindromic substring in s

    --- Example 1 ---
    Input: s = "babad"
    Output: "bab"
    Explanation: "aba" is also a valid answer

    --- Example 2 ---
    Input: s = "cbbd"
    Output: "bb"

    *** Constraints ***
    1 <= s.length <= 1000
    s consists of only digits and English letters
*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a standard way to solve this popular "LPS" problem.

    The idea is the realize we have two kinds of palindromes:

        1. Palindromes of ODD  length
        2. Palindromes of EVEN length

    For each type, we consider each index as a starting point and then we're
    extending the palindrome as far as we can go, thus having an O(N^2).

    However, it's important to note that EVEN palindromes CANNOT start at index
    N-1, because its next counter-part would be Out-of-Bounds.

    Other than that it's straightforward.

*/

/* Time  Beats: 68.34% */
/* Space Beats: 92.84% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */ // Final result is not considered EXTRA space
class Solution_LPS{
public:
    string longestPalindrome(string s)
    {
        const int N = s.size();

        int result_len = 0;
        int start = -1;
        int end   = -1;

        /* Odd */
        for (int mid = 0; mid < N; mid++)
        {
            int L = mid;
            int R = mid;

            int curr_substr_len = 1; // Starts with length 1(ONE)
            while (L >= 0 && R < N)
            {
                if (s[L] != s[R])
                    break;

                if (result_len < curr_substr_len)
                {
                    result_len = curr_substr_len;
                    start = L;
                    end   = R;
                }

                L--; // Decrement
                R++; // Increment

                curr_substr_len += 2;
            }
        }

        /* Even palindromes */
        for (int mid = 0; mid < N-1; mid++) // mid must stop at N-2 because:
        {
            int L = mid;
            int R = mid+1; // If mid = N-1, then R = N (null terminator, valid)
                           // However, after R++, R becomes N+1, causing
                           // undefined behavior (possible segfault or garbage
                           // access). That's why it's important for mid to go:
                           //
                           // [0...N-2] and not [0...N-1]

            int curr_substr_len = 2; // Starts with length 2(TWO)
            while (L >= 0 && R < N)
            {
                if (s[L] != s[R])
                    break;

                if (result_len < curr_substr_len)
                {
                    result_len = curr_substr_len;
                    start = L;
                    end   = R;
                }

                L--; // Decrement
                R++; // Increment

                curr_substr_len += 2;
            }
        }

        return s.substr(start, end - start + 1);
    }
};




/*
    ============================
    === Manacher's Algorithm ===
    ============================
*/
/*
    ------------
    --- IDEA ---
    ------------

    Note: 'Position' pertains to expanded string. The one where separator
          character is added between every character in the original string
          plus two more(one at the very beginning and one at the very end)

          'Index', on the other hand, pertains to the original string.

                     a b a a b
        Indices ->   0 1 2 3 4

                     $ a $ b $ a $ a $ b $
        Positions -> 0 1 2 3 4 5 6 7 8 9 10
    

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Manacher_Algorithm {
public:
    string longestPalindrome(string s)
    {
        const int N = s.size();
        if (N == 1)
            return s;

        int SIZE = 2 * N + 1;

        int LPS[SIZE];
        LPS[0] = 0;
        LPS[1] = 1;

        int center_position = 1;       // center_position_position
        int right_border_position = 2; // center_position_right_position
        int i = 0;                     // current_right_position
        int i_mirror;                  // current_left_position

        int max_LPS_length = 0;
        int max_LPS_center_position = 0;

        int start_index = -1;
        int end_index   = -1;

        int difference = -1;
        int expand     = -1;

        for (i = 2; i < SIZE; i++)
        {
            i_mirror = 2 * center_position - i;

            expand = 0;
            difference = right_border_position - i;

            if (difference >= 0)
            {
                // Case 1
                if (LPS[i_mirror] < difference)
                    LPS[i] = LPS[i_mirror];

                // Case 2
                else if (LPS[i_mirror] == difference && right_border_position == SIZE - 1)
                    LPS[i] = LPS[i_mirror];

                // Case 3
                else if (LPS[i_mirror] == difference && right_border_position < SIZE - 1)
                {
                    LPS[i] = LPS[i_mirror];

                    // Expansions required
                    expand = 1;
                }

                // Case 4
                else if (LPS[i_mirror] > difference)
                {
                    LPS[i] = difference;

                    // Expansion required
                    expand = 1;
                }
            }
            else
            {
                LPS[i] = 0;

                // Expansion required
                expand = 1;
            }

            // Expansion required
            if (expand == 1)
            {
                while (
                        (
                            (i + LPS[i]) < SIZE
                            &&
                            (i - LPS[i]) > 0
                        )
                        &&
                        (
                            ((i + LPS[i] + 1) % 2 == 0)
                            ||
                            (s[(i + LPS[i] + 1) / 2] == s[(i - LPS[i] - 1) / 2])
                        )
                    )
                {
                    LPS[i]++;
                }
            }

            if (LPS[i] > max_LPS_length)
            {
                max_LPS_length = LPS[i];
                max_LPS_center_position = i;
            }

            if (i + LPS[i] > right_border_position)
            {
                center_position = i;
                right_border_position = i + LPS[i];
            }
        }

        // Real indexes in string 's', that is -> w/o separator characters
        start_index = (max_LPS_center_position - max_LPS_length) / 2;
        end_index   = start_index + max_LPS_length - 1;

        string longest_pal_substr = "";

        for (i = start_index; i <= end_index; i++)
            longest_pal_substr += s[i];

        return longest_pal_substr;
    }
};
