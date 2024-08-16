#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    624) Maximum Distance in Arrays
    ===============================

    ============
    Description:
    ============

    You are given m arrays, where each array is sorted in ascending order.

    You can pick up two integers from two different arrays (each array picks
    one) and calculate the distance. We define the distance between two
    integers a and b to be their absolute difference |a - b|.

    Return the maximum distance.

    =======================================================
    FUNCTION: int maxDistance(vector<vector<int>>& arrays);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arrays = [[1,2,3],[4,5],[1,2,3]]
    Output: 4
    Explanation: One way to reach the maximum distance 4 is to pick 1 in the
                 first or third array and pick 5 in the second array.


    --- Example 2 ---
    Input: arrays = [[1],[1]]
    Output: 0


    *** Constraints ***
    m == arrays.length
    2 <= m <= 10^5
    1 <= arrays[i].length <= 500
    -104 <= arrays[i][j] <= 10^4
    arrays[i] is sorted in ascending order.
    There will be at most 105 integers in all the arrays.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Since each array is SORTED in ASCENDING order, you MUST notice that we only
    need the 0th and last element in each array.

    Brute Force would be calculating the distance between every "last element"
    of other arrays and the minimum element in the current one.

    Also calculating distance between every "0th element" of other arrays and
    the maximum element in the current one.

    However, this would lead to a O(n^2) Solution, which is unacceptable.


    The first optimization that comes to mind is that, maybe, we can make two
    copies of this "arrays" vector of vectors and then sort those two copies
    individually.

    First  one by the 0th  element in each array.
    Second one by the last element in ecah array.


    Original: arrays = [[1,2,3],[4,5],[2,3,4]]

        First  copy: : [[1,2,3],[2,3,4],[4,5],]
        Second copy: : [[4,5],[2,3,4],[1,2,3]]

    Now we don't have to calculate with every other array, instead if we are
    calculating the distance from our 0th element(the minimum one), we should
    take the last array's last element of the "Second copy" which is sorted
    in ASCENDING order by the last element.

    However, if the largest element in the entire array is in the same array
    as the current one, then don't find the distance between those two, but
    with the last element of the previous array.

    That would be O(n * logn) Time Complexity Solution.

    But... Do you notice something?

    We will ONLY care about either Largest or 2nd largest and Smallest and 2nd
    Smallest.

    In that case we don't even have to sort, we can just iterate over the
    original array and keep track of the first and 2nd largest and first and
    2nd smallest in the entire array and keep only those 4 variables.

    That not only makes this Solution work in O(1) Space Complexity, but also
    reduced Time Complexity from O(n * logn) to O(n).

*/

/* Time  Beats: 98.58% */
/* Space Beats: 25.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        pair<int, int> absolute_max = {INT_MIN, -1}; // {value, index_of_array}
        pair<int, int> next_max     = {INT_MIN, -1}; // {value, index_of_array}

        pair<int, int> absolute_min = {INT_MAX, -1}; // {value, index_of_array}
        pair<int, int> next_min     = {INT_MAX, -1}; // {value, index_of_array}

        for (int i = 0; i < arrays.size(); i++)
        {
            /* Maxes */
            if (arrays[i].back() > absolute_max.first)
            {
                next_max = absolute_max;
                absolute_max = {arrays[i].back(), i};
            }
            else if (arrays[i].back() > next_max.first)
            {
                next_max = {arrays[i].back(), i};
            }

            /* Mins */
            if (arrays[i][0] < absolute_min.first)
            {
                next_min = absolute_min;
                absolute_min = {arrays[i][0], i};
            }
            else if (arrays[i][0] < next_min.first)
            {
                next_min = {arrays[i][0], i};
            }
        }

        int max_distance = 0;

        for (int i = 0; i < arrays.size(); i++)
        {
            if (i != absolute_max.second)
                max_distance = max(max_distance, abs(absolute_max.first - arrays[i][0]));
            else
                max_distance = max(max_distance, abs(next_max.first - arrays[i][0]));


            if (i != absolute_min.second)
                max_distance = max(max_distance, abs(arrays[i].back() - absolute_min.first));
            else
                max_distance = max(max_distance, abs(arrays[i].back() - next_min.first));
        }

        return max_distance;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely Equivalent idea to the one above, written in a concise way.

*/

/* Time  Beats: 99.06% */
/* Space Beats: 29.72% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    int maxDistance(vector<vector<int>>& arrays)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int curr_min = arrays[0][0];
        int curr_max = arrays[0].back();

        int result = 0;

        for (int i = 1; i < arrays.size(); i++)
        {
            result = max( {result, arrays[i].back() - curr_min, curr_max - arrays[i][0]} );

            curr_min = min(curr_min, arrays[i][0]);
            curr_max = max(curr_max, arrays[i].back());
        }

        return result;
    }
};
