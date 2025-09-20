/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3669) Balanced K-Factor Decomposition
    =====================================

    ============
    Description:
    ============

    Given two integers n and k, split the number n into exactly k positive
    integers such that the product of these integers is equal to n.

    Return any one split in which the maximum difference between any two
    numbers is minimized. You may return the result in any order.

    ==================================================
    FUNCTION: vector<int> minDifference(int n, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 100, k = 2
    Output: [10,10]
    Explanation:
    The split [10, 10] yields 10 * 10 = 100 and a max-min difference of 0,
    which is minimal.

    --- Example 2 ---
    Input: n = 44, k = 3
    Output: [2,2,11]
    Explanation:
        Split [1, 1, 44] yields a difference of 43
        Split [1, 2, 22] yields a difference of 21
        Split [1, 4, 11] yields a difference of 10
        Split [2, 2, 11] yields a difference of 9
    Therefore, [2, 2, 11] is the optimal split with the smallest difference 9.

    --- Example 3 ---


    *** Constraints ***
    4 <= n <= 10^5
    2 <= k <= 5
    k is strictly less than the total number of positive divisors of n.

*/

#include <algorithm>
#include <climits>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.15% */
/* Space Beats: 44.69% */

/* Time  Complexity: O(k * SQRT(n)) */
/* Space Complexity: O(k + SQRT(n)) */
class Solution {
public:
    int diff = INT_MAX;

    vector<int> minDifference(int n, int k)
    {
        vector<int> result;
        vector<int> curr;

        unordered_set<int> factors = get_all_factors_of_number(n);

        solve(n, k, factors, curr, result);

        return result;
    }

private:
    unordered_set<int> get_all_factors_of_number(int number)
    {
        unordered_set<int> uset;

        for (int f = 1; f * f <= number; f++)
        {
            if (f * f == number)
            {
                uset.insert(f); // So that we do NOT count the same one twice
            }
            else if (number % f == 0)
            {
                uset.insert(f);
                uset.insert(number / f);
            }
        }

        return uset;
    }

    void solve(int n, int k, unordered_set<int>& factors,
               vector<int>& curr, vector<int>& result)
    {
        if (k == 1)
        {
            curr.push_back(n);

            int maxx = *max_element(curr.begin(), curr.end());
            int minx = *min_element(curr.begin(), curr.end());

            int curr_diff = maxx - minx;
            if (curr_diff < diff)
            {
                diff = curr_diff;
                result = curr;
            }

            curr.pop_back();
            return;
        }

        for (const auto& factor : factors)
        {
            if (n % factor == 0)
            {
                curr.push_back(factor);
                solve(n / factor, k - 1, factors, curr, result);
                curr.pop_back();
            }
        }
    }
};
