/*
    ============
    === HARD ===
    ============

    ===========================================
    3518) Smallest Palindromic Rearrangement II
    ===========================================

    ============
    Description:
    ============

    You are given a palindromic string s and an integer k.

    Return the k-th lexicographically smallest palindromic permutation of s.

    If there are fewer than k distinct palindromic permutations, return an
    empty string.

    =====
    Note: Different rearrangements that yield the same palindromic string are
          considered identical and are counted once.
    =====

    =====================================================
    FUNCTION: string smallestPalindrome(string s, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abba", k = 2
    Output: "baab"
    Explanation:
        The two distinct palindromic rearrangements of "abba" are "abba" and
        "baab".
        Lexicographically, "abba" comes before "baab". Since k = 2, the output
        is "baab".

    --- Example 2 ---
    Input: s = "aa", k = 2
    Output: ""
    Explanation:
        There is only one palindromic rearrangement: "aa".
        The output is an empty string since k = 2 exceeds the number of
        possible rearrangements.

    --- Example 3 ---
    Input: s = "bacab", k = 1
    Output: "abcba"
    Explanation:
        The two distinct palindromic rearrangements of "bacab" are "abcba" and
        "bacab".
        Lexicographically, "abcba" comes before "bacab". Since k = 1, the
        output is "abcba".


    *** Constraints ***
    1 <= s.length <= 10^4
    s consists of lowercase English letters.
    s is guaranteed to be palindromic.
    1 <= k <= 10^6

*/

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

/*
    Steps:

    1. Find the frequency vector

    2: Find the half_freq vector
       (if there is any odd freq then store it in middle variable)

    3. Check if k > total permutation possible, if yes then return ""

    4. Take the char one by one and find the multinominal coef of remaining

    5. if (coef >= k)
           // Fix  this character in i-th position
       else
           // Skip this character in i-th position and try fixing next
           // lexicographically smallest character for this i-th position

    6. Reverse(left)

    7. return left + middle + reverse(left)

*/

/* Time  Beats: 71.88% */
/* Space Beats: 59.38% */

/* Time  Complexity: O(N + 26^2) --> O(N + 1) --> O(N) */
/* Space Complexity: O(26) ---------------------> O(1) */
class Solution {
public:
    const int MAX_K = 1e6 + 1;

    string smallestPalindrome(string s, int k)
    {
        // Step 1: Compute character frequencies
        vector<int> freq(26, 0);
        for (const char& chr : s)
            freq[chr - 'a']++;

        // Step 2: Compute half-frequencies and find middle character (if any)
        vector<int> half_freq(26, 0);
        string middle = "";

        for (int i = 0; i < 26; ++i)
        {
            if (freq[i] % 2 == 1)
                middle = char(i + 'a');

            half_freq[i] = freq[i] / 2;
        }

        const int HALF_LEN = s.length() / 2;
        string left = "";

        // Step 3: checking if k > total permutation -> if yes then return ""
        long long total_permutation = multinomial(half_freq);

        if (k > total_permutation)
            return "";

        // Step 4: Take the char one-by-one and find the multinominal coef of
        //         remaining characters
        for (int i = 0; i < HALF_LEN; i++)
        {
            for (int letter_idx = 0; letter_idx < 26; letter_idx++)
            {
                if (half_freq[letter_idx])
                {
                    half_freq[letter_idx]--;
                    long long permutation = multinomial(half_freq);

                    // Step 5
                    if (permutation >= k)
                    {
                        // Fix  this character in i-th position
                        left += char('a' + letter_idx);

                        break;
                    }
                    else
                    {
                        // Skip this character in i-th position and try fixing
                        // next lexicographically smallest character for this
                        // i-th position
                        k -= permutation;
                        half_freq[letter_idx]++;
                    }
                }
            }
        }

        // Step 6: reverse(left)
        string right = left;
        reverse(right.begin(), right.end());

        // Step 7: return left + middle + reverse(left)
        return left + middle + right;
    }

private:
    /*
        We know "n choose k" is:

                  n!
            ---------------
            (k! * (n - k)!)

        Can be written as:

            (n * (n - 1) * (n - 2) * ... * (n - k + 1))
            -------------------------------------------
                    (1 * 2 * 3 * ... * k)

    */
    long long binomial(int n, int k)
    {
        if (k > n)
            return 0;

        /*
            "n choose k" is EQUIVALENT to "n choose (n - k)"

              (  n  )           (  n  )
              (     )   <===>   (     )
              (  k  )           ( n-k )

            So, if k is more than n/2, then n - k is smaller.
        */
        if (k > n - k)
            k = n - k;

        long long result = 1;
        for(int i = 1; i <= k; i++)
        {
            result = result * (n - i + 1) / i;

            if (result >= MAX_K)
                return MAX_K;
        }

        return result;
    }



    /*
        Multinomial is:

                    n!
            -----------------
            (k1! * k2! * k3!)

        Can we written as:

            "n choose k1" * "(n - k1) choose k2" * "(n - k1 - k2) choose k3"

                ( n  )             ( n - k1 )          ( n - k1 - k2 )
                (    )      *      (        )     *    (             )
                ( k1 )             (   k2   )          (     k3      )




        For example:

        How many distinct permutations of the letters in ARKANSAS exist,
        accounting for repeated letters?

        Permutations of multiset elements
        In this case:

            The total number of permutations of 8 letters is 8!8!

            But some letters repeat (e.g., ‘A’ appears 3 times), so you divide
            by the factorials of the counts of repeated elements to remove
            duplicates.

                             Hash Map
                        |  Key  :  Value |
                        +----------------+
                        |   A   :    3   |
                        +----------------+
                        |   K   :    1   |
                        +----------------+
                        |   N   :    1   |
                        +----------------+
                        |   S   :    2   |
                        +----------------+

        That’s where this comes in:
        Multinomial coefficient:

                        8!
                ------------------
              (3! * 1! * 1! * 1! * 2!)

        Number of distinct permutations of ARKANSAS

        Or written in anoher way:

        ( 8 )     ( 8 - 3 )     ( 8 - 3 - 1 )    ( 8 - 3 - 1 - 1 )      ( 8 - 3 - 1 - 1 - 1 )
        (   )  *  (       )  *  (           )  * (               )   *  (                   )
        ( 3 )     (   1   )     (     1     )    (      1        )      (         2         )
        ~~~~~     ~~~~~~~~      ~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~~~~~~~~
          ^           ^               ^                 ^                         ^
          |           |               |                 |                         |
          |           |               |                 |                         |
          -------------------------------------------------------------------------
                                      |
                                      |
                Each of these is a Binomial Coefficient (i.e. "n choose k")

    */
    long long multinomial(vector<int>& half_freq)
    {
        int total = accumulate(half_freq.begin(), half_freq.end(), 0);

        long long result = 1;
        for (int i = 0; i < 26; i++)
        {
            int count = half_freq[i];

            result *= binomial(total, count);

            if (result >= MAX_K)
                return MAX_K;

            total -= count;
        }

        return result;
    }
};
