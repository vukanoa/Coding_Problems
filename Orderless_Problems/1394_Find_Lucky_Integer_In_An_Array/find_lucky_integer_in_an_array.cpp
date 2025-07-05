/*
    ============
    === EASY ===
    ============

    ====================================
    1394) Find Lucky Integer In An Array
    ====================================

    ============
    Description:
    ============

    Given an array of integers arr, a lucky integer is an integer that has a
    frequency in the array equal to its value.

    Return the largest lucky integer in the array. If there is no lucky integer
    return -1.

    ==========================================
    FUNCTION: int findLucky(vector<int>& arr);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [2,2,3,4]
    Output: 2
    Explanation: The only lucky number in the array is 2 because frequency[2] == 2.

    --- Example 2 ---
    Input: arr = [1,2,2,3,3,3]
    Output: 3
    Explanation: 1, 2 and 3 are all lucky numbers, return the largest of them.

    --- Example 3 ---
    Input: arr = [2,2,2,3,3]
    Output: -1
    Explanation: There are no lucky numbers in the array.


    *** Constraints ***
    1 <= arr.length <= 500
    1 <= arr[i] <= 500

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findLucky(vector<int>& arr)
    {
        const int N = arr.size();
        int result = -1;

        unordered_map<int, int> freq;

        for (int i = 0; i < N; i++)
            freq[arr[i]]++;

        for (const auto& entry : freq)
        {
            if (entry.first == entry.second)
                result = max(result, entry.first);
        }

        return result;
    }
};
