/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    846) Hand Of Straights
    ===========================

    ============
    Description:
    ============

    Alice has some number of cards and she wants to rearrange the cards into
    groups so that each group is of size groupSize, and consists of groupSize
    consecutive cards.

    Given an integer array hand where hand[i] is the value written on the ith
    card and an integer groupSize, return true if she can rearrange the cards,
    or false otherwise.

    =================================================================
    FUNCTION: bool isNStraightHand(vector<int>& hand, int groupSize);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
    Output: true
    Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]


    --- Example 2 ---
    Input: hand = [1,2,3,4,5], groupSize = 4
    Output: false
    Explanation: Alice's hand can not be rearranged into groups of 4.


    *** Constraints ***
    1 <= hand.length <= 104
    0 <= hand[i] <= 109
    1 <= groupSize <= hand.length

*/

#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 64.63% */
/* Space Beats: 58.55% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Ordered_Map {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize)
    {
        const int N = hand.size();

        if (N % groupSize != 0)
            return false;

        map<int,int> map;
        for (const int& card : hand)
            map[card]++;

        while ( ! map.empty())
        {
            auto lowest_card = map.begin();

            int card = lowest_card->first;
            lowest_card->second--;

            if (lowest_card->second == 0)
                map.erase(lowest_card->first);

            int next = card+1;
            for (int i = 1; i < groupSize; i++)
            {
                if (map.find(next) == map.end()) // It does NOT exist
                    return false;

                map[next]--;
                if (map[next] == 0)
                    map.erase(next);

                next++;
            }
        }

        return true;
    }
};
