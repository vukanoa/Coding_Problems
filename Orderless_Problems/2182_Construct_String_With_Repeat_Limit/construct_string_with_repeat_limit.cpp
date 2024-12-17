/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2182) Construct String With Repeat Limit
    ========================================

    ============
    Description:
    ============

    You are given a string s and an integer repeatLimit. Construct a new string
    repeatLimitedString using the characters of s such that no letter appears
    more than repeatLimit times in a row. You do not have to use all characters
    from s.

    Return the lexicographically largest repeatLimitedString possible.

    A string a is lexicographically larger than a string b if in the first
    position where a and b differ, string a has a letter that appears later in
    the alphabet than the corresponding letter in b. If the first
    min(a.length,b.length) characters do not differ, then the longer string is
    the lexicographically larger one.

    ================================================================
    FUNCTION: string repeatLimitedString(string s, int repeatLimit);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cczazcc", repeatLimit = 3
    Output: "zzcccac"
    Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
    The letter 'a' appears at most 1 time in a row.
    The letter 'c' appears at most 3 times in a row.
    The letter 'z' appears at most 2 times in a row.
    Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
    The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
    Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.


    --- Example 2 ---
    Input: s = "aababab", repeatLimit = 2
    Output: "bbabaa"
    Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa".
    The letter 'a' appears at most 2 times in a row.
    The letter 'b' appears at most 2 times in a row.
    Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
    The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
    Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row, so it is not a valid repeatLimitedString.


    *** Constraints ***
    1 <= repeatLimit <= s.length <= 10^5
    s consists of lowercase English letters.

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem should be solved in a natural, intuitive way. It's greedy.
    You start with 'z' and append as many as possible, then you move to the
    next one, but if 'z' is not 0, then only append 1 of that new character and
    get back to 'z'. Then do as much 'z' as possible and get to the next one.
    Again, if you are NOT done with 'z', only append one current character and
    get back to 'z'.

    Once you're finished with 'z', you're allowed to append as much as possible
    of the next character. And so on.

    There are, kind of, a lot of edge cases, so you do have to be careful. But
    the idea is not very difficult. If you read the code below, I'm sure it'll
    make sense.

*/

/* Time  Beats: 85.82% */
/* Space Beats:  7.11% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(k)     */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit)
    {
        ostringstream out;

        vector<int> freq(26, 0);

        for (const char& chr : s)
            freq[chr - 'a']++;

        int L = 25; // Start from the largest character
        int R = 25; // Start from the largest character

        while (L >= 0 && R >= 0)
        {
            if (freq[L] == 0)
            {
                if (R < L-1)
                    L = R;
                else
                    L--;

                continue;
            }

            // If there is a lexicographically greater character that isn't
            // finished, then output only ONE of current character and get back
            // to that lexicographically grater character. Do this until you're
            // done with it.
            if (L != R && freq[R] > 0)
            {
                out << (char)(L + 'a');
                freq[L]--;
                L = R;
                continue;
            }


            // Append as much as possible
            int times = min(repeatLimit, freq[L]);
            for (int i = 0; i < times; i++)
            {
                out << (char)(L + 'a');
                freq[L]--;
            }

            // Find next lexicographically greatest character with freq > 0
            while (R >= 0 && freq[R] == 0)
                R--;

            // Decrement(while-loop)
            L--;
        }

        return out.str();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA as above, but this is implemented in a slightly different way.

*/

/* Time  Beats: 71.14% */
/* Space Beats: 32.11% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(k)     */
class Solution_2 {
public:
    string repeatLimitedString(string s, int repeatLimit)
    {
        string result;
        vector<int> freq(26, 0);

        for (char ch : s)
            freq[ch - 'a']++;

        int L = 25; // Start from the largest character
        while (L >= 0)
        {
            if (freq[L] == 0)
            {
                L--;
                continue;
            }

            int use = min(freq[L], repeatLimit);
            result.append(use, 'a' + L);
            freq[L] -= use;

            if (freq[L] > 0)  // Need to add a smaller character
            {
                int R = L - 1;

                while (R >= 0 && freq[R] == 0)
                    R--;

                if (R < 0)
                    break;

                result.push_back('a' + R);
                freq[R]--;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of devising some weird Solution with a lot of edge cases, we can
    at least, a little bit easen it up by using Heap.

    This approach is indeed a bit faster. Both in terms of "real runtime" and
    a Big O notation.

*/

/* Time  Beats: 62.28% */
/* Space Beats: 25.74% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(k)        */
class Solution_3 {
public:
    string repeatLimitedString(string s, int repeatLimit)
    {
        unordered_map<char, int> freq;

        for (const char& chr : s)
            freq[chr]++;

        priority_queue<char> max_heap;
        for (auto& [chr, count] : freq)
            max_heap.push(chr);

        string result;

        while ( ! max_heap.empty())
        {
            char chr = max_heap.top();
            max_heap.pop();
            int count = freq[chr];

            int how_many = min(count, repeatLimit);
            result.append(how_many, chr);

            freq[chr] -= how_many;

            if (!max_heap.empty() && freq[chr] > 0)
            {
                char next_chr = max_heap.top();
                max_heap.pop();

                result.push_back(next_chr);
                freq[next_chr]--;

                if (freq[next_chr] > 0)
                    max_heap.push(next_chr);

                max_heap.push(chr);
            }
        }

        return result;
    }
};
