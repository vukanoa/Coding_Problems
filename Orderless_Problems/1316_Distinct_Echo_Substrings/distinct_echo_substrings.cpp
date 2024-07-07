#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===============================
    1316) Distrinct Echo Substrings
    ===============================

    ============
    Description:
    ============

    Return the number of distinct non-empty substrings of text that can be
    written as the concatenation of some string with itself (i.e. it can be
    written as a + a where a is some string).

    ==================================================
    FUNCTION: int distinctEchoSubstrings(string text);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: text = "abcabcabc"
    Output: 3
    Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".

    --- Example 2 ---
    Input: text = "leetcodeleetcode"
    Output: 2
    Explanation: The 2 substrings are "ee" and "leetcodeleetcode".

    *** Constraints ***
    1 <= text.length <= 2000
    text has only lowercase English letters.

*/

class Solution {
public:
    int distinctEchoSubstrings(std::string text)
    {
        std::unordered_set<std::string> uset;

        for (int len = 1; len <= text.length() / 2; len++)
        {
            int left  = 0;
            int right = len;
            int count = 0;
            while (left < text.length() - len)
            {
                if (text[left] == text[right])
                    count++;
                else
                    count = 0;

                if (count == len)
                {
                    uset.insert(text.substr(left - len + 1, left + 1));
                    count--;
                }

                left++;
                right++;
            }
        }

        return uset.size();
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    We will use 2 pointers l and r to count equal characters for different
    lengths of substrings (len).

    Let's consider these 3 cases: 


        1) If counter reaches window length (len) then we record a substring. 

            a b c a b c a    count = 3;
            ~~~~~ ^^^^^

            
            

        2) We disregard current substring when we encounter chars that are not
           equal ('b' and 'c' for example), thus we reset the counter.  
            
            a b a c    count = 1;
            L   R

            a b a c    count = 0;
              L   R



        3) When we record a substring, we move windows thus leaving a character
           behind, this means we have to decrease the counter.  

            a b c a b c a
            ^ ~~~~~ ^^^^^
            |
         no longer need to count


*/

/* Time  Beats: 34.04% */
/* Space Beats: 17.02% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int distinctEchoSubstrings(std::string text)
    {
        const int n = text.length();
        std::unordered_set<std::string> uset;
       
        for (int len = 1; len <= n / 2; len++)
        {
            int left  = 0;
            int right = len;
            int count = 0;

            while (left < n - len)
            {
                if (text[left] == text[right])
                    count++;
                else
                    count = 0;

                if (count == len)
                {
                    uset.insert(text.substr(left - len + 1, len));
                    count--;
                }

                left++;
                right++;
            }
        }
       
        return uset.size();
    }
};
