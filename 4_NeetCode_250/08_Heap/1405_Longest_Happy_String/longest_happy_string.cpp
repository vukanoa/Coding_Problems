/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1405) Longest Happy String
    ===========================

    ============
    Description:
    ============

    A string s is called happy if it satisfies the following conditions:

        s only contains the letters 'a', 'b', and 'c'.
        s does not contain any of "aaa", "bbb", or "ccc" as a substring.
        s contains at most a occurrences of the letter 'a'.
        s contains at most b occurrences of the letter 'b'.
        s contains at most c occurrences of the letter 'c'.

    Given three integers a, b, and c, return the longest possible happy string.
    If there are multiple longest happy strings, return any of them. If there
    is no such string, return the empty string "".

    A substring is a contiguous sequence of characters within a string.

    ===========================================================
    FUNCTION: string longestDiverseString(int a, int b, int c);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = 1, b = 1, c = 7
    Output: "ccaccbcc"
    Explanation: "ccbccacc" would also be a correct answer.

    --- Example 2 ---
    Input: a = 7, b = 1, c = 0
    Output: "aabaa"
    Explanation: It is the only correct answer in this case.


    *** Constraints ***
    0 <= a, b, c <= 100
    a + b + c > 0

*/

#include <string>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you try to be greedy by appending more than a SINGLE letter per
    iteration, then consider this example:

        a = 0, b = 8, c = 11

    This is NOT    the longest string: "ccbbccbbccbbccbbcc"
    This is INDEED the longest stirng: "ccbccbbccbbccbbccbc"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  30.99% */

/* Time  Complexity: O(N * log3) ---> O(N) */
/* Space Complexity: O(3)        ---> O(1) */ // "result" is not EXTRA space
class Solutionqr {
public:
    string longestDiverseString(int a, int b, int c)
    {
        string result;
        result.reserve(a + b + c); // Prevent reallocations

        priority_queue<pair<int,char>> max_heap;

        if (a > 0) max_heap.push( {a, 'a'} );
        if (b > 0) max_heap.push( {b, 'b'} );
        if (c > 0) max_heap.push( {c, 'c'} );

        // O(N * log3) --> O(N)(entire block), where N is (a + b + c)
        while ( ! max_heap.empty())
        {
            auto [freq_one, chr_one] = max_heap.top();
            max_heap.pop(); // O(log3) --> O(1)

            if (result.size() >= 2 && result[result.size() - 2] == chr_one && result[result.size() - 1] == chr_one)
            {
                if (max_heap.empty())
                    break;

                auto [freq_two, chr_two] = max_heap.top();
                max_heap.pop(); // O(log3) --> O(1)

                result += chr_two;
                freq_two--;

                if (freq_two > 0)
                    max_heap.push( {freq_two, chr_two} ); // O(logN) --> O(1)

                max_heap.push( {freq_one, chr_one} ); // O(logN) --> O(1)
            }
            else
            {
                result += chr_one;
                freq_one--;

                if (freq_one > 0)
                    max_heap.push( {freq_one, chr_one} ); // O(logN)
            }
        }

        return result;
    }
};
