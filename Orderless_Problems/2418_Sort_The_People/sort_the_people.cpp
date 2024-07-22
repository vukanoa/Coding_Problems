#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    =====================
    2418) Sort the People
    =====================

    ============
    Description:
    ============

    You are given an array of strings names, and an array heights that consists
    of distinct positive integers. Both arrays are of length n.

    For each index i, names[i] and heights[i] denote the name and height of the
    ith person.

    Return names sorted in descending order by the people's heights.

    =================================================================================
    FUNCTION: vector<string> sortPeople(vector<string>& names, vector<int>& heights);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: names = ["Mary","John","Emma"], heights = [180,165,170]
    Output: ["Mary","Emma","John"]
    Explanation: Mary is the tallest, followed by Emma and John.

    --- Example 2 ---
    Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
    Output: ["Bob","Alice","Bob"]
    Explanation: The first Bob is the tallest, followed by Alice and the second
                 Bob.


    *** Constraints ***
    n == names.length == heights.length
    1 <= n <= 10^3
    1 <= names[i].length <= 20
    1 <= heights[i] <= 10^5
    names[i] consists of lower and upper case English letters.
    All the values of heights are distinct.

*/

using namespace std;

/* Time  Beats: 75.15% */
/* Space Beats: 70.36% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        vector<pair<int, string>> heights_names;

        for (int i = 0; i < names.size(); i++)
            heights_names.push_back( {heights[i], names[i]} );

        sort(heights_names.begin(), heights_names.end(), std::greater<>());

        for (int i = 0; i < names.size(); i++)
            names[i] = heights_names[i].second;

        return names;
    }
};
