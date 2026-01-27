/*
    ============
    === EASY ===
    ============

    ===========================
    2347) Best Poker Hand
    ===========================

    ============
    Description:
    ============

    You are given an integer array ranks and a character array suits. You have
    5 cards where the ith card has a rank of ranks[i] and a suit of suits[i].

    The following are the types of poker hands you can make from best to worst:

        1. "Flush": Five cards of the same suit.
        2. "Three of a Kind": Three cards of the same rank.
        3. "Pair": Two cards of the same rank.
        4. "High Card": Any single card.

    Return a string representing the best type of poker hand you can make with
    the given cards.

    =====
    Note: that the return values are case-sensitive.
    =====

    ===================================================================
    FUNCTION: string bestHand(vector<int>& ranks, vector<char>& suits);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
    Output: "Flush"
    Explanation: The hand with all the cards consists of 5 cards with the same
                 suit, so we have a "Flush".

    --- Example 2 ---
    Input: ranks = [4,4,2,4,4], suits = ["d","a","a","b","c"]
    Output: "Three of a Kind"
    Explanation: The hand with the first, second, and fourth card consists of 3
                 cards with the same rank, so we have a "Three of a Kind". Note
                 that we could also make a "Pair" hand but "Three of a Kind" is
                 a better hand. Also note that other cards could be used to
                 make the "Three of a Kind" hand.

    --- Example 3 ---
    Input: ranks = [10,10,2,12,9], suits = ["a","b","c","a","d"]
    Output: "Pair"
    Explanation: The hand with the first and second card consists of 2 cards
                 with the same rank, so we have a "Pair". Note that we cannot
                 make a "Flush" or a "Three of a Kind".


    *** Constraints ***
    ranks.length == suits.length == 5
    1 <= ranks[i] <= 13
    'a' <= suits[i] <= 'd'
    No two cards have the same rank and suit.

*/

using namespace std;

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation Problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.90% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits)
    {
        // Check for Flush (all suits same)
        if (all_of(suits.begin(), suits.end(), [&](char chr) { return chr == suits[0]; }))
            return "Flush";
        
        unordered_map<int, int> freq;
        int max_count = 0;
        for (const int& rank : ranks)
        {
            freq[rank]++;
            max_count = max(max_count, freq[rank]);
        }
        
        if (max_count >= 3)
            return "Three of a Kind";

        if (max_count == 2)
            return "Pair";

        return "High Card";
    }
};
