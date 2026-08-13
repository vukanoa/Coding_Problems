/*
    ============
    === HARD ===
    ============

    ==================================================
    2213) Longest Substring of One Repeating Character
    ==================================================

    ============
    Description:
    ============

    You are given a 0-indexed string s. You are also given a 0-indexed string
    queryCharacters of length k and a 0-indexed array of integer indices
    queryIndices of length k, both of which are used to describe k queries.

    The ith query updates the character in s at index queryIndices[i] to the
    character queryCharacters[i].

    Return an array lengths of length k where lengths[i] is the length of the
    longest substring of s consisting of only one repeating character after the
    ith query is performed.

    ====================================================================================================
    FUNCTION: vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices);
    ====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
    Output: [3,3,4]
    Explanation: 
    - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
    - 2nd query updates s = "bbbccc". 
      The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
    - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
    Thus, we return [3,3,4].

    --- Example 2 ---
    Input: s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
    Output: [2,3]
    Explanation:
    - 1st query updates s = "abazz". The longest substring consisting of one repeating character is "zz" with length 2.
    - 2nd query updates s = "aaazz". The longest substring consisting of one repeating character is "aaa" with length 3.
    Thus, we return [2,3].



    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.
    k == queryCharacters.length == queryIndices.length
    1 <= k <= 10^5
    queryCharacters consists of lowercase English letters.
    0 <= queryIndices[i] < s.length

*/

#include <map>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 6.71% */
/* Space Beats: 5.37% */

/* Time  Complexity: O(N  +  K * logN) */
/* Space Complexity: O(N)              */
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        const int N = s.size();
        const int K = queryCharacters.size();
        vector<int> result(K, 0);


        vector<map<int,int>> startings(26, map<int,int>()); // {start, end  }
        vector<map<int,int>> endings  (26, map<int,int>()); // {end  , start}

        map<int, map<char,int>, greater<int>> longest;

        int L = 0;
        int R = 1;

        while (R <= N)
        {
            if (R == N || s[R-1] != s[R]) // (R == N) processes the "tail"
            {
                int length = (R-1) - L + 1;
                int letter = s[L];

                startings[letter - 'a'].insert( {L  , R-1} );
                endings  [letter - 'a'].insert( {R-1, L  } );

                longest[length][letter]++;

                L = R;
            }

            // Increment
            R++;
        }

        for (int query_idx = 0; query_idx < K; query_idx++)
        {
            int new_letter = queryCharacters[query_idx];
            int idx        = queryIndices[query_idx];

            if (s[idx] == new_letter)
            {
                result[query_idx] = longest.begin()->first;
                continue;
            }

            char old_letter = s[idx];

            /* Old Interval */
            auto old_start = startings[old_letter - 'a'].upper_bound(idx);
            --old_start;

            int old_L = old_start->first;
            int old_R = old_start->second;
            int old_length = old_R - old_L + 1;

            /* Remove OLD Interval from longest */
            --longest[old_length][old_letter];
            if (longest[old_length][old_letter] == 0)
                longest[old_length].erase(old_letter);
            if (longest[old_length].empty())
                longest.erase(old_length);

            /* Remove OLD Interval */
            endings  [old_letter - 'a'].erase(old_R);
            startings[old_letter - 'a'].erase(old_start);


            /* Insert LEFT Interval */
            if (old_L < idx)
            {
                int left_length = idx - old_L;

                startings[old_letter - 'a'].insert( {old_L, idx-1} );
                endings  [old_letter - 'a'].insert( {idx-1, old_L} );

                longest[left_length][old_letter]++;
            }

            /* Insert RIGHT Interval */
            if (idx < old_R)
            {
                int right_length = old_R - idx;

                startings[old_letter - 'a'].insert( {idx+1, old_R} );
                endings  [old_letter - 'a'].insert( {old_R, idx+1} );

                longest[right_length][old_letter]++;
            }


            s[idx] = new_letter;

            bool has_left  = (idx-1) >= 0 && s[idx-1] == new_letter;
            bool has_right = (idx+1) < N  && s[idx+1] == new_letter;

            int new_L = idx;
            int new_R = idx;

            /* Left Interval */
            if (has_left)
            {
                auto left_start = startings[new_letter - 'a'].upper_bound(idx-1);
                --left_start;

                int left_L = left_start->first;
                int left_R = left_start->second;
                int left_length = left_R - left_L + 1;

                new_L = left_L;

                --longest[left_length][new_letter];
                if (longest[left_length][new_letter] == 0)
                    longest[left_length].erase(new_letter);
                if (longest[left_length].empty())
                    longest.erase(left_length);

                endings[new_letter - 'a'].erase(left_R);
                startings[new_letter - 'a'].erase(left_start);
            }

            /* Right Interval */
            if (has_right)
            {
                auto right_start = startings[new_letter - 'a'].lower_bound(idx+1);

                int right_L = right_start->first;
                int right_R = right_start->second;
                int right_length = right_R - right_L + 1;

                new_R = right_R;

                --longest[right_length][new_letter];
                if (longest[right_length][new_letter] == 0)
                    longest[right_length].erase(new_letter);
                if (longest[right_length].empty())
                    longest.erase(right_length);

                endings  [new_letter - 'a'].erase(right_R);
                startings[new_letter - 'a'].erase(right_start);
            }

            /* Insert NEW Interval */
            int new_length = new_R - new_L + 1;

            startings[new_letter - 'a'].insert( {new_L, new_R} );
            endings  [new_letter - 'a'].insert( {new_R, new_L} );

            ++longest[new_length][new_letter];

            result[query_idx] = longest.begin()->first;
        }

        return result;
    }
};
