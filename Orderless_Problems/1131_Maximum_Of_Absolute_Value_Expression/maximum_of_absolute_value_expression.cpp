/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1131) Maximum of Absolute Value Expression
    ==========================================

    ============
    Description:
    ============

    Given two arrays of integers with equal lengths, return the maximum value
    of:

        |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

    where the maximum is taken over all 0 <= i, j < arr1.length.

    ==================================================================
    FUNCTION: int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
    Output: 13

    --- Example 2 ---
    Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
    Output: 20


    *** Constraints ***
    2 <= arr1.length == arr2.length <= 40000
    -10^6 <= arr1[i], arr2[i] <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2)
    {
        const int N = arr1.size();

        vector<int> sum_with_positive_index (N, 0);
        vector<int> sum_with_negative_index (N, 0);

        vector<int> diff_with_positive_index(N, 0);
        vector<int> diff_with_negative_index(N, 0);

        for (int idx = 0; idx < N; idx++)
        {
            sum_with_positive_index[idx]  = arr1[idx] + arr2[idx] + idx;
            sum_with_negative_index[idx]  = arr1[idx] + arr2[idx] - idx;

            diff_with_positive_index[idx] = arr1[idx] - arr2[idx] + idx;
            diff_with_negative_index[idx] = arr1[idx] - arr2[idx] - idx;
        }

        return max( {max_diff(sum_with_positive_index),
                     max_diff(sum_with_negative_index),
                     max_diff(diff_with_positive_index),
                     max_diff(diff_with_negative_index)} );
    }

private:
    int max_diff(vector<int>& values)
    {
        int curr_max_val = values[0];
        int curr_min_val = values[0];

        for (const int& value : values)
        {
            curr_max_val = max(curr_max_val, value);
            curr_min_val = min(curr_min_val, value);
        }

        return curr_max_val - curr_min_val;
    }
};
