/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    3572) Maximize Y‑Sum by Picking a Triplet of Distinct X‑Values
    ==============================================================

    ============
    Description:
    ============

    You are given two integer arrays x and y, each of length n. You must choose
    three distinct indices i, j, and k such that:

        x[i] != x[j]
        x[j] != x[k]
        x[k] != x[i]

    Your goal is to maximize the value of y[i] + y[j] + y[k] under these
    conditions. Return the maximum possible sum that can be obtained by
    choosing such a triplet of indices.

    If no such triplet exists, return -1.

    ====================================================================
    FUNCTION: int maxSumDistinctTriplet(vector<int>& x, vector<int>& y);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = [1,2,1,3,2], y = [5,3,4,6,2]
    Output: 14
    Explanation:
        Choose i = 0 (x[i] = 1, y[i] = 5), j = 1 (x[j] = 2, y[j] = 3), k = 3
        (x[k] = 3, y[k] = 6). All three values chosen from x are distinct.
        5 + 3 + 6 = 14 is the maximum we can obtain. Hence, the output is 14.

    --- Example 2 ---
    Input: x = [1,2,1,2], y = [4,5,6,7]
    Output: -1
    Explanation:
        There are only two distinct values in x. Hence, the output is -1.


    *** Constraints ***
    n == x.length == y.length
    3 <= n <= 10^5
    1 <= x[i], y[i] <= 10^6

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-expanatory.

*/

/* Time  Beats: 75.82% */
/* Space Beats: 52.35% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y)
    {
        const int N = x.size();
        int result = 0;

        unordered_map<int,int> umap;

        for (int i = 0; i < N; i++)
        {
            if (umap.find(x[i]) != umap.end())
                umap[x[i]] = max(umap[x[i]], y[i]);
            else
                umap[x[i]] = y[i];
        }

        if (umap.size() <= 2)
            return -1;

        vector<int> vec;

        for (const auto& entry : umap)
            vec.push_back(entry.second);

        sort(vec.begin(), vec.end());
        
        result = vec.back();
        vec.pop_back();
        result += vec.back();
        vec.pop_back();
        result += vec.back();

        return result;
    }
};
