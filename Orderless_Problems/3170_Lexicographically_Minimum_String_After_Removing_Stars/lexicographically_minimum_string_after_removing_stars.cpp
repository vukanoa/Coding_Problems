/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    3170) Lexicographically Minimum String After Removing Stars
    ===========================================================

    ============
    Description:
    ============

    You are given a string s. It may contain any number of '*' characters. Your
    task is to remove all '*' characters.

    While there is a '*', do the following operation:

        Delete the leftmost '*' and the smallest non-'*' character to its left.
        If there are several smallest characters, you can delete any of them.

    Return the lexicographically smallest resulting string after removing all
    '*' characters.

    ======================================
    FUNCTION: string clearStars(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaba*"
    Output: "aab"
    Explanation: We should delete one of the 'a' characters with '*'. If we
                 choose s[3], s becomes the lexicographically smallest.

    --- Example 2 ---
    Input: s = "abc"
    Output: "abc"
    Explanation:
    There is no '*' in the string.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of lowercase English letters and '*'.
    The input is generated such that it is possible to delete all '*' characters

*/

#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 49.84% */
/* Space Beats: 49.84% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string clearStars(string s)
    {
        const int N = s.length();

        auto comparator = [](const pair<int,int>& a, const pair<int,int>& b)
        {
            if (a.first == b.first)
                return a.second < b.second; // Decreasing by the second

            return a.first > b.first; // Increasing by the first
        };

        priority_queue<pair<int,int>,
                       vector<pair<int, int>>,
                       decltype(comparator)> min_heap(comparator);


        for (int i = 0; i < N; i++)
        {
            if (s[i] != '*')
                min_heap.push( {s[i], i} );
            else
                min_heap.pop();
        }


        vector<pair<int,int>> vec;

        while ( ! min_heap.empty())
        {
            char chr = min_heap.top().first;
            int  idx = min_heap.top().second;
            min_heap.pop();

            vec.push_back( {idx, chr} );
        }

        sort(vec.begin(), vec.end());

        string result;
        for (int i = 0; i < vec.size(); i++)
        {
            char chr = vec[i].second;
            result += chr;
        }

        return result;
    }
};
