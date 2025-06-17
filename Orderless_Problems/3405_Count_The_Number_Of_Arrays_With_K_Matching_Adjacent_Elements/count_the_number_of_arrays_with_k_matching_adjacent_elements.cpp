/*
    ============
    === HARD ===
    ============

    ==================================================================
    3405) Count the Number of Arrays with K Matching Adjacent Elements 
    ==================================================================

    ============
    Description:
    ============

    You are given three integers n, m, k. A good array arr of size n is defined
    as follows:

        + Each element in arr is in the inclusive range [1, m].

        + Exactly k indices i (where 1 <= i < n) satisfy the condition
          arr[i - 1] == arr[i].

    Return the number of good arrays that can be formed.

    Since the answer may be very large, return it modulo 10^9 + 7.

    ===================================================
    FUNCTION: int countGoodArrays(int n, int m, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, m = 2, k = 1
    Output: 4
    Explanation:
        + There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and
          [2, 2, 1].

        + Hence, the answer is 4.


    --- Example 2 ---
    Input: n = 4, m = 2, k = 2
    Output: 6
    Explanation:
        + The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2],
          [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].

        + Hence, the answer is 6.


    --- Example 3 ---
    Input: n = 5, m = 2, k = 0
    Output: 2
    Explanation:
        + The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the
          answer is 2.


    *** Constraints ***
    1 <= n <= 10^5
    1 <= m <= 10^5
    0 <= k <= n - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    result = C(n−1, k) × m × (m−1)^(n−k−1)  (mod 10^9 + 7)


        C(n−1, k) ---> In how many ways can we pick 'k' indices from 'n-1'
                       places?

        Once we have the number of different ways to pick 'k' indices from
        'n-1' places, we multiply that with 'm'.

        Why with 'm'?

        Because, since all the 'k' elements need to have the same values and
        possible values are [1, m], all of our 'k' elements can be each of them
        at a different time.


    But this isn't all.

    We also need to see in how many different combinations are there of the
    remaining indices.

    However, there's one caveat: If all 'k' values are, say 4, then the
    remaining elements cannot be 4 since that would make more than EXACTLY 'k'
    elements with the same value.

    That's why we need to pick elements from (m-1) values.

    But how many do we need to pick?


    Well, if for example we have:

        n = 7
        k = 3
        m = 9

        _ _ _ _ _ _ _
        0 1 2 3 4 5 6

    Since 'k' are reserved to be one of the values from [1, m], that leaves us
    with:

        n - k - 1 <==> 7 - 3 - 1 = 3

    Why -1 though?

    Because it's not exactly 'k' elements, it's 'k' + 1 because every index
    EXCEPT the leftmost 'k' index, is having its pair.

    In other words--Each of the 'k' indices have its left pair that is one of
    the other 'k' indices, however the leftmost one does NOT have its left
    pair itself.

    So 'k' indices have it's LEFT pair that is also a 'k' index, however ONE
    index of 'k' does NOT have it's LEFT pair, therefore we are NOT counting
    it.

    Let me give you a visual example:

            _ _ _ _ _ _ _ _ _ ... _ _ _
            0 1 2 3 4 5 6 7 8 ...

    Let's say k = 4

            _ X X X X _ _ _ _ ... _ _ _
            0 1 2 3 4 5 6 7 8 ...

    These X's are 'k' indices.

    However, the leftmost 'k' index is having a left "buddy" that is NOT a
    'k' index, however that index(0 in our case) is ALSO having the same value
    as other 'k' indices.

    Read this slowly again and you'll understand it.


    That's why we don't pick the remaining non-k values as:

        (m-1)^(n-k), instead we do: (m-1)^(n-k-1)


    Since (m-1)^(n-k-1) can be a LARGE number and we need to MOD it, we can
    do what's called "modular_exponentiation".

    Reading through the code is enough after this explanation.

*/

/* Time  Beats: 12.50% */
/* Space Beats: 76.14% */

/* Time  Complexity: O(log(N - K)) */
/* Space Complexity: O(1)          */
class Solution {
private:
    static constexpr int MOD   = 1e9 + 7;
    static constexpr int MAX_N = 1e5;

    long long factorial[MAX_N];
    long long inverse_factorial[MAX_N];

public:
    int countGoodArrays(int n, int m, int k)
    {
        initialize_factorials_and_inverse_factorials();

        return combinations(n-1, k) * m % MOD * modular_exponentiation(m-1, n-k-1) % MOD;
    }

private:
    long long modular_exponentiation(long long base, long long exp)
    {
        long long result = 1;
        while (exp > 0)
        {
            if (exp & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exp /= 2;
        }

        return result;
    }

    long long combinations(int x, int y)
    {
        /*

           If you're wondering why are we doing this with a weird
           "inverse_factorial", the answer is that code is difficult to read as
           a math formula.

           This is literally the definition of "n choose k" combinatorial
           problem in math, it's called binomial coefficient. 

            ****************
            *** BINOMIAL ***
            ****************

               ( n )         n!
               (   ) = --------------
               ( k )    k! * (n - k)!

        */
        return factorial[x] * inverse_factorial[y] % MOD * inverse_factorial[x - y] % MOD;
    }

    void initialize_factorials_and_inverse_factorials()
    {
        if (factorial[0])
            return;

        /* Factorial */
        factorial[0] = 1;
        for (int i = 1; i < MAX_N; i++)
            factorial[i] = factorial[i - 1] * i % MOD;

        /* Inverse Factorial */
        inverse_factorial[MAX_N - 1] = modular_exponentiation(factorial[MAX_N - 1], MOD - 2);
        for (int i = MAX_N - 1; i >= 1; i--)
            inverse_factorial[i - 1] = inverse_factorial[i] * i % MOD;
    }
};
