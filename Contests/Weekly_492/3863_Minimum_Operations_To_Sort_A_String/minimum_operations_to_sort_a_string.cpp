/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3863) Minimum Operations to Sort a String
    =========================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    In one operation, you can select any substring of s that is not the entire
    string and sort it in non-descending alphabetical order.

    Return the minimum number of operations required to make s sorted in
    non-descending order. If it is not possible, return -1.

    ======================================
    FUNCTION: int minOperations(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "dog"
    Output: 1
    Explanation:
    Sort substring "og" to "go".
    Now, s = "dgo", which is sorted in ascending order. Thus, the answer is 1.


    --- Example 2 ---
    Input: s = "card"
    Output: 2
    Explanation:
    Sort substring "car" to "acr", so s = "acrd".
    Sort substring "rd" to "dr", making s = "acdr", which is sorted in
    ascending order. Thus, the answer is 2.


    --- Example 3 ---
    Input: s = "gf"
    Output: -1
    Explanation:
    It is impossible to sort s under the given constraints. Thus, the answer is
    -1.



    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only lowercase English letters.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.46% */
/* Space Beats: 75.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(string s)
    {
        const int N = s.size();

        if (N == 1)
            return 0;
        
        if (N == 2)
            return (s[0] <= s[1]) ? 0 : -1;

        if (is_sorted(s.begin(), s.end()))
            return 0;
        
        // ASCII
        char min_chr = 'z' + 1; // '{' (open brace)
        char max_chr = 'a' - 1; // '`' (backtick)

        int min_chr_idx = -1;
        int max_chr_idx = -1;

        // Find LEFTMOST  index of the SMALLEST character (i.e. min chr)
        // Find RIGHTMOST index of the LARGEST  character (i.e. max chr)
        for (int i = 0; i < N; i++)
        {
            if (s[i] < min_chr)
            {
                min_chr     = s[i];
                min_chr_idx = i;
            }

            if (s[i] >= max_chr)
            {
                max_chr     = s[i];
                max_chr_idx = i;
            }
        }

        if (min_chr_idx == 0 || max_chr_idx == N-1)
            return 1;
        
        return (min_chr_idx == N-1 && max_chr_idx == 0) ? 3 : 2;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.11% */
/* Space Beats: 61.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minOperations(string s)
    {
        const int N = s.size();

        if (is_sorted(begin(s), end(s)))
            return 0;

        if (N == 2)
            return -1;

        auto [it_min_chr, it_max_chr] = minmax_element(s.begin() + 1, s.end() - 1);

        if (s[0] <= s[N-1] && (s[0] <= *it_min_chr || *it_max_chr <= s[N-1]))
            return 1;

        return (s[N-1] < *it_min_chr && s[0] > *it_max_chr) ? 3 : 2;
    }
};
