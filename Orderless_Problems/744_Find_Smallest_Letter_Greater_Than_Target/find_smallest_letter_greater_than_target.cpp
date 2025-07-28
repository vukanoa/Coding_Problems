/*
    ============
    === EASY ===
    ============

    =============================================
    744) Find Smallest Letter Greater Than Target
    =============================================

    ============
    Description:
    ============

    You are given an array of characters letters that is sorted in
    non-decreasing order, and a character target. There are at least two
    different characters in letters.

    Return the smallest character in letters that is lexicographically greater
    than target. If such a character does not exist, return the first character
    in letters.

    ======================================================================
    FUNCTION: char nextGreatestLetter(vector<char>& letters, char target);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: letters = ["c","f","j"], target = "a"
    Output: "c"
    Explanation: The smallest character that is lexicographically greater than
    'a' in letters is 'c'.


    --- Example 2 ---
    Input: letters = ["c","f","j"], target = "c"
    Output: "f"
    Explanation: The smallest character that is lexicographically greater than
    'c' in letters is 'f'.


    --- Example 3 ---
    Input: letters = ["x","x","y","y"], target = "z"
    Output: "x"
    Explanation: There are no characters in letters that is lexicographically
    greater than 'z' so we return letters[0].


    *** Constraints ***
    2 <= letters.length <= 10^4
    letters[i] is a lowercase English letter.
    letters is sorted in non-decreasing order.
    letters contains at least two different characters.
    target is a lowercase English letter.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Upper-bound is "If you were to insert number "target"(letter in this
    problem), before which number(letter) would you do it in this vector?"

    Example:
    ['a', 'b', 'b', 'c', 'd', 'e', 'e', 'g', 'z']

    If we wanted to insert "f", before which character, in the given vector,
    would we do it?

    Obviously it's right before the first(and only) occurrence of 'g'.

    So since we want to find lexicographically the smallest letter that is
    greater than target, then we just need to perform the "upper:bound"
    functionality.

    In the code we also have to substract "letter.begin()" so that we can index
    the letter. We also must mod with letter.size() if the upper::bound tends
    to be outside of the vector, i.e. letters.end().

*/

/* Time  Beats: 84.63% */
/* Space Beats: 52.69% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1) */
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target)
    {
        return letters[(upper_bound(letters.begin(), letters.end(), target) - letters.begin()) % letters.size()];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Manually written Binary Search. It's really handy to really undertand
    how it all works "under the hood".

    You should know how to write Binary Search properly without errors.
    It is NOT trivial.

*/
/* Time  Beats: 100.00% */
/* Space Beats:  87.82% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1) */
class Solution_Binary_Search {
public:
    char nextGreatestLetter(vector<char>& letters, char target) 
    {
        const int N = letters.size();

        int low  = 0;
        int high = N-1;

        int idx = -1;

        while (low <= high) 
        {
            int mid = low + (high - low) / 2;

            if (letters[mid] <= target)
                low = mid + 1;
            else 
            {
                high = mid - 1;
                idx  = high + 1;
            }
        }

        return idx == -1 ? letters[0] : letters[idx];
    }
};
