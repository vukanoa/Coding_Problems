/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    978) Longest Turbulent Array
    ============================

    ============
    Description:
    ============

    Given an integer array arr, return the length of a maximum size turbulent
    subarray of arr.

    A subarray is turbulent if the comparison sign flips between each adjacent
    pair of elements in the subarray.

    More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said
    to be turbulent if and only if:

        For i <= k < j:
            arr[k] > arr[k + 1] when k is odd, and
            arr[k] < arr[k + 1] when k is even.
        Or, for i <= k < j:
            arr[k] > arr[k + 1] when k is even, and
            arr[k] < arr[k + 1] when k is od

    ==================================================
    FUNCTION: int maxTurbulenceSize(vector<int>& arr);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [9,4,2,10,7,8,8,1,9]
    Output: 5
    Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]


    --- Example 2 ---
    Input: arr = [4,8,12,16]
    Output: 2


    --- Example 3 ---
    Input: arr = [100]
    Output: 1


    *** Constraints ***
    1 <= arr.length <= 4 * 10^4
    0 <= arr[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.99% */
/* Space Beats: 36.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Naive_Intuitive {
public:
    int maxTurbulenceSize(vector<int>& arr)
    {
        if (arr.size() == 1)
            return 1;

        int max_subarray = 0;

        int start = 0;
        int subarray = 0;

        // k is odd
        while (start < arr.size()-1)
        {
            int k;
            for (k = start; k < arr.size()-1; k++)
            {
                if (k & 1) // k is odd
                {
                    if ( !(arr[k] > arr[k + 1]))
                        break;

                    subarray++;
                }
                else
                {
                    if ( !(arr[k] < arr[k + 1]) )
                        break;

                    subarray++;
                }
            }

            max_subarray = std::max(max_subarray, subarray+1);

            start = k+1;
            subarray = 0;
        }

        start = 0;
        subarray = 0;

        // k is even
        while (start < arr.size()-1)
        {
            int k;
            for (k = start; k < arr.size()-1; k++)
            {
                if (k & 1) // k is odd
                {
                    if ( !(arr[k] < arr[k + 1]))
                        break;

                    subarray++;
                }
                else
                {
                    if ( !(arr[k] > arr[k + 1]) )
                        break;

                    subarray++;
                }
            }

            max_subarray = std::max(max_subarray, subarray+1);

            start = k+1;
            subarray = 0;
        }

        return max_subarray;
    }
};
