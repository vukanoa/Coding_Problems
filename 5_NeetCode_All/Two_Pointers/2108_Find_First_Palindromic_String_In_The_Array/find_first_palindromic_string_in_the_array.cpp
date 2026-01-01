#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ================================================
    2108) Find First Palindromic String in the Array
    ================================================

    ============
    Description:
    ============

    Given an array of strings words, return the first palindromic string in the
    array. If there is no such string, return an empty string "".

    A string is palindromic if it reads the same forward and backward.

    ========================================================
    FUNCTION: string firstPalindrome(vector<string>& words);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abc","car","ada","racecar","cool"]
    Output: "ada"
    Explanation: The first string that is palindromic is "ada".
    Note that "racecar" is also palindromic, but it is not the first.

    --- Example 2 ---
    Input: words = ["notapalindrome","racecar"]
    Output: "racecar"
    Explanation: The first and only string that is palindromic is "racecar".

    --- Example 3 ---
    Input: words = ["def","ghi"]
    Output: ""
    Explanation: There are no palindromic strings, so the empty string is
                 returned.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists only of lowercase English letters.

*/

using namespace std;

/* Time  Beats: 98.09% */
/* Space Beats: 70.81% */

/* Time  Complexity: O(n * length_of_the_longest_word_in_words) */
/* Space Complexity: O(1)                                       */
class Solution {
public:
    string firstPalindrome(vector<string>& words)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        for (int i = 0; i < words.size(); i++)
        {
            int left  = 0;
            int right = words[i].length() - 1;

            bool palindrome = true;
            while (left < right)
            {
                if (words[i][left++] != words[i][right--])
                {
                    palindrome = false;
                    break;
                }
            }

            if (palindrome)
                return words[i];
        }

        return "";
    }
};
