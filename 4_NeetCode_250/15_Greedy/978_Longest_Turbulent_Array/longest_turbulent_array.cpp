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

/* Time  Beats: 100.00% */
/* Space Beats:  27.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr)
    {
        const int N = arr.size();
        int result = 1;

        /**********************/
        /* Start with GREATER */
        /**********************/
        int L = 0;
        int R = 0;
        while (R < N-1)
        {
            result = max(result, R - L + 1);

            int k = (R - L);

            if (k & 1) // Odd
            {
                if (arr[R] > arr[R+1]) // NOT what we want
                    L = R;
                else if (arr[R] == arr[R+1])
                    L = R + 1;
            }
            else
            {
                if (arr[R] < arr[R+1]) // NOT what we want
                    L = R + 1;
                else if (arr[R] == arr[R+1])
                    L = R + 1;
            }

            // Increment
            R++;
        }
        result = max(result, R - L + 1);



        /**********************/
        /* Start with SMALLER */
        /**********************/
        int l = 0;
        int r = 0;
        while (r < N-1)
        {
            result = max(result, r - l + 1);

            int k = (r - l);

            if (k & 1) // Odd
            {
                if (arr[r] < arr[r+1]) // NOT what we want
                    l = r;
                else if (arr[r] == arr[r+1])
                    l = r + 1;
            }
            else
            {
                if (arr[r] > arr[r+1]) // NOT what we want
                    l = r + 1;
                else if (arr[r] == arr[r+1])
                    l = r + 1;
            }

            // Increment
            r++;
        }
        result = max(result, r - l + 1);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  60.70% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Kadane_Algorithm {
public:
    int maxTurbulenceSize(vector<int>& arr)
    {
        const int N = arr.size();

        int result = 1;

        int smaller = 1;
        int greater = 1;

        for (int i = 0; i < N-1; i++)
        {
            if (arr[i] > arr[i+1])
            {
                smaller = greater + 1;
                greater = 1;
            }
            else if (arr[i] < arr[i+1])
            {
                greater = smaller + 1;
                smaller = 1;
            }
            else
            {
                smaller = 1;
                greater = 1;
            }

            result = max(result, max(smaller, greater));
        }

        return result;
    }
};
