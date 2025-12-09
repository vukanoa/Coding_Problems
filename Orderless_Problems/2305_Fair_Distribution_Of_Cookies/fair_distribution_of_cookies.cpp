/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    2305) Fair Distribution of Cookies
    ==================================

    ============
    Description:
    ============

    You are given an integer array cookies, where cookies[i] denotes the number
    of cookies in the ith bag. You are also given an integer k that denotes the
    number of children to distribute all the bags of cookies to. All the
    cookies in the same bag must go to the same child and cannot be split up.

    The unfairness of a distribution is defined as the maximum total cookies
    obtained by a single child in the distribution.

    Return the minimum unfairness of all distributions.

    =============================================================
    FUNCTION: int distributeCookies(vector<int>& cookies, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: cookies = [8,15,10,20,8], k = 2
    Output: 31
    Explanation: One optimal distribution is [8,15,8] and [10,20]
    - The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
    - The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
    The unfairness of the distribution is max(31,30) = 31.
    It can be shown that there is no distribution with an unfairness less than 31.

    --- Example 2 ---
    Input: cookies = [6,1,3,2,2,4,1,2], k = 3
    Output: 7
    Explanation: One optimal distribution is [6,1], [3,2,2], and [4,1,2]
    - The 1st child receives [6,1] which has a total of 6 + 1 = 7 cookies.
    - The 2nd child receives [3,2,2] which has a total of 3 + 2 + 2 = 7 cookies.
    - The 3rd child receives [4,1,2] which has a total of 4 + 1 + 2 = 7 cookies.
    The unfairness of the distribution is max(7,7,7) = 7.
    It can be shown that there is no distribution with an unfairness less than 7.

    *** Constraints ***
    2 <= cookies.length <= 8
    1 <= cookies[i] <= 10^5
    2 <= k <= cookies.length

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.81% */
/* Space Beats: 48.98% */

/* Time  Complexity: O(k^N)   */
/* Space Complexity: O(N + k) */
class Solution {
public:
    int minimum_unfairness = INT_MAX;

    int distributeCookies(vector<int>& cookies, int k)
    {
        vector<int> subset_sums(k, 0);
        backtrack(0, cookies, subset_sums, k);

        return minimum_unfairness;
    }

private:
    void backtrack(int index, vector<int>& cookies, vector<int>& subset_sums, int k)
    {
        if (index == cookies.size())
        {
            int curr_max = INT_MIN;

            for (int i = 0; i < k; i++)
                curr_max = max(curr_max, subset_sums[i]);

            minimum_unfairness = min(minimum_unfairness, curr_max);
            return;
        }

        for (int i = 0; i < k; i++)
        {
            subset_sums[i] += cookies[index];
            backtrack(index + 1, cookies, subset_sums, k);
            subset_sums[i] -= cookies[index];
        }
    }
};
