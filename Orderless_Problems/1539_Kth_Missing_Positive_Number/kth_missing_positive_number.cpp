/*
    ============
    === EASY ===
    ============

    =================================
    1539) Kth Missing Positive Number
    =================================

    ============
    Description:
    ============

    Given an array arr of positive integers sorted in a strictly increasing
    order, and an integer k.

    Return the kth positive integer that is missing from this array.

    =======================================================
    FUNCTION: int findKthPositive(vector<int>& arr, int k);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,3,4,7,11], k = 5
    Output: 9
    Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...].
                 The 5th missing positive integer is 9.

    --- Example 2 ---
    Input: arr = [1,2,3,4], k = 2
    Output: 6
    Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing
                 positive integer is 6.


    *** Constraints ***
    1 <= arr.length <= 1000
    1 <= arr[i] <= 1000
    1 <= k <= 1000
    arr[i] < arr[j] for 1 <= i < j <= arr.length

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00%% */
/* Space Beats:  59.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k)
    {
        const int N = arr.size();

        int number = 1;
        for (int i = 0; i < N; i++)
        {
            while (number < arr[i])
            {
                k--;
                if (k == 0)
                    return number;
                
                number++;
            }

            number++;
        }

        while (--k > 0)
            number++;

        return number;
    }
};
