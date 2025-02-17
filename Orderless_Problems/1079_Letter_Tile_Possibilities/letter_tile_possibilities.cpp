/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    1079) Letter Tile Possibilities
    ===============================

    ============
    Description:
    ============

    You have n  tiles, where each tile has one letter tiles[i] printed on it.

    Return the number of possible non-empty sequences of letters you can make
    using the letters printed on those tiles.

    =================================================
    FUNCTION: int numTilePossibilities(string tiles);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tiles = "AAB"
    Output: 8
    Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
                                            "ABA", "BAA".

    --- Example 2 ---
    Input: tiles = "AAABBC"
    Output: 188

    --- Example 3 ---
    Input: tiles = "V"
    Output: 1


    *** Constraints ***
    1 <= tiles.length <= 7
    tiles consists of uppercase English letters.

*/

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

/* Time  Beats: 33.33% */
/* Space Beats: 30.04% */

/* Time  Complexity: O(n * n!) */
/* Space Complexity: O(n * n!) */
class Solution {
public:
    int numTilePossibilities(string tiles)
    {
        unordered_set<string> sequences;
        vector<bool> used(tiles.length(), false);

        // Generate all possible sequences including empty string
        generate_sequences(tiles, "", used, sequences);

        // Subtract 1 to exclude empty string from count
        return sequences.size() - 1;
    }

private:
    void generate_sequences(string& tiles,
                            string current,
                            vector<bool>& used,
                            unordered_set<string>& sequences)
    {
        sequences.insert(current);

        for (int i = 0; i < tiles.length(); ++i)
        {
            if ( ! used[i])
            {
                used[i] = true;
                generate_sequences(tiles, current + tiles[i], used, sequences);
                used[i] = false;
            }
        }
    }
};
