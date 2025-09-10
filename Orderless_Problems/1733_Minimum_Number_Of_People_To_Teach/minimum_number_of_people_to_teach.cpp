/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    1733) Minimum Number of People to Teach
    =======================================

    ============
    Description:
    ============

    On a social network consisting of m users and some friendships between
    users, two users can communicate with each other if they know a common
    language.

    You are given an integer n, an array languages, and an array friendships
    where:

        + There are n languages numbered 1 through n,

        + languages[i] is the set of languages the ith user knows, and

        + friendships[i] = [ui, vi] denotes a friendship between the users ui
          and vi.

    You can choose one language and teach it to some users so that all friends
    can communicate with each other. Return the minimum number of users you
    need to teach.

    =====
    Note: that friendships are not transitive, meaning if x is a friend of y
          and y is a friend of z, this doesn't guarantee that x is a friend of
          z.
    =====

    ========================================================================================================
    FUNCTION: int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships);
    ========================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
    Output: 1
    Explanation: You can either teach user 1 the second language or user 2 the
                 first language.

    --- Example 2 ---
    Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
    Output: 2
    Explanation: Teach the third language to users 1 and 3, yielding two users
                 to teach.


    *** Constraints ***
    2 <= n <= 500
    languages.length == m
    1 <= m <= 500
    1 <= languages[i].length <= n
    1 <= languages[i][j] <= n
    1 <= ui < vi <= languages.length
    1 <= friendships.length <= 500
    All tuples (ui, vi) are unique
    languages[i] contains only unique values

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Code is genuinely self-explanaory. Go through it once and I'm sure you'll
    understand it.

*/

/* Time  Beats: 22.35% */
/* Space Beats:  7.06% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M + N) */
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships)
    {
        unordered_set<int> users_without_common_language;

        for (auto friendship : friendships)
        {
            unordered_map<int, int> language_map;
            bool has_common_language = false;

            for (int language : languages[friendship[0] - 1])
                language_map[language] = 1;

            for (int language : languages[friendship[1] - 1])
            {
                if (language_map[language])
                {
                    has_common_language = true;
                    break;
                }
            }

            if ( ! has_common_language)
            {
                users_without_common_language.insert(friendship[0] - 1);
                users_without_common_language.insert(friendship[1] - 1);
            }
        }

        int max_shared_language_count = 0;
        vector<int> language_frequency(n + 1, 0);

        for (const auto& user : users_without_common_language)
        {
            for (int language : languages[user])
            {
                language_frequency[language]++;
                max_shared_language_count = max(max_shared_language_count, language_frequency[language]);
            }
        }

        return users_without_common_language.size() - max_shared_language_count;
    }
};
