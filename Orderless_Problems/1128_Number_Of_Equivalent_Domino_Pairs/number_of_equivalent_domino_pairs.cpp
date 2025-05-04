/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    1128) Number of Equivalent Domino Pairs
    =======================================

    ============
    Description:
    ============

    Given a list of dominoes, dominoes[i] = [a, b] is equivalent to
    dominoes[j] = [c, d] if and only if either (a == c and b == d), or
    (a == d and b == c) - that is, one domino can be rotated to be equal to
    another domino.

    Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length,
    and dominoes[i] is equivalent to dominoes[j].

    =================================================================
    FUNCTION: int numEquivDominoPairs(vector<vector<int>>& dominoes);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
    Output: 1

    --- Example 2 ---
    Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
    Output: 3


    *** Constraints ***
    1 <= dominoes.length <= 4 * 10%4
    dominoes[i].length == 2
    1 <= dominoes[i][j] <= 9

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

/* Time  Beats: 41.75% */
/* Space Beats: 26.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes)
    {
        const int N = dominoes.size();
        int result = 0;

        unordered_map<string, int> umap;

        for (int i = 0; i < N; i++)
        {
            if (dominoes[i][0] > dominoes[i][1])
                swap(dominoes[i][0], dominoes[i][1]);

            string str;
            str += to_string(dominoes[i][0]);
            str += to_string(dominoes[i][1]);

            umap[str]++;
        }

        for (const auto& entry : umap)
            result += (entry.second * (entry.second - 1) / 2);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes)
    {
        int result = 0;

        vector<int> counter(100, 0);
        for (auto& d : dominoes)
        {
            int val = (d[0] < d[1]) ? d[0] * 10 + d[1] : d[1] * 10 + d[0];

            result += counter[val];
            counter[val]++;
        }

        return result;
    }
};
