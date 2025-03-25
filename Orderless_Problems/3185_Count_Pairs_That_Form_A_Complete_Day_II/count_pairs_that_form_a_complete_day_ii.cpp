/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3185) Count Pairs That Form a Complete Day II
    =============================================

    ============
    Description:
    ============

    Given an integer array hours representing times in hours, return an integer
    denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms
    a complete day.

    A complete day is defined as a time duration that is an exact multiple of
    24 hours.

    For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and
    so on.

    ==============================================================
    FUNCTION: long long countCompleteDayPairs(vector<int>& hours);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hours = [12,12,30,24,24]
    Output: 2
    Explanation: The pairs of indices that form a complete day are (0, 1) and (3, 4).

    --- Example 2 ---
    Input: hours = [72,48,24,3]
    Output: 3
    Explanation: The pairs of indices that form a complete day are (0, 1), (0, 2), and (1, 2).


    *** Constraints ***
    1 <= hours.length <= 5 * 10^5
    1 <= hours[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 80.91% */
/* Space Beats: 62.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours)
    {
        const int N = hours.size();
        long long  result = 0;

        unordered_map<int,int> umap_passed;
        for (int i = 0; i < N; i++)
        {
            if (hours[i] % 24 != 0)
                hours[i] %= 24;
        }


        long long divisible_by_days = 0;

        if (hours[0] % 24 != 0)
            umap_passed[hours[0]]++;
        else
            divisible_by_days++;

        for (int i = 1; i < N; i++)
        {
            if (hours[i] % 24 == 0)
                divisible_by_days++;
            else
            {
                int target = 24 - hours[i];

                if (umap_passed.find(target) != umap_passed.end())
                    result += umap_passed[target];

                umap_passed[hours[i]]++;
            }
        }

        long long  n = divisible_by_days - 1;
        result += n * (n + 1) / 2;

        return result;
    }
};
