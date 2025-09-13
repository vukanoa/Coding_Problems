/*
    ============
    === EASY ===
    ============

    ===========================
    2103) Rings and Rod
    ===========================

    ============
    Description:
    ============

    There are n rings and each ring is either red, green, or blue. The rings
    are distributed across ten rods labeled from 0 to 9.

    You are given a string rings of length 2n that describes the n rings that
    are placed onto the rods. Every two characters in rings forms a
    color-position pair that is used to describe each ring where:

        + The first character of the ith pair denotes the ith ring's color
          ('R', 'G', 'B').

        + The second character of the ith pair denotes the rod that the ith
          ring is placed on ('0' to '9').

    For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the
    rod labeled 3, a green ring placed onto the rod labeled 2, and a blue ring
    placed onto the rod labeled 1.

    Return the number of rods that have all three colors of rings on them.

    ========================================
    FUNCTION: int countPoints(string rings);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rings = "B0B6G0R6R0R6G9"
    Output: 1
    Explanation: 
    - The rod labeled 0 holds 3 rings with all colors: red, green, and blue.
    - The rod labeled 6 holds 3 rings, but it only has red and blue.
    - The rod labeled 9 holds only a green ring.
    Thus, the number of rods with all three colors is 1.

    --- Example 2 ---
    Input: rings = "B0R0G0R9R0B0G0"
    Output: 1
    Explanation: 
    - The rod labeled 0 holds 6 rings with all colors: red, green, and blue.
    - The rod labeled 9 holds only a red ring.
    Thus, the number of rods with all three colors is 1.

    --- Example 3 ---
    Input: rings = "G4"
    Output: 0
    Explanation: 
    Only one ring is given. Thus, no rods have all three colors.


    *** Constraints ***
    rings.length == 2 * n
    1 <= n <= 100
    rings[i] where i is even is either 'R', 'G', or 'B' (0-indexed).
    rings[i] where i is odd is a digit from '0' to '9' (0-indexed).

*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  26.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countPoints(string rings)
    {
        const int N = rings.length();
        int result = 0;

        unordered_map<int, unordered_set<char>> umap;
        for (int i = 0; i < N; i += 2)
        {
            char color    = rings[i];
            int  ring_idx = rings[i+1];

            umap[ring_idx].insert(color);

        }

        for (const auto& entry : umap)
        {
            if (entry.second.size() == 3)
                result++;
        }

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
/* Space Beats:  46.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bitmask {
public:
    int countPoints(string rings)
    {
        const int N = rings.size();
        int rods[10] = {};

        for (int i = 0; i < N; i += 2)
        {
            // 1 = R, 2 = G, 4 = B
            int color    = rings[i] == 'R' ? 1 : rings[i] == 'G' ? 2 : 4;
            int ring_idx = rings[i+1] - '0';

            rods[ring_idx] |= color;
        }

        return count(begin(rods), end(rods), 7);
    }
};
