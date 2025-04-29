/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    3527) Find the Most Common Response
    ===================================

    ============
    Description:
    ============

    You are given a 2D string array responses where each responses[i] is an
    array of strings representing survey responses from the ith day.

    Return the most common response across all days after removing duplicate
    responses within each responses[i]. If there is a tie, return the
    lexicographically smallest response.

    =======================================================================
    FUNCTION: string findCommonResponse(vector<vector<string>>& responses);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: responses = [["good","ok","good","ok"],
                        ["ok","bad","good","ok","ok"],
                        ["good"],
                        ["bad"]]
    Output: "good"
    Explanation:
        + After removing duplicates within each list,
          responses=[["good", "ok"], ["ok", "bad", "good"], ["good"], ["bad"]]

        + "good" appears 3 times, "ok" appears 2 times, and "bad" appears 2
          times

        + Return "good" because it has the highest frequency.


    --- Example 2 ---
    Input: responses = [["good","ok","good"],
                        ["ok","bad"],
                        ["bad","notsure"],
                        ["great","good"]]
    Output: "bad"
    Explanation:
        + After removing duplicates within each list we have
          responses = [["good", "ok"],
                       ["ok", "bad"],
                       ["bad", "notsure"],
                       ["great", "good"]].

        + "bad", "good", and "ok" each occur 2 times.

        + The output is "bad" because it is the lexicographically smallest
          amongst the words with the highest frequency.



    *** Constraints ***
    1 <= responses.length <= 1000
    1 <= responses[i].length <= 1000
    1 <= responses[i][j].length <= 10
    responses[i][j] consists of only lowercase English letter

*/

#include <algorithm>
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

/* Time  Beats: 51.71% */
/* Space Beats: 52.62% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N) */
class Solution {
public:
    string findCommonResponse(vector<vector<string>>& responses)
    {
        const int N = responses.size();

        vector<unordered_set<string>> vec(N);
        vector<string> freq;

        for (int i = 0; i < N; i++)
        {
            for (const auto& str : responses[i])
                vec[i].insert(str);
        }

        unordered_map<string, int> counter;

        for (int i = 0; i < N; i++)
        {
            for (const auto& str : vec[i])
                counter[str]++;
        }

        int maxx = 0;
        for (const auto& entry : counter)
            maxx = max(maxx, entry.second);

        for (const auto& entry : counter)
        {
            if (entry.second == maxx)
                freq.push_back(entry.first);
        }

        sort(freq.begin(), freq.end());

        return freq[0];
    }
};
