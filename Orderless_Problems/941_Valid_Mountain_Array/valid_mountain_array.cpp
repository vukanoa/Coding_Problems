#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    941) Valid Mountain Array
    ===========================

    ============
    Description:
    ============

    Given an array of integers arr, return true if and only if it is a valid
    mountain array.

    Recall that arr is a mountain array if and only if:

        arr.length >= 3
        There exists some i with 0 < i < arr.length - 1 such that:
            arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
            arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

    ====================================================
    FUNCTION: bool validMountainArray(vector<int>& arr);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,1]
    Output: false

    --- Example 2 ---
    Input: arr = [3,5,5]
    Output: false

    --- Example 3 ---
    Input: arr = [0,3,2,1]
    Output: true


    *** Constraints ***
    1 <= arr.length <= 10^4
    0 <= arr[i] <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    There are a bunch of Base-edge-cases.
    1. If there are less than 2 elements, then it's CERTAINLY impossible to
       be a mountain array.

    2. If there are 2 or more, then we MUST have first to elements be STRICTLY
       increasing AND last two elements STRICTLY decreasing.

       As you can see if we have only 2 elements, this if-statement will always
       be FALSE because it's not possible to fulfill both conditions at the
       same time for array of size 2.

       That is true of arrays of size 3 and 4 as well.
       We could've wrote the first if-statement with < 5, but this also works.


    After we're done with edge-cases, simply start from element at index 2 and
    always check with the previous one. If at ANY point we find out that two
    elements that are next to each other are EQUAL we IMMEDIATELY return false.

    We are told they have to be either:
        a) STRICTLY INCREASING, or
        b) STRICTLY DECREASING

    So if at any points we find two consecutive elements of equal value, return
    false.

    After that, while the "increasing_flag" is TRUE, you must have ATLEAST
    one pair of elements where the left one is smaller than the right one.
    After that if it changes to decreasing, flip the flag and check if, until
    the end, all the elements are STRICTLY DECREASING.

    If at any point, after we've flipped the flag, we find an INCREASING pair,
    we return false.

    If we're done with the for loop and haven't return false, then return true.

*/

/* Time  Beats: 97.68% */
/* Space Beats: 43.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool validMountainArray(vector<int>& arr)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        if (arr.size() < 2)
            return false;

        if (arr[0] >= arr[1] || arr[arr.size() - 2] <= arr[arr.size() - 1])
            return false;

        bool increasing_flag = true;
        for (int i = 2; i < arr.size()-1; i++)
        {
            if (arr[i-1] == arr[i])
                return false;

            if (increasing_flag && arr[i-1] < arr[i])
                continue;

            increasing_flag = false;
            if ( ! (arr[i-1] > arr[i]))
                return false;
        }

        return true;
    }
};
