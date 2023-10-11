#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    115) Distinct Subsequences
    ===========================

    ============
    Description:
    ============

    Given two strings s and t, return the number of distinct subsequences of s
    which equals t.

    The test cases are generated so that the answer fits on a 32-bit signed
    integer.

    ==============================================
    FUNCTION: int numDistinct(string s, string t);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "rabbbit", t = "rabbit"
    Output: 3
    Explanation:
    As shown below, there are 3 ways you can generate "rabbit" from s.

            ----------------
            |              |
            v              |
        rabbbit            |
            #           Omit this one
                           |
                           |
           -----------------
           |               |
           v               |
        rabbbit            |
           #               |
                           |
                           |
          ------------------
          |
          v
        rabbbit
          #




    --- Example 2 ---
    Input: s = "babgbag", t = "bag"
    Output: 5
    Explanation:
    As shown below, there are 5 ways you can generate "bag" from s.

        babgbag
          # ###    <--- Omit these

        babgbag
          ####     <--- Omit these

        babgbag
         ####      <--- Omit these

        babgbag
        ## ##      <--- Omit these

        babgbag
        ####       <--- Omit these


    *** Constraints ***
    1 <= s.length, t.length <= 1000        // This is important
    s and t consist of English letters.

*/


/*
    ------------
    --- IDEA ---
    ------------

    It's pretty similar to LCS(Longest Common Subsequence), but there are
    important differences. You really have to understand why and how are you
    filling the matrix "dp".

    Here is matrix "dp" for the Example 1:

        Input: s = "rabbbit", t = "rabbit"
        Output: 3

             0     1     2     3     4     5     6      7
            'r'   'a'   'b'   'b'   'b'   'i'   't'    ''
          +-----+-----+-----+-----+-----+-----+-----++-----+
    0 'r' |  3  |  0  |  0  |  0  |  0  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    1 'a' |  3  |  3  |  0  |  0  |  0  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    2 'b' |  3  |  3  |  3  |  1  |  0  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    3 'b' |  3  |  3  |  3  |  2  |  1  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    4 'i' |  1  |  1  |  1  |  1  |  1  |  1  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    5 't' |  1  |  1  |  1  |  1  |  1  |  1  |  1  ||  0  |
          +=====+=====+=====+=====+=====+=====+=====++=====+
    6 ''  |  1  |  1  |  1  |  1  |  1  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----+-----++-----+




    And here it is for the Example 2:

        Input: s = "babgbag", t = "bag"
        Output: 5

             0     1     2     3     4     5     6      7
            'b'   'a'   'b'   'g'   'b'   'a'   'g'    ''
          +-----+-----+-----+-----+-----+-----+-----++-----+
    0 'b' |  5  |  2  |  2  |  1  |  1  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    1 'a' |  3  |  3  |  1  |  1  |  1  |  1  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    2 'g' |  2  |  2  |  2  |  2  |  1  |  1  |  1  ||  0  |
          +=====+=====+=====+=====+=====+=====+=====++=====+
    6 ''  |  1  |  1  |  1  |  1  |  1  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----+-----++-----+


    First we fill the very last row with 1's because if t is an empty string
    then whatever happens to be in the string s, we know that the maximum
    number of distinct subsequences is 1. (Omit all character in the string s).

    However, if the opposite is the case then that means that the maximum
    number of distinct subsequences is 0. Why?

    Consider this:
        s = "bc"
        t = "abc"

    There is nothing we can do to string s to make it be equal to t(adding is
    not allow, this is not "Edit Distance" Problem).

    So then if:
        s = ""
        t = "rab"

    Then the answer is 0.

    Since this matrix "dp" is of size (M+1) * (N+1) we are strating from:
        i = M
        j = N

    Since we have already computed the very last row and the very last column.

    So we are starting at that position and we are going backwards(left) within
    the Rows and then backwards(up) once the Rows is finished.

    This is the main point:
        if (t[i] == s[j]) // Remember that i is the Row and M == t.length()!!
            dp[i][j] = Right + Diagonal
        else
            dp[i][j] = Right only

    Make sure to understand what this means.

    If we are at certain position 'i' that means that we're considering string
    s being equal to the substring from that position untli the end.

             0     1     2     3     4     5     6      7
            'b'   'a'   'b'   'g'   'b'   'a'   'g'    ''
          +-----+-----+-----+-----+-----+-----+-----++-----+
    0 'b' |  5  |  2  |  2  |  1  |  1  |  0  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    1 'a' |  3  |  3  |  1  |  1  |  1  |  1  |  0  ||  0  |
          +-----+-----+-----+-----+-----+-----+-----++-----+
    2 'g' |  2  |  2  |  2  |  2  |  1  |  1  |  1  ||  0  |
          +=====+=====+=====+=====+=====+=====+=====++=====+
    6 ''  |  1  |  1  |  1  |  1  |  1  |  1  |  1  ||  1  |
          +-----+-----+-----+-----+-----+-----+-----++-----+

    Each cell represents one subproblem.
    i determines what substring out of string s, we are looking right now.
    j determines what substring out of string t, we are looking right now.

    Let's say that i == 3. That means subtring of s we're considering is "gbag"

    Let's say that j == 1. That means substring of t we're considering is "ag"

    So what does that mean?

    It's the same thing as if the example looks like this:
        s = "gbag"
        t = "ag"

    What is the number of distinct subsequences. It's obvious that it's 1.

    But how do we know that? Or, rather, how did we conclude that out of the
    previously done subproblems before this one?

    If the beginning characters are NOT the same, then it's the same answer as
    if the example was:
        s = "bag"
        t = "ag"

    So what's the answer of that? What is the maximum number od distinct
    subsequences there?
    We can see that's it's 1.

    But, here comes the difficult part:
        What if the beginning characters ARE THE SAME?

    Let's consider different example(Let's use the subproblem of the Example 1)

        s = "bbit"
        t = "bit"

    What is the maximum number of distinct subsequences here?
    It's 2.

        First:
            s = "bbit"
                 #   <---- Omit this one

            t = "bit"


        Second:
            s = "bbit"
                  #  <---- Omit this one

            t = "bit"



    So if you think about the first one, it's really not any different,
    actually, it's the exact same thing - We ask:"What is the maximum number of
    distinct subsequnces if we omit this current character in string s?

    However, the Second one is the "important one".
    We want to know, IF WE TAKE THIS CURRENT CHARACTER(use it because it's the
    same one as the one at the beginning of string t), then what is the maximum
    number of distinct subsequences of the REMAINING string, which in this case
    is this:
        s = "bit"  (notice how the first 'b' isn't there anymore)
        t = "it"   (notuce how the first 'b' isn't there anymore)

    And we have to add those two answers together and store it in out dp[i][j].


    But how do we get the answer of this subproblem:
        s = "bit"
        t = "it"

    When we have:
        s = "bbit"
        t = "bit"


    Well, you can see that the answer you're looking for is:
        Diagonally ==> (i+1, j+1)


    That's why we do:
        if (t[i] == s[j])
            dp[i][j] = dp[i][j+1] + dp[i+1][j+1];
        else
            dp[i][j] = dp[i][j+1]

*/

/* Time  Beats: 65.41% */
/* Space Beats: 28.02% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution {
public:
    int numDistinct(std::string s, std::string t)
    {
        int M = t.length(); // Rows are T's length(It's easier for me to visualize it that way)
        int N = s.length();

        // It has to be "unsigned long long" since there can be some big example, as the one below
        std::vector<std::vector<unsigned long long>> dp(M + 1, std::vector<unsigned long long>(N + 1, 0));
        for (int i = 0; i <= N; i++)
            dp[M][i] = 1; // Last Row: s="..."  t=""

        for (int i = M-1; i >= 0; i--)
        {
            for (int j = N-1; j >= 0; j--)
            {
                if (t[i] == s[j])
                    dp[i][j] = dp[i+1][j+1] + dp[i][j+1]; // Diagonal + Right
                else
                    dp[i][j] = dp[i][j+1]; // Right
            }
        }

        return (int)dp[0][0];
    }
};

int
main()
{
    Solution sol;

    /* Example 1 */
    // std::string s = "rabbbit";
    // std::string t = "rabbit";


    /* Example 2 */
    std::string s = "babgbag";
    std::string t = "bag";


    /* Example BIG */
    // std::string s = "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo";
    // std::string t = "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys";


    std::cout << "\n\t==============================";
    std::cout << "\n\t=== DISTINCT SUBSEQUENCES ===";
    std::cout << "\n\t==============================\n";

    /* Write Input */
    std::cout << "\n\ts = \"" << s << "\"";
    std::cout << "\n\tt = \"" << t << "\"\n";

    /* Solution */
    int res = sol.numDistinct(s, t);

    /* Write Output */
    std::cout << "\n\tResult: " << res << "\n\n";

    return 0;
}
