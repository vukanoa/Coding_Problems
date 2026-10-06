/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3799) Word Squares II
    ===========================

    ============
    Description:
    ============

    You are given a string array words, consisting of distinct 4-letter
    strings, each containing lowercase English letters.

    A word square consists of 4 distinct words: top, left, right and bottom,
    arranged as follows:

        + top forms the top row.
        + bottom forms the bottom row.
        + left forms the left column (top to bottom).
        + right forms the right column (top to bottom).

    It must satisfy:

        + top[0]    == left[0], top[3]    == right[0]
        + bottom[0] == left[3], bottom[3] == right[3]

    Return all valid distinct word squares, sorted in ascending lexicographic
    order by the 4-tuple (top, left, right, bottom)

    ====================================================================
    FUNCTION: vector<vector<string>> wordSquares(vector<string>& words);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["able","area","echo","also"]
    Output: [["able","area","echo","also"],["area","able","also","echo"]]
    Explanation:
    There are exactly two valid 4-word squares that satisfy all corner
    constraints:
        "able" (top), "area" (left), "echo" (right), "also" (bottom)
            top[0] == left[0] == 'a'
            top[3] == right[0] == 'e'
            bottom[0] == left[3] == 'a'
            bottom[3] == right[3] == 'o'
        "area" (top), "able" (left), "also" (right), "echo" (bottom)
            All corner constraints are satisfied.

    Thus, the answer is
    [["able","area","echo","also"],["area","able","also","echo"]].


    --- Example 2 ---
    Input: words = ["code","cafe","eden","edge"]
    Output: []
    Explanation:
    No combination of four words satisfies all four corner constraints. Thus,
    the answer is empty array [].


    *** Constraints ***
    4 <= words.length <= 15
    words[i].length == 4
    words[i] consists of only lowercase English letters.
    All words[i] are distinct.

*/

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.55% */
/* Space Beats: 16.95% */

/* Time  Complexity: O(N^4) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words)
    {
        const int N = words.size();
        vector<vector<string>> result;

        vector<tuple<string,string,string,string>> combinations;
        unordered_set<string> used;
        
        for (int i = 0; i < N; i++)
        {
            string top = words[i];
            used.insert(top);

            for (int j = 0; j < N; j++)
            {
                if (used.count(words[j]))
                    continue;

                if (top[0] != words[j][0])
                    continue;

                string left = words[j];
                used.insert(left);

                for (int k = 0; k < N; k++)
                {
                    if (used.count(words[k]))
                        continue;

                    if (top[3] != words[k][0])
                        continue;

                    string right = words[k];
                    used.insert(right);

                    for (int l = 0; l < N; l++)
                    {
                        if (used.count(words[l]))
                            continue;

                        if (left[3] != words[l][0] || right[3] != words[l][3])
                            continue;

                        string bottom = words[l];

                        combinations.push_back( {top, left, right, bottom} );
                    }

                    used.erase(right);
                }

                used.erase(left);
            }

            used.erase(top);
        }

        /* Sort */
        sort(combinations.begin(), combinations.end());

        for (const auto& [top, left, right, bottom] : combinations)
        {
            result.push_back( {top, left, right, bottom} );
        }

        return result;
    }
};
