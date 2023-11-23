#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1007) Minimum Domino Rotations For Equal Row
    ============================================

    ============
    Description:
    ============

    In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom
    halves of the ith domino. (A domino is a tile with two numbers from 1 to 6
    - one on each half of the tile.)

    We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

    Return the minimum number of rotations so that all the values in tops are
    the same, or all the values in bottoms are the same.

    If it cannot be done, return -1.

    ==========================================================================
    FUNCTION: int minDominoRotations(vector<int>& tops, vector<int>& bottoms);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
    Output: 2
    Explanation: The first figure represents the dominoes as given by tops and
    bottoms: before we do any rotations.  If we rotate the second and fourth
    dominoes, we can make every value in the top row equal to 2, as indicated
    by the second figure.


    --- Example 2 ---
    Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
    Output: -1
    Explanation:
    In this case, it is not possible to rotate the dominoes to make one row of values equal.


    *** Constraints ***
    2 <= tops.length <= 2 * 10^4
    bottoms.length == tops.length
    1 <= tops[i], bottoms[i] <= 6

*/

/* Time  Beats: 44.29% */
/* Space Beats: 5.79% */
class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms)
    {
        std::unordered_map<int, int> map_tops;
        std::unordered_map<int, int> map_bots;

        /* Step 1: Store frequence of all elements in map */

        // O(N)
        for (int& num : tops)
            map_tops[num]++;

        // O(N)
        for (int& num : bottoms)
            map_bots[num]++;


        /* Step 2: Bucket Sort's first step */
        // O(N)
        int max_freq_top = 0;
        std::vector<std::vector<int>> freq_top(tops.size() + 1);
        for (const auto& it: map_tops)
        {
            if (it.second > max_freq_top)
                max_freq_top = it.second;

            freq_top[it.second].push_back(it.first);
        }

        // O(N)
        int max_freq_bot = 0;
        std::vector<std::vector<int>> freq_bot(tops.size() + 1);
        for (const auto& it: map_bots)
        {
            if (it.second > max_freq_bot)
                max_freq_bot = it.second;

            freq_bot[it.second].push_back(it.first);
        }

        // Finish
        int swaps = (max_freq_top >= max_freq_bot) ? fun(tops,    bottoms, freq_top, max_freq_top)
                                                   : fun(bottoms, tops,    freq_bot, max_freq_bot);

        if (swaps != -1)
            return swaps;

        return (max_freq_top < max_freq_bot) ? fun(tops,    bottoms, freq_top, max_freq_top)
                                             : fun(bottoms, tops,    freq_bot, max_freq_bot);
    }

private:
    int fun(std::vector<int>& tops, std::vector<int>& bottoms, std::vector<std::vector<int>>& freq, int max_freq)
    {
        for (int i = 0; i < freq[max_freq].size(); i++)
        {
            int curr_non_swap = freq[max_freq][i];

            int swapped = 0;
            for (int j = 0; j < tops.size(); j++)
            {
                if (tops[j] == curr_non_swap)
                    continue;

                if (bottoms[j] == curr_non_swap)
                    swapped++;
                else
                    break;
            }

            if (swapped == tops.size() - max_freq)
                return swapped;
        }

        return -1;
    }
};




/* Time  Beats: 15.18% */
/* Space Beats: 83.72% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms)
    {
        int result = INT_MAX;

        for(int i = 1; i <= 6; i++)
        {
            bool is_top_row_all_equal_possible    = true;
            bool is_bottom_row_all_equal_possible = true;

            int swaps_in_top    = 0;
            int swaps_in_bottom = 0;

            for(int j = 0; j < tops.size(); j++)
            {
                if(tops[j] == i);
                else if(bottoms[j] == i)
                    swaps_in_top++;
                else
                    is_top_row_all_equal_possible = false;

                if(bottoms[j] == i);
                else if(tops[j] == i)
                    swaps_in_bottom++;
                else
                    is_bottom_row_all_equal_possible = false;
            }

            if(is_top_row_all_equal_possible)
                result = std::min(result, swaps_in_top);

            if(is_bottom_row_all_equal_possible)
                result = std::min(result, swaps_in_bottom);
        }

        return result == INT_MAX ? -1 : result;
    }
};
