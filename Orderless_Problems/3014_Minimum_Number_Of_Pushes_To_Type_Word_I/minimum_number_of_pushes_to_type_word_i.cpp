/*
    ============
    === EASY ===
    ============

    =============================================
    3014) Minimum Number of Pushes to Type Word I
    =============================================

    ============
    Description:
    ============

    You are given a string word containing distinct lowercase English letters.

    Telephone keypads have keys mapped with distinct collections of lowercase
    English letters, which can be used to form words by pushing them. For
    example, the key 2 is mapped with ["a","b","c"], we need to push the key
    one time to type "a", two times to type "b", and three times to type "c" .

    It is allowed to remap the keys numbered 2 to 9 to distinct collections of
    letters. The keys can be remapped to any amount of letters, but each letter
    must be mapped to exactly one key. You need to find the minimum number of
    times the keys will be pushed to type the string word.

    Return the minimum number of pushes needed to type word after remapping the
    keys.

    An example mapping of letters to keys on a telephone keypad is given below.
    Note that 1, *, #, and 0 do not map to any letters.

    =========================================
    FUNCTION: int minimumPushes(string word);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcde"
    Output: 5
    Explanation: The remapped keypad given in the image provides the minimum cost.
    "a" -> one push on key 2
    "b" -> one push on key 3
    "c" -> one push on key 4
    "d" -> one push on key 5
    "e" -> one push on key 6
    Total cost is 1 + 1 + 1 + 1 + 1 = 5.
    It can be shown that no other mapping can provide a lower cost.

    --- Example 2 ---
    Input: word = "xycdefghij"
    Output: 12
    Explanation: The remapped keypad given in the image provides the minimum cost.
    "x" -> one push on key 2
    "y" -> two pushes on key 2
    "c" -> one push on key 3
    "d" -> two pushes on key 3
    "e" -> one push on key 4
    "f" -> one push on key 5
    "g" -> one push on key 6
    "h" -> one push on key 7
    "i" -> one push on key 8
    "j" -> one push on key 9
    Total cost is 1 + 2 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 = 12.
    It can be shown that no other mapping can provide a lower cost.


    *** Constraints ***
    1 <= word.length <= 26
    word consists of lowercase English letters.
    All letters in word are distinct.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumPushes(string word)
    {
        int n = word.size();
        int result = 0;
        int pushes = 1;

        if (n <= 8)
            return n;
        
        while (n > 0)
        {
            result += min(n, 8) * pushes;

            pushes++;
            n -= 8;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minimumPushes(string word)
    {
        const int N = word.size();
        int result = 0;

        for (int i = 0; i < N; i++)
            result += i / 8 + 1;

        return result;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    This approach is based on the same greedy strategy as above Solution_2.

    Instead of summing the number of key presses one by one, we can derive the
    answer directly using a mathematical formula.

    Let the length of the string word be N, and let

        m = floor((N−1) / 8) + 1

    denote the maximum number of key presses required for any letter.

    There are m−1 complete groups, each containing 8 letters. The letters in
    the i-th group require exactly i key presses, where:

        1 <= i <= m-1

    Therefore, these groups contribute:

        8 * m * (m-1) / 2   ==>   4 * m * (m-1)

    key presses in total.

    The remaining N − 8 * (m−1) letters each require exactly m key presses,
    contributing:

        (N  -  8 * (m-1)) * m

    key presses.
    Hence, the total number of key presses is:

        4 * m * (m-1) * (N  -  8 * (m-1)) * m

*/

/* Time  Beats: 100.00% */
/* Space Beats: 77.73% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    int minimumPushes(string word)
    {
        const int N = word.size();
        int m = (N-1) / 8 + 1;

        return 4*m*(m-1) + (N - 8*(m-1)) * m;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar to the above Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.81% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math_2 {
public:
    int minimumPushes(string word)
    {
        const int N = word.size();

        const int remaining_letters        = N % 8;
        const int complete_groups_of_eight = (N - remaining_letters) / 8;

        return (4 * complete_groups_of_eight + remaining_letters) * (complete_groups_of_eight + 1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Exactly the same as above, though implemented using bitwise operators.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.67% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    int minimumPushes(string word)
    {
        const int N = word.size();

        const int complete_groups_of_eight = N >> 3;
        const int remaining_letters        = N & 7;

        return ((complete_groups_of_eight << 2) + remaining_letters) * (complete_groups_of_eight + 1);
    }
};
