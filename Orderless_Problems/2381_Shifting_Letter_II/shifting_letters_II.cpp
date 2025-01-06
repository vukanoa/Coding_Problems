/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2381) Shifting Letters II
    ===========================

    ============
    Description:
    ============

    You are given a string s of lowercase English letters and a 2D integer
    array shifts where shifts[i] = [starti, endi, directioni]. For every i,
    shift the characters in s from the index starti to the index endi
    (inclusive) forward if directioni = 1, or shift the characters backward if
    directioni = 0.

    Shifting a character forward means replacing it with the next letter in the
    alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a
    character backward means replacing it with the previous letter in the
    alphabet (wrapping around so that 'a' becomes 'z').

    Return the final string after all such shifts to s are applied.

    ========================================================================
    FUNCTION: string shiftingLetters(string s, vector<vector<int>>& shifts);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
    Output: "ace"
    Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
    Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
    Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".

    --- Example 2 ---
    Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
    Output: "catz"
    Explanation: Firstly, shift the characters from index 0 to index 0 backward. Now s = "cztz".
    Finally, shift the characters from index 1 to index 1 forward. Now s = "catz".


    *** Constraints ***
    1 <= s.length, shifts.length <= 5 * 10^4
    shifts[i].length == 3
    0 <= starti <= endi < s.length
    0 <= directioni <= 1
    s consists of lowercase English letters.

*/

#include <numeric>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Sweep Line. This is a famous technique for "intervals" kind of problems.
    Instead of going through each range of each interval, we can go only
    through each range one and utilize its "start" and "end" values to our
    advantage.

    Let's consider the first example, so it's not dry:

        Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]

        X    X
             X    X
        X         X
        0    1    2    3    4  ...


    This is how it would look like if we were to draw in on a number Line.

    However, imagine that we had these ranges instead:
        [0, 4], [2, 8], [11, 13]


        X               X
                X                       X
                                                      X         X
        0   1   2   3   4   5   6   7   8   9   10   11   12   13



    We would need to go through each range manually and then add or subtract
    depending on the "dir" value.

    But what if there are M ranges and each range is from [0, s.length()]?
    That would mean that we'd need O(M * N) time to go through each range and
    subtract/add depending on the "dir" value.

    That is way too inefficient.

    What we can do instead is use a SweepLine technique.
    How does it work. Let's consider, for now, that all "dir" values are 1.

    We need to "mark" the beginning of an interval by adding 1 to that "start"
    index.

    Then, we should DECREMENT by one at index "end + 1", i.e. one element AFTER
    the last element in the given range.

    Why are we doing that?

    Because at that point we'll know that the previous interval STOPPED.
    This doesn't make sense if you've never seen it before, but let me show you


        [0, 4], [2, 8], [11, 13]


        1                  -1
                1                          -1
                                                      1             -1
        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14

    So, how is this vector:

    dp=[1   0   1   0   0  -1   0   0   0   -1   0    1    0    0   -1]
        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14

    going to help us?


    Well, it wouldn't help us in this form. We need to do one additional,
    crucial thing, to it. That crucial thing will take us O(n) time, or one
    additional pass, so our Big O Time Complexity stays the same.

    We need to begin at index 1 and iterate until the end of the array. While
    we're iterating we need to add previous value of dp to this one.

    In other words:
        for i = 1 to N:
            dp[i] += dp[i-1]

    In third words--Do a "Partial Sum", as it's called, at least in C++.
    I'll have two Implementations down below. One with manual iteration and
    the other with a built-in function:

        std::partial_sum

    After we've done our partial_sum, this is the vector we'll end up with:

    dp=[1   1   2   2   2   1   1   1   1   0    0    1    1    1    0]
        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14

    Now simply iterate through each character in string s and add the
    corresponding value to its ASCII representation, then do a
    "mathematical_mod" because it's possible that the values can be negative
    and '%' operator doesn't work as a MODULO in mathematics, so we've fixed
    that in the function below.

    Let's just explain this line:

        char chr = mathematical_mod(s[i] - 'a' + dp[i]) + 'a';

    s[i] is an ASCII representation of an lowercase English letter [97, 122]

    Then we're SUBRACTING 'a'(value 97) from it. So if s[i] was 'b', then it
    would be:

        'b' - 'a'   <==>   98 - 97   = 1


    Now we have an index from [0, 25]

    We add dp[i] to that, i.e. our corresponding value which represents if we
    should replace it with some forward character(if its positive) or some
    previous character(if its negative).

    In mathematics -25 % 26 is 1.

    if we had a character 'b' and it turns out that dp[i] for this 'b' is -4
    then:

        'b' = 98

        98 - 'a'  <==> 98 - 97 = 1

        1 + dp[i] <==> 1 + (-4) = -3

        Since -3 is a NEGATIVE value, doing mathematical MODULO:

            -3 % 26 ---> (-3 % 26 + 26) % 26  = 23

        23 + 'a'  // To turn it to an ASCII character

        23 + 97 = 120

        120 == 'x'


*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.08% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Sweep_Line {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts)
    {
        const int N = s.length();
        const int M = shifts.size();

        ostringstream out;

        vector<int> dp(N+1, 0);
        for (const auto& shift : shifts)
        {
            const int& from = shift[0];
            const int& to   = shift[1];
            const int& dir  = shift[2];

            dp[from] += (dir == 1) ? +1 : -1;
            dp[to+1] += (dir == 1) ? -1 : +1;
        }

        for (int i = 0; i < N; i++)
        {
            if (i > 0)
                dp[i] += dp[i-1];

            char chr = mathematical_mod(s[i] - 'a' + dp[i]) + 'a';
            out << chr;
        }

        return out.str();
    }

private:
    /*
       Mathematical modulo works a bit differently than operator '%'.

       In mathematics: (-25) modulo 26 is 1
       In C++:         (-25) modulo 26 is -25

       Since we need the mathematical verison of modulo, we need to use the
       function below.

    */
    int mathematical_mod(int num)
    {
        const int ALPHABET_LENGTH = 26;
        return (num % ALPHABET_LENGTH + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    }

};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but here we're using built-in function std::partial_sum.

*/

/* Time  Beats: 48.64% */
/* Space Beats: 44.38% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Sweep_Line_Partial_Sum {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts)
    {
        const int N = s.length();
        const int M = shifts.size();

        ostringstream out;

        vector<int> dp(N+1, 0);
        for (const auto& shift : shifts)
        {
            const int& from = shift[0];
            const int& to   = shift[1];
            const int& dir  = shift[2];

            dp[from] += (dir == 1) ? +1 : -1;
            dp[to+1] += (dir == 1) ? -1 : +1;
        }

        /* Partial Sum */
        partial_sum(dp.begin(), dp.end(), dp.begin());

        for (int i = 0; i < N; i++)
        {
            char chr = mathematical_mod(s[i] - 'a' + dp[i]) + 'a';
            out << chr;
        }

        return out.str();
    }

private:
    /*
       Mathematical modulo works a bit differently than operator '%'.

       In mathematics: (-25) modulo 26 is 1
       In C++:         (-25) modulo 26 is -25

       Since we need the mathematical verison of modulo, we need to use the
       function below.

    */
    int mathematical_mod(int num)
    {
        const int ALPHABET_LENGTH = 26;
        return (num % ALPHABET_LENGTH + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    }

};
