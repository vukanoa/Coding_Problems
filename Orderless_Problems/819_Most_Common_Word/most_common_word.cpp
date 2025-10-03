/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    819) Most Common Word
    ===========================

    ============
    Description:
    ============


    Given a string paragraph and a string array of the banned words banned,
    return the most frequent word that is not banned. It is guaranteed there is
    at least one word that is not banned, and that the answer is unique.

    The words in paragraph are case-insensitive and the answer should be
    returned in lowercase.

    =====
    Note: that words can not contain punctuation symbols.
    =====

    ==========================================================================
    FUNCTION: string mostCommonWord(string paragraph, vector<string>& banned);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
    Output: "ball"
    Explanation:
    "hit" occurs 3 times, but it is a banned word.
    "ball" occurs twice (and no other word does), so it is the most frequent
    non-banned word in the paragraph.
    Note that words in the paragraph are not case sensitive,
    that punctuation is ignored (even if adjacent to words, such as "ball,"),
    and that "hit" isn't the answer even though it occurs more because it is banned.


    --- Example 2 ---
    Input: paragraph = "a.", banned = []
    Output: "a"


    *** Constraints ***
    1 <= paragraph.length <= 1000
    paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
    0 <= banned.length <= 100
    1 <= banned[i].length <= 10
    banned[i] consists of only lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned)
    {
        const int N = paragraph.length();

        string result_str = "";
        int max_frequency = 0;

        unordered_set<string> uset_banned(banned.begin(), banned.end());
        unordered_map<string, int> frequency_map; // Unordered

        // Replace all delimiters with spaces
        for (char& chr : paragraph)
        {
            // if (chr == '!'  || chr == '?'  || chr == '\'' || chr == ','  || chr == ';'  || chr == '\"')
            //     chr = ' ';

            if ( ! isalpha(chr))
                chr = ' ';
        }

        istringstream iss(paragraph);
        string word;

        while (iss >> word)
        {
            // Convert word to lowercase word
            for (char& chr : word)
            {
                chr = static_cast<char>(tolower(static_cast<unsigned char>(chr)));
            }

            if ( ! uset_banned.count(word)) // If it's NOT banned
            {
                frequency_map[word]++;

                if (max_frequency < frequency_map[word])
                {
                    max_frequency = frequency_map[word];
                    result_str    = word;
                }
            }
        }

        return result_str;
    }
};
