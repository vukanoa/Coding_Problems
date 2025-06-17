/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    275) H-Index II
    ===========================

    ============
    Description:
    ============

    Given an array of integers citations where citations[i] is the number of
    citations a researcher received for their ith paper and citations is sorted
    in non-descending order, return the researcher's h-index.

    According to the definition of h-index on Wikipedia: The h-index is defined
    as the maximum value of h such that the given researcher has published at
    least h papers that have each been cited at least h times.

    You must write an algorithm that runs in logarithmic time.

    =============================================
    FUNCTION: int hIndex(vector<int>& citations);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: citations = [0,1,3,5,6]
    Output: 3
    Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and
                 each of them had received 0, 1, 3, 5, 6 citations respectively
                 Since the researcher has 3 papers with at least 3 citations
                 each and the remaining two with no more than 3 citations each,
                 their h-index is 3.

    --- Example 2 ---
    Input: citations = [1,2,100]
    Output: 2


    *** Constraints ***
    n == citations.length
    1 <= n <= 10^5
    0 <= citations[i] <= 1000
    citations is sorted in ascending order.

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
/* Space Beats:  96.26% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int hIndex(vector<int>& citations)
    {
        const int N = citations.size();

        int low  = 0;
        int high = N - 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (citations[mid] >= N - mid)
                high = mid - 1;
            else
                low  = mid + 1;
        }

        return N - low;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same as above, but implemented in a different way. It's
    always beneficial to see more than one Binary Search implementation of any
    problem that uses this technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.06% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_2 {
public:
    int hIndex(vector<int>& citations)
    {
        const int N = citations.size();

        int low  = 0;
        int high = N; // we MUST include N because h-index can be 0 to N

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (citations[mid] >= N - mid)
                high = mid;     // mid might be valid, try going left
            else
                low  = mid + 1; // mid is too small
        }

        return N - low;
    }
};
