/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    2438) Range Product Queries of Powers
    =====================================

    ============
    Description:
    ============

    Given a positive integer n, there exists a 0-indexed array called powers,
    composed of the minimum number of powers of 2 that sum to n. The array is
    sorted in non-decreasing order, and there is only one way to form the array

    You are also given a 0-indexed 2D integer array queries, where
    queries[i] = [lefti, righti]. Each queries[i] represents a query where you
    have to find the product of all powers[j] with lefti <= j <= righti.

    Return an array answers, equal in length to queries, where answers[i] is
    the answer to the ith query. Since the answer to the ith query may be too
    large, each answers[i] should be returned modulo 10^9 + 7.

    ==========================================================================
    FUNCTION: vector<int> productQueries(int n, vector<vector<int>>& queries);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 15, queries = [[0,1],[2,2],[0,3]]
    Output: [2,4,64]
    Explanation:
    For n = 15, powers = [1,2,4,8]. It can be shown that powers cannot be a smaller size.
    Answer to 1st query: powers[0] * powers[1] = 1 * 2 = 2.
    Answer to 2nd query: powers[2] = 4.
    Answer to 3rd query: powers[0] * powers[1] * powers[2] * powers[3] = 1 * 2 * 4 * 8 = 64.
    Each answer modulo 10^9 + 7 yields the same answer, so [2,4,64] is returned.

    --- Example 2 ---
    Input: n = 2, queries = [[0,0]]
    Output: [2]
    Explanation:
    For n = 2, powers = [2].
    The answer to the only query is powers[0] = 2. The answer modulo 10^9 + 7
    is the same, so [2] is returned.


    *** Constraints ***
    1 <= n <= 10^9
    1 <= queries.length <= 10^5
    0 <= starti <= endi < powers.length

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.21% */
/* Space Beats: 58.51% */

/* Time  Complexity: O(N + Q) */
/* Space Complexity: O(N)     */
class Solution {
private:
    const int MOD = 1e9 + 7; // Prime number

public:
    vector<int> productQueries(int n, vector<vector<int>>& queries)
    {
        vector<int> powers;
        vector<int> answer;

        int ith_bit = 0;
        while (n > 0)
        {
            if (n & 1)
                powers.push_back(ith_bit);

            n >>= 1; // Divide by 2. Instruction: sar(shift arithmetic right)
            ith_bit++;
        }

        // Create "Prefix Sum" of vector "powers"
        partial_sum(powers.begin(), powers.end(), powers.begin());

        for (const auto& query : queries)
        {
            const int left  = query[0];
            const int right = query[1];

            int curr_power = powers[right] - (left == 0 ? 0 : powers[left - 1]);

            answer.push_back(fast_exponentiation(2, curr_power));
        }

        return answer;
    }

private:
    long long fast_exponentiation(long long base, long long exponent)
    {
        long long result = 1;
        base %= MOD;

        while (exponent > 0)
        {
            // If the current LSB is set(i.e. 1)
            if (exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;

            // Right Shift
            exponent >>= 1;
        }

        return result;
    }
};
