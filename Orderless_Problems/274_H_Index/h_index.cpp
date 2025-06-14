/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    274) H-Index
    ===========================

    ============
    Description:
    ============

    Given an array of integers citations where citations[i] is the number of
    citations a researcher received for their ith paper, return the
    researcher's h-index.

    According to the definition of h-index on Wikipedia: The h-index is
    defined as the maximum value of h such that the given researcher has
    published at least h papers that have each been cited at least h times.

    =============================================
    FUNCTION: int hIndex(vector<int>& citations);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: citations = [3,0,6,1,5]
    Output: 3
    Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and
                 each of them had received 3, 0, 6, 1, 5 citations
                 respectively. Since the researcher has 3 papers with at least
                 3 citations each and the remaining two with no more than 3
                 citations each, their h-index is 3.

    --- Example 2 ---
    Input: citations = [1,3,1]
    Output: 1


    *** Constraints ***
    n == citations.length
    1 <= n <= 5000
    0 <= citations[i] <= 1000

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-expanatory.

    The first CITATION VALUE that has GREATER THAN OR EQUAL number of papers
    with than CITATION VALUE is the one we return.

    Obvious we try from the back.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.22% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(M) */ // Where 'M' is the upper bound of citations[i]
class Solution {
public:
    int hIndex(vector<int>& citations)
    {
        const int N = citations.size();

        int freq[1001];
        memset(freq, 0, sizeof(freq));

        for (const int& cit : citations)
        {
            freq[cit]++;
        }

        int at_least[1001];
        memset(at_least, 0, sizeof(at_least));

        at_least[1000] = freq[1000];
        for (int cit = 999; cit >= 0; cit--)
        {
            at_least[cit] += freq[cit] + at_least[cit+1];

            if (at_least[cit] >= cit)
                return cit;
        }

        return 0;
    }
};
