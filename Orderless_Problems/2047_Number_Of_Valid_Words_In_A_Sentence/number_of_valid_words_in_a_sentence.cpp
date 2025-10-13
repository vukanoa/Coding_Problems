/*
    ============
    === EASY ===
    ============

    =========================================
    2047) Number of Valid Words in a Sentence
    =========================================

    ============
    Description:
    ============

    A sentence consists of lowercase letters ('a' to 'z'), digits ('0' to '9'),
    hyphens ('-'), punctuation marks ('!', '.', and ','), and spaces (' ')
    only. Each sentence can be broken down into one or more tokens separated by
    one or more spaces ' '.

    A token is a valid word if all three of the following are true:

        + It only contains lowercase letters, hyphens, and/or punctuation
          (no digits).

        + There is at most one hyphen '-'. If present, it must be surrounded by
          lowercase characters ("a-b" is valid, but "-ab" and "ab-" are not
          valid).

        + There is at most one punctuation mark. If present, it must be at the
          end of the token ("ab,", "cd!", and "." are valid, but "a!b" and
          "c.," are not valid).

    Examples of valid words include "a-b.", "afad", "ba-c", "a!", and "!".

    Given a string sentence, return the number of valid words in sentence.

    ===============================================
    FUNCTION: int countValidWords(string sentence);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sentence = "cat and  dog"
    Output: 3
    Explanation: The valid words in the sentence are "cat", "and", and "dog".

    --- Example 2 ---
    Input: sentence = "!this  1-s b8d!"
    Output: 0
    Explanation: There are no valid words in the sentence.
    "!this" is invalid because it starts with a punctuation mark.
    "1-s" and "b8d" are invalid because they contain digits.

    --- Example 3 ---
    Input: sentence = "alice and  bob are playing stone-game10"
    Output: 5
    Explanation: The valid words in the sentence are "alice", "and", "bob",
    "are", and "playing".
    "stone-game10" is invalid because it contains digits.


    *** Constraints ***
    1 <= sentence.length <= 1000
    sentence only contains lowercase English letters, digits, ' ', '-', '!',
    '.', and ','.
    There will be at least 1 token.

*/

#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  49.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countValidWords(string sentence)
    {
        const int N = sentence.size();
        int result = 0;

        istringstream iss(sentence);
        string token;

        unordered_set<char> punctuation = {'.', ',', '!'};

        while (iss >> token)
        {
            bool valid = true;
            int hyphens = 0;
            for (unsigned i = 0; i < token.length(); i++)
            {
                char chr = token[i];
                if (isdigit(chr))
                {
                    valid = false;
                    break;
                }

                // If it's a punctuation and NOT a LAST character, then it's INVALID!
                if ((i < (token.length()-1)) && punctuation.count(chr))
                {
                    valid = false;
                    break;
                }

                if (chr == '-')
                {
                    if (hyphens > 0)
                    {
                        valid = false; // Because this is a 2nd hyphen in this token
                        break;
                    }

                    if (i == 0 || i == (token.length()-1)) // First or last
                    {
                        valid = false;
                        break;
                    }

                    if ( ! isalpha(token[i-1]) ||  ! isalpha(token[i+1]))
                    {
                        valid = false;
                        break;
                    }

                    hyphens++;
                }
            }

            if (valid)
                result++;
        }

        return result;
    }
};
