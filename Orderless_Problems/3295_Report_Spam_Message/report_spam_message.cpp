/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3295) Report Spam Message
    ===========================

    ============
    Description:
    ============

    You are given an array of strings message and an array of strings
    bannedWords.

    An array of words is considered spam if there are at least two words in it
    that exactly match any word in bannedWords.

    Return true if the array message is spam, and false otherwise.

    ================================================================================
    FUNCTION: bool reportSpam(vector<string>& message, vector<string>& bannedWords);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: message = ["hello","world","leetcode"], bannedWords = ["world","hello"]
    Output: true
    Explanation: The words "hello" and "world" from the message array both
                 appear in the bannedWords array.

    --- Example 2 ---
    Input: message = ["hello","programming","fun"], bannedWords = ["world","programming","leetcode"]
    Output: false
    Explanation: Only one word from the message array ("programming")
                 appears in the bannedWords array.


    *** Constraints ***
    1 <= message.length, bannedWords.length <= 10^5
    1 <= message[i].length, bannedWords[i].length <= 15
    message[i] and bannedWords[i] consist only of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 36.73% */
/* Space Beats: 19.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords)
    {
        const int N = message.size();
        const int M = bannedWords.size();

        unordered_map<string, int> umap_message;
        for (int i = 0; i < N; i++)
            umap_message[message[i]]++;

        unordered_set<string> uset_bannedWords(bannedWords.begin(), bannedWords.end());

        int count = 0;
        for (const string banned : uset_bannedWords)
        {
            if (umap_message.count(banned))
                count += umap_message[banned];

            if (count >= 2)
                return true;
        }


        return false;
    }
};
