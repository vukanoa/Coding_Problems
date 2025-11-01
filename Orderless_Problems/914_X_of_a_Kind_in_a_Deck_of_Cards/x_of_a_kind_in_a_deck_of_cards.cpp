/*
    ============
    === EASY ===
    ============

    ===================================
    914) X of a Kind in a Deck of Cards
    ===================================

    ============
    Description:
    ============

    You are given an integer array deck where deck[i] represents the number
    written on the ith card.

    Partition the cards into one or more groups such that:

        + Each group has exactly x cards where x > 1, and
        + All the cards in one group have the same integer written on them.

    Return true if such partition is possible, or false otherwise.

    =================================================
    FUNCTION: bool hasGroupsSizeX(vector<int>& deck);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: deck = [1,2,3,4,4,3,2,1]
    Output: true
    Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].

    --- Example 2 ---
    Input: deck = [1,1,1,2,2,2,3,3]
    Output: false
    Explanation: No possible partition.


    *** Constraints ***
    1 <= deck.length <= 10^4
    0 <= deck[i] < 10^4

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

/* Time  Beats: 100.00% */
/* Space Beats:  21.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck)
    {
        const int N = deck.size();
        if (N == 1)
            return false;

        unordered_map<int,int> freq;
        for (int i = 0; i < N; i++)
            freq[deck[i]]++;

        int curr_gcd = freq.begin()->second;

        auto iter = next(freq.begin());
        while (iter != freq.end())
        {
            curr_gcd = gcd(curr_gcd, iter->second);
            iter++;
        }

        return curr_gcd > 1;
    }

private:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};
