/*
    ============
    === EASY ===
    ============

    =================================
    1408) String Matching in an Array
    =================================

    ============
    Description:
    ============

    Given an array of string words, return all strings in words that is a
    substring of another word. You can return the answer in any order.

    A substring is a contiguous sequence of characters within a string

    ===============================================================
    FUNCTION: vector<string> stringMatching(vector<string>& words);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["mass","as","hero","superhero"]
    Output: ["as","hero"]
    Explanation: "as" is substring of "mass" and "hero" is substring of
    "superhero". ["hero","as"] is also a valid answer.


    --- Example 2 ---
    Input: words = ["leetcode","et","code"]
    Output: ["et","code"]
    Explanation: "et", "code" are substring of "leetcode".


    --- Example 3 ---
    Input: words = ["blue","green","bu"]
    Output: []
    Explanation: No string of words is substring of another string.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 30
    words[i] contains only lowercase English letters.
    All the strings of words are unique.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Instead of writing it manually, it's very very handy to know to check, in
    O(n), if some variable "potential_substr" is a substr of another variable
    "word".

    You can do it this way:

        if (word.find(potential_substr) != string::npos)
            uset_result.insert(potential_substr);

    If we were to write our own comparison it would take us O(L^2), where L is
    the average length of the word in "words".

    Using the std::find it's O(L).

    However, we could have this same exact Time Complexity, namely O(N^2 * L)
    but write it ourselves.

    Underneath this "std::find" fuction is an algorithm called:
    Boyer-Moore or Boyer-Moore-Horspool.

    It's used for longer patterns due to its efficiency with skip-based
    searching.

    However, Rabin-Karp is also an efficient way to solve this problem.

*/

/* Time  Beats: 21.77% */
/* Space Beats: 17.90% */

/* Time  Complexity: O(n^2 * L) */ // 'L' is the average length of word
/* Space Complexity: O(n * L)   */
class Solution {
public:
    vector<string> stringMatching(vector<string>& words)
    {
        const int N = words.size();
        unordered_set<string> uset_result;

        for (const string potential_substr : words)
        {
            for (const string word : words)
            {
                if (potential_substr == word)
                    continue;

                if (word.find(potential_substr) != string::npos)
                    uset_result.insert(potential_substr);
            }
        }

        vector<string> result(uset_result.begin(), uset_result.end());
        return result;
    }
};
