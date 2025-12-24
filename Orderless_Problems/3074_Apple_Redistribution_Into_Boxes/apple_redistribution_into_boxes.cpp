/*
    ============
    === EASY ===
    ============

    =====================================
    3074) Apple Redistribution into Boxes
    =====================================

    ============
    Description:
    ============

    You are given an array apple of size n and an array capacity of size m.

    There are n packs where the ith pack contains apple[i] apples. There are m
    boxes as well, and the ith box has a capacity of capacity[i] apples.

    Return the minimum number of boxes you need to select to redistribute these
    n packs of apples into boxes.

    =====
    Note: that, apples from the same pack can be distributed into different
          boxes.
    =====

    ======================================================================
    FUNCTION: int minimumBoxes(vector<int>& apple, vector<int>& capacity);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: apple = [1,3,2], capacity = [4,3,1,5,2]
    Output: 2
    Explanation: We will use boxes with capacities 4 and 5.
    It is possible to distribute the apples as the total capacity is greater
    than or equal to the total number of apples.

    --- Example 2 ---
    Input: apple = [5,5,5], capacity = [2,4,2,7]
    Output: 4
    Explanation: We will need to use all the boxes.

    *** Constraints ***
    1 <= n == apple.length <= 50
    1 <= m == capacity.length <= 50
    1 <= apple[i], capacity[i] <= 50
    The input is generated such that it's possible to redistribute packs of
    apples into boxes.

*/

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.29% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Log because Introsort's TC
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity)
    {
        const int N = apple.size();
        const int M = capacity.size();

        int result = 0;

        /* Sort in DECREASING order */
        sort(capacity.begin(), capacity.end(), greater<int>());

        int apples = accumulate(apple.begin(), apple.end(), 0);
        int curr_capacity = 0;

        if (curr_capacity >= apples)
            return result;

        for (int i = 0; i < M; i++)
        {
            curr_capacity += capacity[i];
            result++;

            if (curr_capacity >= apples)
                return result;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Counting Sort.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.48% */

/* Time  Complexity: O(N + C) */ // Where 'C' is 50
/* Space Complexity: O(C)     */
class Solution_Counting_Sort {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity)
    {
        int N = capacity.size();

        int remaining_apples = accumulate(apple.begin(), apple.end(), 0);

        // Frequency table for capacities (constraints guarantee max <= 50)
        uint8_t capacity_freq[51] = {0};

        int max_capacity_value = 0;
        for (const int& curr_capacity : capacity)
        {
            capacity_freq[curr_capacity]++;
            max_capacity_value = max(max_capacity_value, curr_capacity);
        }

        int used_box_count = 0;

        for (int curr_capacity = max_capacity_value; curr_capacity > 0; curr_capacity--)
        {
            int available_boxes = capacity_freq[curr_capacity];
            if (available_boxes == 0)
                continue;

            int total_capacity_here = curr_capacity * available_boxes;

            if (total_capacity_here < remaining_apples)
            {
                remaining_apples -= total_capacity_here;
                used_box_count += available_boxes;
            }
            else
            {
                int required_boxes = (remaining_apples + curr_capacity - 1) / curr_capacity;
                return used_box_count + required_boxes;
            }
        }

        return -1;
    }
};
