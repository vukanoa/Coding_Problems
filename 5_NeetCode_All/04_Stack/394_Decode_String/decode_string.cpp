/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    394) Decode String
    ===========================

    ============
    Description:
    ============

    Given an encoded string, return its decoded string.

    The encoding rule is: k[encoded_string], where the "encoded_string" inside
    the square brackets is being repeated exactly 'k' times. Note that 'k' is
    guaranteed to be a positive integer.

    You may assume that the input string is always valid; there are no extra
    white spaces, square brackets are well-formed, etc. Furthermore, you may
    assume that the original data does not contain any digits and that digits
    are only for those repeat numbers, 'k'. For example, there will not be
    input like 3a or 2[4].

    The test cases are generated so tha the length of the output will never
    exceed 10^5.

    ========================================
    FUNCTION: string decodeString(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "3[a]2[bc]"
    Output: "aaabcbc"

    --- Example 2 ---
    Input:  s = "3[a2[c]]"
    Output: "accaccacc"

    --- Example 3 ---
    Input:  s = "2[abc]3[cd]ef"
    Output: "abcabccdcdcdef

    *** Constraints ***
    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in 's' are in the range [1, 300].

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only "problematic" scenarios in this problem are 2 cases:
    k[k[k[]]]
        and
    k[k[]k[]k[]]

    It could be done using recursion, as we have already did in the above
    solution, however, we could do it using a stack, as well.

    Consider this example:
    54[ab6[cd]]

    Let's go character by character:

    1)
    54[ab6[cd]]
    #

    Stack:
    {5 |   |   |   |   |   |   |   |   }
    {5 | 4 |   |   |   |   |   |   |   }
    {5 | 4 | [ |   |   |   |   |   |   }
    {5 | 4 | [ | a |   |   |   |   |   }
    {5 | 4 | [ | a | b |   |   |   |   }
    {5 | 4 | [ | a | b | 6 |   |   |   }
    {5 | 4 | [ | a | b | 6 | [ |   |   }
    {5 | 4 | [ | a | b | 6 | [ | c | d }
    // First ']' closed bracket detected

    Now we're going to pop from our stack into our string "substr" like this:
        substr = stack.back() + substr;
    Since we want the right order.

    We pop until we get to an opening bracket '['. (We are sure there is at
    least one since we're told that the string input will always be valid. So
    If we had stumbled upon a closing bracket ']' then we're sure that an
    opening bracket '[' is already in our stack).

    After the while loop we pop once more, to get rid of the opening bracket
    '[' itself.

    Now we have the substring "cd". What do we want to do with it?
    Now that we have popped an opening bracket '[' as well, we have to pop
    digits until we get to a non digit character or until we get to the
    beginning of the string and then convert that number in our string 'k' and
    then multiply our substring "cd" exactly k numbers.

    The stack should look like this:

    {5 | 4 | [ | a | b                 }

    k = "6" // We have to convert a string to integer

    By multiplying it is meant that we push that substring into the stack
    exactly k times.

    So our stack now looks like this:

    {5 | 4 | [ | a | b | c | d | c | d | c | d | c | d | c | d | c | d }
                        ----------------------------------------------
                                     cd cd cd cd cd cd

    And then we do the outer problem by continuing to iterate through our
    while loop.

    The outer problem is now: 54[abcdcdcdcdcdcd]

    At the end we will have "abcdcdcdcdcdcd" repeated 54 times and put in our
    string "stack".

    We just return that.

    There was a minor issue with this problem. It is said that the string will
    always be valid, however 54-th Input was just "3".

    So I've added:
        if (isdigit(stack.back()))
            return "";

    To overcome that.
*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string decodeString(string s)
    {
        string result;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ']')
            {
                string decoded_substr;
                while (result.back() != '[')
                {
                    decoded_substr = result.back() + decoded_substr;
                    result.pop_back();
                }
                result.pop_back(); // Pop the '['

                string repeat_count_str;
                while ( ! result.empty() && isdigit(result.back()))
                {
                    repeat_count_str = result.back() + repeat_count_str;
                    result.pop_back();
                }

                int repeat_count = stoi(repeat_count_str);

                while (repeat_count-- > 0)
                    result += decoded_substr;
            }
            else
            {
                result += s[i];
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA as above, implemented differently.

    It uses:
        substr.insert(0, 1, stack.back());

    instead of:
        substr = stack.back() + substr;


    substr.insert(0, 1, stack.back()) means "at offset 0,
                                             put 1 character,
                                             character is stack.back()"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // result is not EXTRA Space
class Solution_2 {
public:
    string decodeString(string s)
    {
        const int N = s.size();
        string result;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == ']')
            {
                string decoded_substr = "";
                while (result.back() != '[')
                {
                    decoded_substr.insert(0, 1, result.back());
                    result.pop_back();
                }
                result.pop_back(); // Pop '[' itself.

                string repeat_count_str;
                while ( ! result.empty() && isdigit(result.back()))
                {
                    repeat_count_str.insert(0, 1, result.back());
                    result.pop_back();
                }

                int repeat_count = stoi(repeat_count_str);

                while (repeat_count-- > 0)
                    result += decoded_substr;
            }
            else
            {
                result.push_back(s[i]);
            }
        }

        return result;
    }
};
