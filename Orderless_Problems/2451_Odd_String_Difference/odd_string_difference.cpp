/*
    ============
    === EASY ===
    ============

    ===========================
    2451) Odd String Difference
    ===========================

    ============
    Description:
    ============

    You are given an array of equal-length strings words. Assume that the
    length of each string is n.

    Each string words[i] can be converted into a difference integer array
    difference[i] of length n - 1 where
    difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2.

    Note that the difference between two letters is the difference between
    their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1,
    and 'z' is 25.

        + For example, for the string "acb", the difference integer array is
          [2 - 0, 1 - 2] = [2, -1].

    All the strings in words have the same difference integer array, except
    one. You should find that string.

    Return the string in words that has different difference integer array.

    ==================================================
    FUNCTION: string oddString(vector<string>& words);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["adc","wzy","abc"]
    Output: "abc"
    Explanation:
    - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
    - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
    - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1].
    The odd array out is [1, 1], so we return the corresponding string, "abc".

    --- Example 2 ---
    Input: words = ["aaa","bob","ccc","ddd"]
    Output: "bob"
    Explanation: All the integer arrays are [0, 0] except for "bob", which
                 corresponds to [13, -13].


    *** Constraints ***
    3 <= words.length <= 100
    n == words[i].length
    2 <= n <= 20
    words[i] consists of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 80.60% */

/* Time  Complexity: O(SIZE * N) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string oddString(vector<string>& words)
    {
        const int SIZE = words.size();
        const int N    = words[0].length();

        vector<int> one(N-1, 0);
        vector<int> two(N-1, 0);
        for (int j = 0; j < N-1; j++)
        {
            one[j] = words[0][j+1] - words[0][j];
            two[j] = words[1][j+1] - words[1][j];
        }

        if (one != two)
        {
            vector<int> three(N-1, 0);
            for (int j = 0; j < N-1; j++)
                three[j] = words[2][j+1] - words[2][j];

            return one == three ? words[1] : words[0];
        }

        for (int i = 2; i < SIZE; i++)
        {
            vector<int> curr(N-1, 0);

            for (int j = 0; j < N-1; j++)
                curr[j] = words[i][j+1] - words[i][j];

            if (one != curr)
                return words[i];
        }

        return ""; // Unreachable code
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 80.60% */

/* Time  Complexity: O(SIZE * N) */
/* Space Complexity: O(N)        */
class Solution_2 {
public:
    string oddString(vector<string>& words)
    {
        const int N = words[0].length();

        for (int j = 0; j < N-1; j++)
        {
            unordered_map<int, vector<int>> umap;

            for (int i = 0; i < words.size(); i++)
                umap[words[i][j + 1] - words[i][j]].push_back(i);

            if (umap.size() == 2)
                return words[begin(umap)->second.size() == 1 ? begin(umap)->second.back() : next(begin(umap))->second.back()];
        }

        return words[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.39% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Constant_Space {
public:
    string oddString(vector<string>& words)
    {
        const int SIZE = words.size();
        int matching_first = 0;
        int mismatch_idx   = 0;

        for (int i = 1; i < SIZE; i++)
        {
            if (matches_diff(words[0], words[i]))
                matching_first++;
            else
                mismatch_idx = i;
        }

        return matching_first > 0 ? words[mismatch_idx] : words[0];
    }

private:
    bool matches_diff(string& a, string& b)
    {
        const int N = a.length();

        for (size_t i = 0; i < N - 1; i++)
        {
            if (a[i + 1] - a[i] != b[i + 1] - b[i])
                return false;
        }

        return true;
    }
};
