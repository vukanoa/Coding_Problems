/*
    ============
    === EASY ===
    ============

    ====================================
    3663) Find the Latest Frequent Digit
    ====================================

    ============
    Description:
    ============

    Given an integer n, find the digit that occurs least frequently in its
    decimal representation. If multiple digits have the same frequency, choose
    the smallest digit.

    Return the chosen digit as an integer.
    The frequency of a digit x is the number of times it appears in the decimal
    representation of n.

    ===========================================
    FUNCTION: int getLeastFrequentDigit(int n);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1553322
    Output: 1
    Explanation:
    The least frequent digit in n is 1, which appears only once. All other
    digits appear twice.

    --- Example 2 ---
    Input: n = 723344511
    Output: 2
    Explanation:
    The least frequent digits in n are 7, 2, and 5; each appears only once.


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 18.75% */
/* Space Beats:  6.25% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int getLeastFrequentDigit(int n)
    {
        int num = n;

        unordered_map<int,int> freq;
        while (num > 0)
        {
            int d = num % 10;
            num /= 10;

            freq[d]++;
        }

        map<int,vector<int>> freq_to_d;
        for (const auto& entry : freq)
            freq_to_d[entry.second].push_back(entry.first);

        vector<int> vec = freq_to_d.begin()->second;
        int minn = *min_element(vec.begin(), vec.end());

        return minn;
    }
};
