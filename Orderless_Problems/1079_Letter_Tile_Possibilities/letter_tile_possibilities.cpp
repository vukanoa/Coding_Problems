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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(n!) */
/* Space Complexity: O(n)  */
class Solution_Optimized_Recursion {
public:
    int numTilePossibilities(string tiles)
    {
        // Track frequency of each uppercase letter (A-Z)
        int counter[26] = {0};

        for (char c : tiles)
            counter[c - 'A']++;

        return find_sequences(counter);
    }

private:
    int find_sequences(int counter[26])
    {
        int total_count = 0;

        for (int i = 0; i < 26; i++)
        {
            if (counter[i] == 0)
                continue;

            total_count++;

            counter[i]--;
            total_count += find_sequences(counter);
            counter[i]++;
        }

        return total_count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.62% */
/* Space Beats: 53.96% */

/* Time  Complexity: O(2^n * n) */
/* Space Complexity: O(2^n * n) */
class Solution_Permutations_Combinations {
public:
    int numTilePossibilities(string tiles)
    {
        unordered_set<string> seen;

        sort(tiles.begin(), tiles.end());

        return generate_sequences(tiles, "", 0, seen) - 1;
    }

private:
    int factorial(int n)
    {
        if (n <= 1)
            return 1;

        int result = 1;
        for (int num = 2; num <= n; num++)
            result *= num;

        return result;
    }

    int count_permutations(string& seq)
    {
        int counter[26] = {0};
        for (char ch : seq)
            counter[ch - 'A']++;

        // Calculate permutations using factorial formula
        int total = factorial(seq.length());
        for (int count : counter)
        {
            if (count > 1)
                total /= factorial(count);
        }

        return total;
    }

    int generate_sequences(string& tiles,
                           string current,
                           int pos,
                           unordered_set<string>& seen)
    {
        if (pos >= tiles.length())
        {
            if (seen.insert(current).second)
                return count_permutations(current);

            return 0;
        }

        // Try including and excluding current character
        return generate_sequences(tiles, current             , pos + 1, seen) +
               generate_sequences(tiles, current + tiles[pos], pos + 1, seen);
    }
};
