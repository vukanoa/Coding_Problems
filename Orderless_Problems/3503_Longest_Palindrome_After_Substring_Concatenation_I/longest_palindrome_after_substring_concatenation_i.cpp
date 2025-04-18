/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3503) Longest Palindrome After Substring Concatenation I
    ========================================================

    ============
    Description:
    ============

    You are given two strings, s and t.

    You can create a new string by selecting a substring from s
    (possibly empty) and a substring from t (possibly empty), then
    concatenating them in order.

    Return the length of the longest palindrome that can be formed this way.

    ====================================================
    FUNCTION: int longestPalindrome(string s, string t);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a", t = "a"
    Output: 2
    Explanation: Concatenating "a" from s and "a" from t results in "aa", which
                 is a palindrome of length 2.

    --- Example 2 ---
    Input: s = "abc", t = "def"
    Output: 1
    Explanation: Since all characters are different, the longest palindrome is
                 any single character, so the answer is 1.

    --- Example 3 ---
    Input: s = "b", t = "aaaa"
    Output: 4
    Explanation:
    Selecting "aaaa" from t is the longest palindrome, so the answer is 4.




    --- Example 4 ---
    Input: s = "abcde", t = "ecdba"
    Output: 5
    Explanation: Concatenating "abc" from s and "ba" from t results in "abcba",
                 which is a palindrome of length 5.


    *** Constraints ***
    1 <= s.length, t.length <= 30
    s and t consist of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This was done during the contest, so the code is a bit messy.

    The problem is that there are a lot of edge cases, but other than that it's
    a pretty standard "Palindrome" problem.

*/

/* Time  Beats: 97.26% */
/* Space Beats: 98.25% */

/* Time  Complexity: O(N * M * (N + M)) */
/* Space Complexity: O(1)               */
class Solution {
public:
    int longestPalindrome(string s, string t)
    {
        const int length_s = s.size();
        const int length_t = t.size();

        int max_palindrome_length = 0;

        int s_longest = longest_palindrome(s);
        int t_longest = longest_palindrome(t);

        for (int index_s = 0; index_s < length_s; index_s++)
        {
            for (int index_t = length_t - 1; index_t >= 0; index_t--)
            {
                if (s[index_s] == t[index_t])
                {
                    int matched_length = 0;

                    int left  = index_s;
                    int right = index_t;

                    while (left < length_s && right >= 0 && s[left] == t[right])
                    {
                        matched_length += 2;

                        left++;
                        right--;
                    }

                    int max_right_extension = 0;
                    int same_char_count     = 0;

                    if (right >= 0)
                    {
                        int end_index_t = right;

                        char repeated_char_t = t[right];
                        same_char_count = 1;

                        right--;
                        while (right >= 0 && t[right] == repeated_char_t)
                        {
                            same_char_count++;
                            right--;
                        }

                        int palin_suffix_length = 0;
                        for (int start = 0; start <= end_index_t; start++)
                        {
                            if (is_palindrome(t.substr(start, end_index_t - start + 1)))
                            {
                                palin_suffix_length = end_index_t - start + 1;
                                break;
                            }
                        }

                        max_right_extension = max(same_char_count, palin_suffix_length);
                    }

                    int max_left_extension = 0;
                    int left_same_count = 0;
                    if (left < length_s)
                    {
                        int start_index_s = left;

                        char repeated_char_s = s[left];
                        left_same_count = 1;

                        left++;
                        while (left < length_s && s[left] == repeated_char_s)
                        {
                            left_same_count++;
                            left++;
                        }

                        int palin_prefix_length = 0;
                        for (int end = length_s - 1; end >= start_index_s; end--)
                        {
                            if (is_palindrome(s.substr(start_index_s, end - start_index_s + 1)))
                            {
                                palin_prefix_length = end - start_index_s + 1;
                                break;
                            }
                        }

                        max_left_extension = max(left_same_count, palin_prefix_length);
                    }

                    max_palindrome_length = max(max_palindrome_length, matched_length + max(max_left_extension, max_right_extension));
                }
            }
        }

        return max(max_palindrome_length, max(s_longest, t_longest));
    }

private:
    int longest_palindrome(string str)
    {
        int length = str.length();

        string longest_odd_palindrome = "";
        for (int center = 0; center < length; center++)
        {
            int current_length = 1;

            for (int offset = 0; center - offset - 1 >= 0 && center + offset + 1 < length; offset++)
            {
                if (str[center - offset - 1] != str[center + offset + 1])
                    break;

                current_length += 2;
            }

            if (current_length > longest_odd_palindrome.length())
                longest_odd_palindrome = str.substr(center - current_length / 2, current_length);
        }

        string longest_even_palindrome = "";
        for (int center = 0; center < length - 1; center++)
        {
            int current_length = 0;
            for (int offset = 0; center - offset >= 0 && center + offset + 1 < length; offset++)
            {
                if (str[center - offset] != str[center + offset + 1])
                    break;
                else
                    current_length += 2;
            }

            if (current_length > longest_even_palindrome.length())
                longest_even_palindrome = str.substr(center - current_length / 2 + 1, current_length);
        }

        if (longest_odd_palindrome.length() >= longest_even_palindrome.length())
            return longest_odd_palindrome.size();

        return longest_even_palindrome.size();
    }

    bool is_palindrome(string str)
    {
        int left  = 0;
        int right = str.length() - 1;

        while (left < right)
        {
            while (left < right && !alpha_num(str[left]))
                left++;

            while (right > left && !alpha_num(str[right]))
                right--;

            if (tolower((str[left])) != tolower((str[right])))
                return false;

            left++;
            right--;
        }

        return true;
    }

    bool alpha_num(char& character)
    {
        return (character >= 65 && character <= 90)  ||
               (character >= 97 && character <= 122) ||
               (character >= 48 && character <= 57);
    }
};
