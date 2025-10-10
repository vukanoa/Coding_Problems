/*
    ============
    === EASY ===
    ============

    ==============================
    1078) Occurrences After Bigram
    ==============================

    ============
    Description:
    ============

    Given two strings first and second, consider occurrences in some text of
    the form "first second third", where second comes immediately after first,
    and third comes immediately after second.

    Return an array of all the words third for each occurrence of "first second
    third".

    ==================================================================================
    FUNCTION: vector<string> findOcurrences(string text, string first, string second);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: text = "alice is a good girl she is a good student", first = "a",
           second = "good"
    Output: ["girl","student"]

    --- Example 2 ---
    Input: text = "we will we will rock you", first = "we", second = "will"
    Output: ["we","rock"]


    *** Constraints ***
    1 <= text.length <= 1000
    text consists of lowercase English letters and spaces.
    All the words in text are separated by a single space.
    1 <= first.length, second.length <= 10
    first and second consist of lowercase English letters.
    text will not have any leading or trailing spaces.

*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second)
    {
        vector<string> result;


        istringstream iss(text);
        string word;

        vector<string> words_in_order;
        while (iss >> word)
            words_in_order.push_back(word);

        for (unsigned i = 2; i < words_in_order.size(); i++)
        {
            if (words_in_order[i-2] == first && words_in_order[i-1] == second)
                result.push_back(words_in_order[i]);
        }

        return result;
    }
};
