/*
    ============
    === EASY ===
    ============

    =================================
    1200) Minimum Absolute Difference
    =================================

    ============
    Description:
    ============


    Given an array of distinct integers arr, find all pairs of elements with
    the minimum absolute difference of any two elements.

    Return a list of pairs in ascending order(with respect to pairs), each pair
    [a, b] follows

        a, b are from arr

        a < b

        b - a equals to the minimum absolute difference of any two elements in
              arr

    =====================================================================
    FUNCTION: vector<vector<int>> minimumAbsDifference(vector<int>& arr);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [4,2,1,3]
    Output: [[1,2],[2,3],[3,4]]
    Explanation: The minimum absolute difference is 1. List all pairs with
                 difference equal to 1 in ascending order.

    --- Example 2 ---
    Input: arr = [1,3,6,10,15]
    Output: [[1,3]]

    --- Example 3 ---
    Input: arr = [3,8,-10,23,19,-4,-14,27]
    Output: [[-14,-10],[19,23],[23,27]]


    *** Constraints ***
    2 <= arr.length <= 10^5
    -10^6 <= arr[i] <= 10^6

*/

#include <algorithm>
#include <climits>
#include <cstdint>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.19% */
/* Space Beats: 16.72% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // C++'s "Into Sort"
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr)
    {
        const int N = arr.size();
        vector<vector<int>> result;

        /* Sort in ASCENDING order */
        sort(arr.begin(), arr.end());

        int min_diff = INT_MAX;
        for (int i = 0; i < N-1; i++)
        {
            int curr_diff = arr[i+1] - arr[i];

            min_diff = min(min_diff, curr_diff);
        }

        for (int i = 0; i < N-1; i++)
        {
            int curr_diff = arr[i+1] - arr[i];

            if (curr_diff == min_diff)
            {
                result.push_back( {arr[i], arr[i+1]} );
            }
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

/* Time  Complexity: O(N + RANGE) */
/* Space Complexity: O(RANGE / 8) */
class Solution_Bitwise {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr)
    {
        static constexpr int ONE_MILLION = 1'000'000; // -1e6 <= arr[i] <= 1e6
        static constexpr int RANGE       = ONE_MILLION * 2 + 1;
        static constexpr int BYTE_COUNT  = (RANGE + 7) / 8;

        uint8_t bitset[BYTE_COUNT] = {0};

        for (const int& num : arr)
        {
            int shifted = num + ONE_MILLION;

            int idx = shifted / 8;
            int bit = shifted % 8;

            bitset[idx] |= (1 << (7 - bit));
        }

        bool have_prev = false;

        int min_diff  = INT_MAX;
        int prev_elem = 0;

        for (int curr_shifted_elem = 0; curr_shifted_elem < RANGE; curr_shifted_elem++)
        {
            int idx = curr_shifted_elem / 8;
            int bit = curr_shifted_elem % 8;

            if (bitset[idx] & (1 << (7 - bit)))
            {
                int curr_elem = curr_shifted_elem - ONE_MILLION;

                if (have_prev)
                    min_diff = min(min_diff, curr_elem - prev_elem);

                prev_elem = curr_elem;
                have_prev = true;
            }
        }

        vector<vector<int>> result;
        have_prev = false;

        for (int curr_shifted_elem = 0; curr_shifted_elem < RANGE; curr_shifted_elem++)
        {
            int idx = curr_shifted_elem / 8;
            int bit = curr_shifted_elem % 8;

            if (bitset[idx] & (1 << (7 - bit)))
            {
                int curr_elem = curr_shifted_elem - ONE_MILLION;

                if (have_prev && curr_elem - prev_elem == min_diff)
                    result.push_back({prev_elem, curr_elem});

                prev_elem = curr_elem;
                have_prev = true;
            }
        }

        return result;
    }
};
