/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    443) String COmpression
    ===========================

    ============
    Description:
    ============

    Given an array of characters chars, compress it using the following
    algorithm:

    Begin with an empty string s. For each group of consecutive repeating
    characters in chars:

        + If the group's length is 1, append the character to s.

        + Otherwise, append the character followed by the group's length.

    The compressed string s should not be returned separately, but instead, be
    stored in the input character array chars. Note that group lengths that are
    10 or longer will be split into multiple characters in chars.

    After you are done modifying the input array, return the new length of the
    array.

    You must write an algorithm that uses only constant extra space.

    =====
    Note: The characters in the array beyond the returned length do not matter
          and should be ignored. 
    =====

    ============================================
    FUNCTION: int compress(vector<char>& chars);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: chars = ["a","a","b","b","c","c","c"]
    Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
    Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

    --- Example 2 ---
    Input: chars = ["a"]
    Output: Return 1, and the first character of the input array should be: ["a"]
    Explanation: The only group is "a", which remains uncompressed since it's a single character.

    --- Example 3 ---
    Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
    Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
    Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".


    *** Constraints ***
    1 <= chars.length <= 2000
    chars[i] is a lowercase English letter, uppercase English letter, digit, or
    symbol.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I wanted to write this sort of "messy" approach because it's common in:
        1. Sliding Window
        2. Compression Grouping
        3. Intervals
        4. ...

    it's common to need to "flush" the last group after the main loop.
    Like this:

        while (i < N)
        {
            if (chars[i] != chars[i - 1])
            {
                // process previous group
            }
            i++;
        }

        // process final group


    However, there's a nice little "trick" we can use to AVOID this.
    In this Solution we're NOT using it. We're writing it the old "messy" way.

    However in the Solution_2, there's this "Sentinel" trick that is handy to
    know.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.45% */

/* Time  Complexity: O(N + log_base_10(N)) --> O(N) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    int compress(vector<char>& chars)
    {
        const int N = chars.size();
        int result = 0;

        int start = 0;
        int size = 1;
        int i = 1;
        while (i < N)
        {
            if (chars[i-1] != chars[i])
            {
                if (size == 1)
                {
                    result++;
                    chars[start] = chars[i-1];
                    start++;
                }
                else
                {
                    string digits = to_string(size);
                    const int NUMBER_OF_DIGITS = digits.length();

                    // Letter + number_of_digits
                    result += 1 + NUMBER_OF_DIGITS;

                    chars[start] = chars[i-1];
                    start++;
                    for (unsigned x = 0; x < NUMBER_OF_DIGITS; x++)
                    {
                        chars[start] = digits[x];
                        start++;
                    }
                }

                size  = 1; // Reset
            }
            else
            {
                size++;
            }

            // Increment
            i++;
        }

        if (size == 1)
        {
            result++;
            chars[start] = chars[i-1];
            start++;
        }
        else
        {
            string digits = to_string(size);
            const int NUMBER_OF_DIGITS = digits.length();

            // Letter + number_of_digits
            result += 1 + NUMBER_OF_DIGITS;

            chars[start] = chars[i-1];
            start++;
            for (unsigned x = 0; x < NUMBER_OF_DIGITS; x++)
            {
                chars[start] = digits[x];
                start++;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Sentinel trick.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int compress(vector<char>& chars)
    {
        chars.push_back('\0'); // Add a sentinel that will NEVER match Input
        const int N = chars.size();
        int result = 0;

        int start = 0;
        int size = 1;
        int i = 1;
        while (i < N)
        {
            if (chars[i-1] != chars[i])
            {
                if (size == 1)
                {
                    result++;
                    chars[start] = chars[i-1];
                    start++;
                }
                else
                {
                    string digits = to_string(size);
                    const int NUMBER_OF_DIGITS = digits.length();

                    // Letter + number_of_digits
                    result += 1 + NUMBER_OF_DIGITS;

                    chars[start] = chars[i-1];
                    start++;
                    for (unsigned x = 0; x < NUMBER_OF_DIGITS; x++)
                    {
                        chars[start] = digits[x];
                        start++;
                    }
                }

                size  = 1; // Reset
            }
            else
            {
                size++;
            }

            // Increment
            i++;
        }

        chars.pop_back(); // Remove the "sentinel"

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Concise way of writing it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    int compress(vector<char>& chars)
    {
        const int N = chars.size();
        int result = 0;

        int i = 0;
        while (i < N)
        {
            int group_len = 1;
            while (i + group_len < N && chars[i + group_len] == chars[i])
                group_len++;

            chars[result++] = chars[i];
            if (group_len > 1)
            {
                for (const char& chr : to_string(group_len))
                    chars[result++] = chr;
            }
            i += group_len;
        }

        return result;
    }
};
