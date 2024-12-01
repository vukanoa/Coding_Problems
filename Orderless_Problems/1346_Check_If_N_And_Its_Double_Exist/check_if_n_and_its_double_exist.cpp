#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    =====================================
    1346) Check If N and Its Double Exist
    =====================================

    ============
    Description:
    ============


    Given an array arr of integers, check if there exist two indices i and j such that :

        + i != j
        + 0 <= i, j < arr.length
        + arr[i] == 2 * arr[j]

    ==============================================
    FUNCTION: bool checkIfExist(vector<int>& arr);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [10,2,5,3]
    Output: true
    Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]

    --- Example 2 ---
    Input: arr = [3,1,7,11]
    Output: false
    Explanation: There is no i and j that satisfy the conditions.


    *** Constraints ***
    2 <= arr.length <= 500
    -10^3 <= arr[i] <= 10^3

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same as "Two Sum", but even easier. Instead of using "sum"
    it uses "product". That's literally it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  16.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool checkIfExist(vector<int>& arr)
    {
        unordered_set<int> uset;
        for (const int& num : arr)
        {
            if (uset.count(num * 2) || ((num % 2 == 0) && uset.count(num / 2)))
                return true;

            uset.insert(num);
        }

        return false;
    }
};
