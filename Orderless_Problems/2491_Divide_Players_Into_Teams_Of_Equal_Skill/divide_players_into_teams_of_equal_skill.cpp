#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2491) Divide Players Into Teams Of Equal Skill
    ==============================================

    ============
    Description:
    ============

    You are given a positive integer array skill of even length n where
    skill[i] denotes the skill of the ith player. Divide the players into n / 2
    teams of size 2 such that the total skill of each team is equal.

    The chemistry of a team is equal to the product of the skills of the
    players on that team.

    Return the sum of the chemistry of all the teams, or return -1 if there is
    no way to divide the players into teams such that the total skill of each
    team is equal.

    ======================================================
    FUNCTION: long long dividePlayers(vector<int>& skill);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: skill = [3,2,5,1,3,4]
    Output: 22
    Explanation:
    Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where
    each team has a total skill of 6.  The sum of the chemistry of all the
    teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.


    --- Example 2 ---
    Input: skill = [3,4]
    Output: 12
    Explanation:
    The two players form a team with a total skill of 7.
    The chemistry of the team is 3 * 4 = 12.


    --- Example 3 ---
    Input: skill = [1,1,2,3]
    Output: -1
    Explanation:
    There is no way to divide the players into teams such that the total skill
    of each team is equal.


    *** Constraints ***
    2 <= skill.length <= 10^5
    skill.length is even.
    1 <= skill[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.20% */
/* Space Beats: 20.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long dividePlayers(vector<int>& skill)
    {
        const int n = skill.size();
        int total = std::accumulate(skill.begin(), skill.end(), 0);

        if ((total % (n / 2)) != 0) // We cannot even group them in any way
            return -1;

        std::unordered_map<int, int> umap_counter;
        for (int i = 0; i < skill.size(); i++)
            umap_counter[skill[i]]++;

        long long result = 0;
        int target = total / (n / 2);

        for (const int& s : skill)
        {
            if (umap_counter[s] == 0) // We've already used that one to pair up
                continue;

            int diff = target - s;
            umap_counter[s]--; // We MUST decrement it here, because
                               // "diff" and "s" can be the same number

            if (umap_counter[diff] == 0)
                return -1;

            result += diff * s;
            umap_counter[diff]--;
        }

        return result;
    }
};
