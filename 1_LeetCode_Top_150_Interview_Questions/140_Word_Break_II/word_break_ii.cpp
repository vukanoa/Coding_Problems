/*
    ============
    === HARD ===
    ============

    ===========================
    140) Word Break II
    ===========================

    ============
    Description:
    ============

    Given a string s and a dictionary of strings wordDict, add spaces in s to
    construct a sentence where each word is a valid dictionary word. Return all
    such possible sentences in any order.

    =====
    Node: that the same word in the dictionary may be reused multiple times in
          the segmentation.
    =====

    =======================================================================
    FUNCTION: vector<string> wordBreak(string s, vector<string>& wordDict);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "catsanddog",
           wordDict = ["cat","cats","and","sand","dog"]

    Output: ["cats and dog","cat sand dog"]




    --- Example 2 ---
    Input: s = "pineapplepenapple",
           wordDict = ["apple","pen","applepen","pine","pineapple"]

    Output:["pine apple pen apple","pineapple pen apple","pine applepen apple"]

    Explanation: Note that you are allowed to reuse a dictionary word.




    --- Example 3 ---
    Input: s = "catsandog",
           wordDict = ["cats","dog","sand","and","cat"]

    Output: []



    *** Constraints ***
    1 <= s.length <= 20
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 10
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.
    Input is generated in a way that the length of the answer doesn't exceed 10^5.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's pretty much a standard Bactracking approach. I'm not sure why is this
    a HARD problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.24% */

/* Time  Complexity: O(M + N * 2^N) */
/* Space Complexity: O(M + 2^N)     */
class Solutionxxxx {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict)
    {
        const int N = s.size();

        unordered_set<string> dictionary(wordDict.begin(), wordDict.end());
        vector<string> results;

        string sentence;
        backtracking(0, sentence, results, s, dictionary);

        return results;
    }
private:
    void backtracking(int start, string sentence, vector<string>& results, string s, unordered_set<string>& dictionary)
    {
        const int N = s.size();

        if (start >= N)
        {
            sentence.pop_back(); // Pop the <Space>
            results.push_back(sentence);
            return;
        }

        string word;
        word.reserve(N); // To prevent reallocations
        for (int i = start; i < N; i++)
        {
            word += s[i];

            if (dictionary.count(word))
            {
                sentence += word;
                sentence += " ";

                backtracking(i + 1, sentence, results, s, dictionary);

                sentence.pop_back(); // Pop the <Space>
                int word_size = word.size();
                while (word_size-- > 0)
                    sentence.pop_back();
            }
        }
    }
};
