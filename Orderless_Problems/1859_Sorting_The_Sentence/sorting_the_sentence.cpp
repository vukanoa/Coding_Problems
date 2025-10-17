/*
    ============
    === EASY ===
    ============

    ===========================
    1859) Sorting the Sentence
    ===========================

    ============
    Description:
    ============

    A sentence is a list of words that are separated by a single space with no
    leading or trailing spaces. Each word consists of lowercase and uppercase
    English letters.

    A sentence can be shuffled by appending the 1-indexed word position to each
    word then rearranging the words in the sentence.

        + For example, the sentence "This is a sentence" can be shuffled as
          "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".

    Given a shuffled sentence s containing no more than 9 words, reconstruct
    and return the original sentence.

    ========================================
    FUNCTION: string sortSentence(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "is2 sentence4 This1 a3"
    Output: "This is a sentence"
    Explanation: Sort the words in s to their original positions "This1 is2 a3
    sentence4", then remove the numbers.

    --- Example 2 ---
    Input: s = "Myself2 Me1 I4 and3"
    Output: "Me Myself and I"
    Explanation: Sort the words in s to their original positions "Me1 Myself2
    and3 I4", then remove the numbers.

    *** Constraints ***
    2 <= s.length <= 200
    s consists of lowercase and uppercase English letters, spaces, and digits
    from 1 to 9.
    The number of words in s is between 1 and 9.
    The words in s are separated by a single space.
    s contains no leading or trailing spaces.

*/

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.17% */
/* Space Beats:  5.16% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string sortSentence(string s) 
    {
        string result = "";

        stringstream iss(s); 
        string word;

        pair<int, string> pairs;
        vector<pair<int, string> > sent;
        
        while (iss >> word)
        {
            int size = word.size();
            int i = word[size-1] - '0';
            sent.push_back(make_pair(i, word.substr(0, size-1)));
        }
        
        // Sort
        sort(sent.begin(), sent.end());
        
        int len = sent.size();
        for(int i = 0; i < len; i++)
        {
            result += sent[i].second;

            if (i != len-1)
                result += " ";
        }
        
        return result;
    }
};
