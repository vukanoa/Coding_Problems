/*
    ============
    === HARD ===
    ============

    ===========================================
    1735) Count Ways to Make Array With Product
    ===========================================

    ============
    Description:
    ============

    You are given a 2D integer array, queries. For each queries[i], where
    queries[i] = [ni, ki], find the number of different ways you can place
    positive integers into an array of size ni such that the product of the
    integers is ki. As the number of ways may be too large, the answer to the
    ith query is the number of ways modulo 109 + 7.

    Return an integer array answer where answer.length == queries.length, and
    answer[i] is the answer to the ith query.

    ====================================================================
    FUNCTION: vector<int> waysToFillArray(vector<vector<int>>& queries);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queries = [[2,6],[5,1],[73,660]]
    Output: [4,1,50734910]
    Explanation: Each query is independent.
    [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
    [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
    [73,660]: There are 1050734917 ways to fill an array of size 73 that
              multiply to 660. 1050734917 modulo 109 + 7 = 50734910.

    --- Example 2 ---
    Input: queries = [[1,1],[2,2],[3,3],[4,4],[5,5]]
    Output: [1,2,3,10,5]


    *** Constraints ***
    1 <= queries.length <= 10^4 
    1 <= ni, ki <= 10^4

*/

#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;


class Solution {
public:
    static constexpr int MAX_N = 10001;
    static constexpr int MOD   = 1e9 + 7;

    int smallest_prime_factor[MAX_N];
    vector<int> waysToFillArray(vector<vector<int>>& queries)
    {
        sieve();

        static long long choose[10050][33];

        /* Memset */
        memset(choose, 0, sizeof(choose));

        for (int i = 0; i < 10050; ++i)
            choose[i][0] = 1;

        // Standard Binomial Identity
        for (int n = 1; n < 10050; ++n)
        {
            for (int r = 1; r < 33; ++r)
            {
                choose[n][r] = (choose[n - 1][r - 1] + choose[n - 1][r]) % MOD;
            }
        }

        vector<int> result;

        for (const auto& query : queries)
        {
            int bucket_count = query[0];
            int value = query[1];

            vector<int> frequencies = get_factor_frequencies(value);

            long long ways = 1;

            for (const int& freq : frequencies)
            {
                ways = (ways * choose[bucket_count + freq - 1][freq]) % MOD;
            }

            result.push_back(static_cast<int>(ways));
        }

        return result;
    }

private:
    void sieve()
    {
        smallest_prime_factor[1] = 1;

        for (int i = 2; i < MAX_N; ++i)
            smallest_prime_factor[i] = i;

        for (int i = 4; i < MAX_N; i += 2)
            smallest_prime_factor[i] = 2;

        for (int i = 3; i * i < MAX_N; ++i)
        {
            if (smallest_prime_factor[i] == i)
            {
                for (int j = i * i; j < MAX_N; j += i)
                {
                    if (smallest_prime_factor[j] == j)
                        smallest_prime_factor[j] = i;
                }
            }
        }
    }

    vector<int> get_factor_frequencies(int value)
    {
        unordered_map<int, int> prime_frequency;
        vector<int> frequencies;

        while (value != 1)
        {
            int prime = smallest_prime_factor[value];
            prime_frequency[prime]++;
            value /= prime;
        }

        for (const auto& entry : prime_frequency)
            frequencies.push_back(entry.second);

        return frequencies;
    }
};
