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
#include <unordered_map>
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

        map<int,int> map_freq;
        for (const int& card_value : hand)
            map_freq[card_value]++;

        while ( ! map_freq.empty())
        {
            auto lowest_card = map_freq.begin();

            int start_card = lowest_card->first;
            lowest_card->second--;

            if (lowest_card->second == 0)
                map_freq.erase(lowest_card->first);

            int next_card = start_card+1;
            for (int i = 1; i < groupSize; i++)
            {
                if (map_freq.find(next_card) == map_freq.end())// DOESN'T exist
                    return false;

                map_freq[next_card]--;
                if (map_freq[next_card] == 0)
                    map_freq.erase(next_card);

                next_card++;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.67% */
/* Space Beats: 79.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Greedy {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize)
    {
        const int N = hand.size();

        if (N % groupSize != 0)
            return false;

        // Map to store the count of each card value
        unordered_map<int, int> freq;
        for (const int& card_value : hand)
            freq[card_value]++;

        for (const int& card_value : hand)
        {
            int start_card = card_value;

            // Find the start of a potential straight sequence
            while (freq[start_card - 1])
                start_card--;

            // Process sequences starting from every start_card <= card_value
            while (start_card <= card_value)
            {
                // There can be multiple sequences that start on the same
                // start_card
                while (freq[start_card] > 0)
                {
                    int next_card = start_card;
                    while (next_card < start_card + groupSize)
                    {
                        if (freq[next_card] == 0) // next_card does NOT exist
                            return false;

                        freq[next_card]--;

                        // Increment
                        next_card++;
                    }
                }

                start_card++;
            }
        }

        return true;
    }
};
