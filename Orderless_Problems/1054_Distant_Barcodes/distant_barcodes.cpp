/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1054) Distant Barcodes
    ===========================

    ============
    Description:
    ============

    In a warehouse, there is a row of barcodes, where the ith barcode is
    barcodes[i].

    Rearrange the barcodes so that no two adjacent barcodes are equal. You may
    return any answer, and it is guaranteed an answer exists.

    ===============================================================
    FUNCTION: vector<int> rearrangeBarcodes(vector<int>& barcodes);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: barcodes = [1,1,1,2,2,2]
    Output: [2,1,2,1,2,1]

    --- Example 2 ---
    Input: barcodes = [1,1,1,1,2,2,3,3]
    Output: [1,3,1,3,1,2,1,2]


    *** Constraints ***
    1 <= barcodes.length <= 10000
    1 <= barcodes[i] <= 10000

*/

#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 69.54% */
/* Space Beats: 13.87% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes)
    {
        const int N = barcodes.size();

        unordered_map<int, int> freq;
        set<pair<int, int>> set;
        int position = 0;

        for (const auto& b : barcodes)
            freq[b]++;

        for (const auto& entry : freq)
            set.insert( {entry.second, entry.first} );

        for (auto it = set.rbegin(); it != set.rend(); it++)
        {
            for (int count = 0; count < it->first; count++)
            {
                if (position >= N)
                    position = 1;

                barcodes[position] = it->second;

                position += 2;
            }
        }

        return barcodes;
    }
};
