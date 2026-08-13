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

#include <climits>
#include <map>
#include <set>
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




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, written in a better way.

*/

/* Time  Beats: 18.79% */
/* Space Beats: 16.11% */

/* Time  Complexity: O(N  +  K * logN) */
/* Space Complexity: O(N)              */
class Solution_2 {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        const int N = s.size();
        const int K = queryCharacters.size();

        vector<int> result(K, 0);

        set<pair<int,int>> intervals;
        multiset<int> lengths;

        for (int L = 0; L < N;)
        {
            int R = L;

            while (R < N && s[R] == s[L])
                R++;

            intervals.insert( {L, R-1} );
            lengths.insert(R - L);

            L = R;
        }

        for (int query_idx = 0; query_idx < K; query_idx++)
        {
            int idx         = queryIndices[query_idx];
            char new_letter = queryCharacters[query_idx];

            if (s[idx] != new_letter)
            {
                /* Current Interval */
                auto current = intervals.upper_bound( {idx, INT_MAX} );
                --current;

                int L = current->first;
                int R = current->second;

                intervals.erase(current);
                lengths.erase(lengths.find(R - L + 1));


                /* Split LEFT Interval */
                if (L <= idx-1)
                {
                    intervals.insert( {L, idx-1} );
                    lengths.insert(idx - L);
                }

                /* Split RIGHT Interval */
                if (idx+1 <= R)
                {
                    intervals.insert( {idx+1, R} );
                    lengths.insert(R - idx);
                }


                int new_L = idx;
                int new_R = idx;


                /* Merge RIGHT Interval */
                auto right = intervals.lower_bound( {idx+1, 0} );

                if (right != intervals.end() && right->first == idx+1 && s[idx+1] == new_letter)
                {
                    lengths.erase(lengths.find(right->second - right->first + 1));
                    new_R = right->second;
                    intervals.erase(right);
                }


                /* Merge LEFT Interval */
                auto left = intervals.lower_bound( {idx, 0} );

                if (left != intervals.begin())
                {
                    --left;

                    if (left->second == idx-1 && s[idx-1] == new_letter)
                    {
                        lengths.erase(lengths.find(left->second - left->first + 1));
                        new_L = left->first;
                        intervals.erase(left);
                    }
                }

                /* Insert NEW Interval */
                intervals.insert( {new_L, new_R} );
                lengths.insert(new_R - new_L + 1);

                s[idx] = new_letter;
            }

            result[query_idx] = *lengths.rbegin();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same, but even better implementation.

*/

/* Time  Beats: 46.98% */
/* Space Beats: 19.46% */

/* Time  Complexity: O(N  +  K * logN) */
/* Space Complexity: O(N)              */
class Solution_3 {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        const int N = s.size();
        const int K = queryIndices.size();

        vector<int> result(K, 0);

        set<int> boundaries;
        set<int> lengths;
        vector<int> count(N + 1);

        auto add_length = [&](int length)
        {
            if (++count[length] == 1)
                lengths.insert(length);
        };

        auto remove_length = [&](int length)
        {
            if (--count[length] == 0)
                lengths.erase(length);
        };

        boundaries.insert(0);
        boundaries.insert(N);

        int L = 0;

        for (int R = 1; R < N; R++)
        {
            if (s[R-1] != s[R])
            {
                boundaries.insert(R);
                add_length(R - L);

                L = R;
            }
        }

        add_length(N - L);

        auto update = [&](int idx, bool insert_boundary)
        {
            if (insert_boundary)
            {
                auto iter = boundaries.lower_bound(idx);
                int next  = *iter;
                int prev  = *std::prev(iter);

                remove_length(next - prev);

                add_length(idx  - prev);
                add_length(next - idx);

                boundaries.insert(idx);
            }
            else
            {
                auto iter = boundaries.find(idx);
                int prev  = *std::prev(iter);
                int next  = *std::next(iter);

                remove_length(idx  - prev);
                remove_length(next - idx);

                add_length(next - prev);

                boundaries.erase(iter);
            }
        };



        for (int query_idx = 0; query_idx < K; query_idx++)
        {
            int idx         = queryIndices[query_idx];
            char new_letter = queryCharacters[query_idx];

            if (idx > 0)
            {
                bool old_boundary = s[idx-1] != s[idx];
                bool new_boundary = s[idx-1] != new_letter;

                if (old_boundary != new_boundary)
                    update(idx, new_boundary);
            }

            if (idx+1 < N)
            {
                bool old_boundary = s[idx]     != s[idx+1];
                bool new_boundary = new_letter != s[idx+1];

                if (old_boundary != new_boundary)
                    update(idx+1, new_boundary);
            }

            s[idx] = new_letter;

            result[query_idx] = *lengths.rbegin();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Segment Tree Implementation.

*/

/* Time  Beats: 58.39% */
/* Space Beats: 80.54% */

/* Time  Complexity: O(N  +  K * logN) */
/* Space Complexity: O(N)              */
class SegmentTree {
public:
    void construct_segment_tree(int idx,
                                int start,
                                int end,
                                string& s,
                                vector<int>& prefix,
                                vector<int>& suffix,
                                vector<int>& longest,
                                vector<char>& left_char,
                                vector<char>& right_char)
    {
        if (start == end)
        {
            prefix[idx]     = 1;
            suffix[idx]     = 1;
            longest[idx]    = 1;
            left_char[idx]  = s[start];
            right_char[idx] = s[start];

            return;
        }

        int mid = start + (end - start) / 2;

        // 0-indexed
        construct_segment_tree(2*idx + 1, start, mid, s,
                                                      prefix,
                                                      suffix,
                                                      longest,
                                                      left_char,
                                                      right_char);

        construct_segment_tree(2*idx + 2, mid+1, end, s,
                                                      prefix,
                                                      suffix,
                                                      longest,
                                                      left_char,
                                                      right_char);


        int left  = 2*idx + 1;
        int right = 2*idx + 2;

        int left_length  = mid - start + 1;
        int right_length = end - mid;

        left_char[idx]  = left_char[left];
        right_char[idx] = right_char[right];

        prefix[idx] = prefix[left];

        if (prefix[left] == left_length && right_char[left] == left_char[right])
            prefix[idx] = prefix[left] + prefix[right];

        suffix[idx] = suffix[right];

        if (suffix[right] == right_length && right_char[left] == left_char[right])
            suffix[idx] = suffix[right] + suffix[left];

        longest[idx] = max(longest[left], longest[right]);

        if (right_char[left] == left_char[right])
            longest[idx] = max(longest[idx], suffix[left] + prefix[right]);
    }


    void update_segment_tree(int idx,
                             int start,
                             int end,
                             int update_idx,
                             char new_letter,
                             vector<int>& prefix,
                             vector<int>& suffix,
                             vector<int>& longest,
                             vector<char>& left_char, vector<char>& right_char)
    {
        if (start == end)
        {
            prefix[idx]     = 1;
            suffix[idx]     = 1;
            longest[idx]    = 1;
            left_char[idx]  = new_letter;
            right_char[idx] = new_letter;

            return;
        }

        int mid = start + (end - start) / 2;

        // 0-indexed
        if (update_idx <= mid)
        {
            update_segment_tree(2*idx + 1, start, mid, update_idx,
                                                       new_letter,
                                                       prefix,
                                                       suffix,
                                                       longest,
                                                       left_char,
                                                       right_char);
        }
        else
        {
            update_segment_tree(2*idx + 2, mid+1, end, update_idx,
                                                       new_letter,
                                                       prefix,
                                                       suffix,
                                                       longest,
                                                       left_char,
                                                       right_char);
        }


        int left  = 2*idx + 1;
        int right = 2*idx + 2;

        int left_length  = mid - start + 1;
        int right_length = end - mid;

        left_char[idx]  = left_char[left];
        right_char[idx] = right_char[right];

        prefix[idx] = prefix[left];

        if (prefix[left] == left_length && right_char[left] == left_char[right])
        {
            prefix[idx] = prefix[left] + prefix[right];
        }

        suffix[idx] = suffix[right];

        if (suffix[right] == right_length && right_char[left] == left_char[right])
        {
            suffix[idx] = suffix[right] + suffix[left];
        }

        longest[idx] = max(longest[left], longest[right]);

        if (right_char[left] == left_char[right])
        {
            longest[idx] = max(longest[idx], suffix[left] + prefix[right]);
        }
    }
};

class Solution_Segment_Tree {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        const int N = s.size();
        const int K = queryCharacters.size();

        vector<int> prefix(4 * N);
        vector<int> suffix(4 * N);
        vector<int> longest(4 * N);

        vector<char> left_char (4 * N);
        vector<char> right_char(4 * N);

        SegmentTree seg_tree;

        seg_tree.construct_segment_tree(0, 0, N-1, s, prefix, suffix, longest, left_char, right_char);

        vector<int> result(K, 0);

        for (int query_idx = 0; query_idx < K; query_idx++)
        {
            int idx         = queryIndices[query_idx];
            char new_letter = queryCharacters[query_idx];

            seg_tree.update_segment_tree(0, 0, N-1, idx, new_letter, prefix, suffix, longest, left_char, right_char);

            result[query_idx] = longest[0];
        }

        return result;
    }
};
