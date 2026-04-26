/*
    ============
    === EASY ===
    ============

    ===================================================
    1502) Can Make Arithmetic Progression From Sequence
    ===================================================

    ============
    Description:
    ============

    A sequence of numbers is called an arithmetic progression if the difference
    between any two consecutive elements is the same.

    Given an array of numbers arr, return true if the array can be rearranged
    to form an arithmetic progression. Otherwise, return false.

    ==============================================================
    FUNCTION: bool canMakeArithmeticProgression(vector<int>& arr);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [3,5,1]
    Output: true
    Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with
                 differences 2 and -2 respectively, between each consecutive
                 elements.

    --- Example 2 ---
    Input: arr = [1,2,4]
    Output: false
    Explanation: There is no way to reorder the elements to obtain an
                 arithmetic progression.


    *** Constraints ***
    2 <= arr.length <= 1000
    -10^6 <= arr[i] <= 10^6

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.28% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // SC of C++"s Intro-Sort
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr)
    {
        const int N = arr.size();

        /* Sort */
        sort(arr.begin(), arr.end());

        int diff = arr[1] - arr[0];
        for (int i = 2; i < N; i++)
        {
            if ((arr[i] - arr[i-1]) != diff)
                return false;
        }
        
        return true;
    }
};
