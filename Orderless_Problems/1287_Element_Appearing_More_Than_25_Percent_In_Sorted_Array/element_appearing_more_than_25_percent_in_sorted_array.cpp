/*
    ============
    === EASY ===
    ============

    =====================================================
    1287) Element Appearing More than 25% In Sorted Array
    =====================================================

    ============
    Description:
    ============

    Given an integer array sorted in non-decreasing order, there is exactly one
    integer in the array that occurs more than 25% of the time, return that
    integer.

    ===================================================
    FUNCTION: int findSpecialInteger(vector<int>& arr);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,2,6,6,6,6,7,10]
    Output: 6

    --- Example 2 ---
    Input: arr = [1,1]
    Output: 1


    *** Constraints ***
    1 <= arr.length <= 10^4
    0 <= arr[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.70% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findSpecialInteger(vector<int>& arr)
    {
        const int SIZE = arr.size();
        const int N    = arr.size() / 4;

        for (int i = 0; i < SIZE - N; i++)
        {
            if (arr[i] == arr[i + N])
                return arr[i];
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  62.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Binary_Search {
public:
    int findSpecialInteger(vector<int>& arr)
    {
        const int n = arr.size();
        vector<int> candidates = {arr[n / 4], arr[n / 2], arr[3 * n / 4]};

        int target = n / 4;

        for (int candidate : candidates)
        {
            auto low  = lower_bound(arr.begin(), arr.end(), candidate);
            auto high = upper_bound(arr.begin(), arr.end(), candidate);

            int low_idx  = distance(arr.begin(), low);
            int high_idx = distance(arr.begin(), high);

            if (high_idx - low_idx > target)
                return candidate;
        }

        return -1;
    }
};
