#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    1122) Relative Sort Array
    ===========================

    ============
    Description:
    ============

    Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all
    elements in arr2 are also in arr1.

    Sort the elements of arr1 such that the relative ordering of items in arr1
    are the same as in arr2. Elements that do not appear in arr2 should be
    placed at the end of arr1 in ascending order.

    ==============================================================================
    FUNCTION: vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
    Output: [2,2,2,1,4,3,3,9,6,7,19]

    --- Example 2 ---
    Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
    Output: [22,28,8,6,17,44]


    *** Constraints ***
    1 <= arr1.length, arr2.length <= 1000
    0 <= arr1[i], arr2[i] <= 1000
    All the elements of arr2 are distinct.
    Each arr2[i] is in arr1.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO: (Using custom sort)

*/

/* Time  Beats: 61.59% */
/* Space Beats: 64.46% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    std::vector<int> relativeSortArray(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        const int n1 = arr1.size();
        const int n2 = arr2.size();

        int a2i[1001];

        // Initialize a2i with n2 (indicating elements not in arr2)
        fill(a2i, end(a2i), n2);
        for(int i = 0; i < n2; i++)
            a2i[arr2[i]] = i;// a2i is an array & the map: x=arr2[i]->i

        sort(arr1.begin(), arr1.end(), [&](int x, int y){
            // ordered by {a2i[x], x}
            if (a2i[x] == a2i[y]) return x<y;
            return a2i[x] < a2i[y];
        });

        return arr1;
    }
};
