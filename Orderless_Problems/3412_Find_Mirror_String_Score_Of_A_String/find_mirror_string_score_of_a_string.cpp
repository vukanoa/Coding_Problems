/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3412) Find Mirror String Score of a String
    ==========================================

    ============
    Description:
    ============

    You are given a string s.

    We define the mirror of a letter in the English alphabet as its
    corresponding letter when the alphabet is reversed. For example, the mirror
    of 'a' is 'z', and the mirror of 'y' is 'b'.

    Initially, all characters in the string s are unmarked.

    You start with a score of 0, and you perform the following process on the
    string s:

    Iterate through the string from left to right. At each index i, find the
    closest unmarked index j such that j < i and s[j] is the mirror of s[i].
    Then, mark both indices i and j, and add the value i - j to the total
    score. If no such index j exists for the index i, move on to the next
    index without making any changes.

    Return the total score at the end of the process.

    =============================================
    FUNCTION: long long calculateScore(string s);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aczzx"
    Output: 5
    Explanation:
        i = 0. There is no index j that satisfies the conditions, so we skip.

        i = 1. There is no index j that satisfies the conditions, so we skip.

        i = 2. The closest index j that satisfies the conditions is j = 0,
        so we mark both indices 0 and 2, and then add 2 - 0 = 2 to the score.

        i = 3. There is no index j that satisfies the conditions, so we skip.

        i = 4. The closest index j that satisfies the conditions is j = 1,
        so we mark both indices 1 and 4, and then add 4 - 1 = 3 to the score.


    --- Example 2 ---
    Input: s = "abcdef"
    Output: 0
    Explanation: For each index i, there is no index j that satisfies the
                 conditions.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It is VERY important to note to yourself that we're looking for the CLOSEST
    mirror character.

    Once you keep that in mind, stack should quickly come to mind. (Or vector
    int this case, it doesn't matter)

    We are iterating from left to right and we're checking if the mirror of
    this current character has occurred already. We do that by checking if
    values of HashMap for this that mirror character is NOT empty.

    Key will be the mirror character(every character can be a mirror character)
    however values will be indices, from left-to-right.

    Example:
        a a b b a b a z ...
        0 1 2 3 4 5 6 7
                      i

    A map will look like this:

             Hash Map
        |  Key  :    Value  |
        +-------------------+
        |  'a'  : {0,1,4,6} |
        +-------------------+
        |  'b'  : {2,3,5}   |
        +-------------------+
        |  ...  :   ...     |
        +-------------------+
        |  'z'  : {}        |
        +-------------------+


    Once we're on i=7, i.e. at letter 'z', we are going to calculate its mirror
    character. In this case that's letter 'a'. Now we would like to find the
    closest letter 'a', if there is one, to the LEFT of index i.

    That is why we've used a vector/stack. We need the rightmost index of 'a'
    that is to the left of current index i.

    In this case, that would be index 6. To mark is as "used", we simply remove
    this index from 'a', i.e. we pop_back from vector(or just "pop" if you're
    using a stack) and do NOT push current index of 'z', since we've used it.

    Add: "i - idx_of_closest_mirror_chr" to the result and that's it.

*/

/* Time  Beats: 66.67% */
/* Space Beats: 75.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long calculateScore(string s)
    {
        const int N = s.size();
        long long result = 0;

        // Map each character to vector storing its indices from left-to-right
        unordered_map<char, vector<int>> letter_idxs;

        for (int i = 0; i < N; i++)
        {
            char mirror_chr = ('z' - s[i]) + 'a';

            // If we have encountered a character and it is unmarked
            if (letter_idxs[mirror_chr].size() > 0)
            {
                int idx_of_closest_mirror_chr = letter_idxs[mirror_chr].back();

                // Last element is the closest mirror element
                // Also, mark it by removing it. Make it unavailable.
                letter_idxs[mirror_chr].pop_back();

                result += (i - idx_of_closest_mirror_chr);
            }
            else
            {
                // If it is the first occurance - unmarked
                letter_idxs[s[i]].push_back(i);
            }
        }

        return result;
    }
};
