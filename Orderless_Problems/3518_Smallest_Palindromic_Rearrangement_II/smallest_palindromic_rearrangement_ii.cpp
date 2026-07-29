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
    ------------
    --- IDEA ---
    ------------

    My Example:
        left_part_of_the_palindrome = "abbbcf"  <--  Sorted lexicographically

        There are 6! = 120 permutations:

              1. abbbcf
              2. abbbfc
              3. abbcbf
              4. abbcfb
              5. abbfbc
              6. abbfcb
              7. abcbbf
              8. abcbfb
              9. abcfbb
             10. abfbbc
             11. abfbcb
             ...


    Even if N--i.e. size of string s--is ODD, we will NOT take the middle char
    in the "left_part".

    Why?
    Because if there IS a middle charactr in a palindrome, two things are true:

        1. There is EXACTLY 1 character with an ODD frequency(i.e. middle_char)
        2. The ONE AND ONLY index at which that char can be at is index: N/2

    Therefore, even if there is a middle character--It will ALWAYS be at the
    same position!

            a e e c v c e e a       N = 9  (middle_char's freq is exactly 1)
            0 1 2 3 4 5 6 7 8
                    ^
                    |
                    |
                  4 = N/2


            a f f c f c f f a       N = 9  (middle_char's freq is NOT 1 )
            0 1 2 3 4 5 6 7 8              (here middle_char's freq is 5)
                    ^
                    |
                    |
                  4 = N/2
                    
    That's why we do NOT take that additional frequency into account.
    We'll only weork with:

        "aeec" for the first  example
        "affc" for the second example


    Steps for solving this problem:

        1: Find the frequency of this FIRST HALF of s, w/o the middle_chr is
           exists

        2. If (total_permutations < k) possible, then return ""

        3. Take characters one-by-one and find the multinominal coef of
           remaining.

        4. if (coef >= k)
               // Fix  this character at pos-th position
           else
               // Skip this character at pos-th position and try to fix next
               // lexicographically smallest character for this pos-th position

        5. right_part = reverse(left_part)

        6. If (N % 2 == 0), i.e. size of s is ODD, then there is NO middle_chr
               return left_part + right_part
           else
               return left_part + middle_chr + right_part

*/

/* Time  Beats: 71.01% */
/* Space Beats: 75.36% */

/* Time  Complexity: O(N + 26^2) --> O(N + 1) --> O(N) */
/* Space Complexity: O(26) ---------------------> O(1) */
class Solution {
private:
    const int MAX_K = 1e6 + 1;

public:
    string smallestPalindrome(string s, int k)
    {
        const int N = s.size();

        // Step 1: Find the frequency of this FIRST HALF of s, w/o the
        //         middle_chr is exists
        int freq[26] = {0};
        for (int i = 0; i < N/2; i++) // Process ONLY THE FIRST HALF! (w/o mid)
            freq[s[i] - 'a']++;

        char middle_chr = '#'; // Middle exists IF AND ONLY IF size N is ODD!
        if (N & 1)
            middle_chr = s[N/2];

        // Step 2: If (total_permutations < k) then it's possible--return ""
        long long total_permutations = multinomial(freq);
        if (total_permutations < k)
            return "";

        // Step 3: Take characters one-by-one and find the multinominal coef of
        //         remaining.
        string left_part = "";

        for (int pos = 0; pos < N/2; pos++)
        {
            for (int i = 0; i < 26; i++)
            {
                if (freq[i] > 0)
                {
                    freq[i]--;

                    long long permutations = multinomial(freq);

                    // Step 4:
                    if (permutations >= k)
                    {
                        // Fix this character at this "pos"-th position
                        left_part += static_cast<char>(i + 'a');

                        break; // Since we have successfully FIXED chr at "pos"
                    }
                    else
                    {
                        // Skip this character--i.e. character (i + 'a')--for
                        // "pos"-th position and try to fix next
                        // lexicographically smallest character at this
                        // "pos"-th position
                        k -= permutations;
                        freq[i]++;
                    }
                }
            }
        }

        // Step 5: right_part = reverse(left_part)
        string right_part = left_part;
        reverse(right_part.begin(), right_part.end());

        // Step 6: If size of original stirng s is ODD--There is NO middle_chr
        //        return left_part + right_part
        //    else
        //        return left_part + middle_chr + right_part
        if (N % 2 == 0) // i.e. there is NO middle chr, i.e. N is EVEN
            return left_part + right_part;

        return left_part + middle_chr + right_part;
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
        if (n < k)
            return 0;

        /*
            "n choose k" is EQUIVALENT to "n choose (n - k)"

              (  n  )           (  n  )
              (     )   <===>   (     )
              (  k  )           ( n-k )

            So, if k is STRICTLY GREATER than n/2, then (n - k) is smaller.
        */
        if (k > n/2)
            k = n - k;

        long long result = 1;
        for (int i = 1; i <= k; i++)
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

        Can be written as:

            "n choose k1" * "(n - k1) choose k2" * "(n - k1 - k2) choose k3"

                ( n  )             ( n - k1 )          ( n - k1 - k2 )
                (    )      *      (        )     *    (             )
                ( k1 )             (   k2   )          (     k3      )




        For example:

        How many DISTINCT permutations exist in a word "ARKANSAS"?
        (accounting for repeated letters)

        Permutations of multiset elements
        In this case:

            The total number of permutations of 8 letters is 8!

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
                        |   R   :    1   |
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
    long long multinomial(int (&freq)[26])
    {
        int total_characters = accumulate(begin(freq), end(freq), 0);

        long long result = 1LL;
        for (int i = 0; i < 26; i++)
        {
            int frequency_of_curr_chr = freq[i];

            result *= binomial(total_characters, frequency_of_curr_chr);

            if (result >= MAX_K)
                return MAX_K;

            total_characters -= frequency_of_curr_chr;
        }

        return result;
    }
};
