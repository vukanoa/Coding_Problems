#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ============================
    1550) Three Consecutive Odds
    ============================

    ============
    Description:
    ============

    Given an integer array arr, return true if there are three consecutive odd
    numbers in the array. Otherwise, return false.

    ======================================================
    FUNCTION: bool threeConsecutiveOdds(vector<int>& arr);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,6,4,1]
    Output: false
    Explanation: There are no three consecutive odds.

    --- Example 2 ---
    Input: arr = [1,2,34,3,4,5,7,23,12]
    Output: true
    Explanation: [5,7,23] are three consecutive odds.


    *** Constraints ***
    1 <= arr.length <= 1000
    1 <= arr[i] <= 1000

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Sliding-Window technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 45.76%  */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr)
    {
        int window = 0;
        for (int i = 0; i < 3 && i < arr.size(); i++)
            window += arr[i] % 2;

        if (window == 3)
            return true;

        for (int i = 3; i < arr.size(); i++)
        {
            window += arr[i] % 2;
            window -= arr[i - 3] % 2;

            if (window == 3)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Self_explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.60% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool threeConsecutiveOdds(vector<int>& arr)
    {
        const int N = arr.size();
        int concecutive_odds = 0;

        // Loop through each element in the array
        for (int i = 0; i < N; i++)
        {
            if (arr[i] & 1)
                concecutive_odds++;
            else
                concecutive_odds = 0;


            if (concecutive_odds == 3)
                return true;
        }

        return false;
    }
};
