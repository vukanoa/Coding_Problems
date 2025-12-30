/*
    ============
    === HARD ===
    ============

    ==============================
    1125) Smallest Sufficient Team
    ==============================

    ============
    Description:
    ============

    In a project, you have a list of required skills req_skills, and a list of
    people. The ith person people[i] contains a list of skills that the person
    has.

    Consider a sufficient team: a set of people such that for every required
    skill in req_skills, there is at least one person in the team who has that
    skill. We can represent these teams by the index of each person.

        + For example, team = [0, 1, 3] represents the people with skills
          people[0], people[1], and people[3].

    Return any sufficient team of the smallest possible size, represented by
    the index of each person. You may return the answer in any order.

    It is guaranteed an answer exists.

    =========================================================================================================
    FUNCTION: vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people);
    =========================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
    Output: [0,2]

    --- Example 2 ---
    Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
    people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
    Output: [1,2]


    *** Constraints ***
    1 <= req_skills.length <= 16
    1 <= req_skills[i].length <= 16
    req_skills[i] consists of lowercase English letters.
    All the strings of req_skills are unique.
    1 <= people.length <= 60
    0 <= people[i].length <= 16
    1 <= people[i][j].length <= 16
    people[i][j] consists of lowercase English letters.
    All the strings of people[i] are unique.
    Every skill in people[i] is a skill in req_skills.
    It is guaranteed a sufficient team exists.

*/

#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.33% */
/* Space Beats: 61.16% */

/* Time  Complexity: O(N * 2^M) */
/* Space Complexity: O(N)       */
class Solution {
public:
    vector<int> result;

    int memo[61][1 << 16];

    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people)
    {
        int skill_count  = req_skills.size();
        int people_count = people.size();

        unordered_map<string, int> skill_to_bit;

        for (int i = 0; i < skill_count; ++i)
            skill_to_bit[req_skills[i]] = 1 << i;

        vector<int> people_skill;
        for (const auto& person : people)
        {
            int mask = 0;

            for (const string& skill : person)
            {
                if (skill_to_bit.count(skill))
                    mask |= skill_to_bit[skill];
            }

            people_skill.push_back(mask);
        }

        /* Memset */
        memset(memo, -1, sizeof(memo)); // -1 <==> 0xff, in 2's complement

        vector<int> curr_team;
        solve(0, 0, skill_count, curr_team, people_skill);

        return result;
    }

private:
    void solve(int person_index, int curr_mask, int skill_count, vector<int>& curr_team, vector<int>& people_skill)
    {
        if (person_index == people_skill.size())
        {
            if (curr_mask == ((1 << skill_count) - 1))
            {
                if (result.empty() || curr_team.size() < result.size())
                    result = curr_team;
            }

            return;
        }

        if (memo[person_index][curr_mask] != -1 &&
            memo[person_index][curr_mask] <= curr_team.size())
        {
            return;
        }

        // Skip
        solve(person_index + 1, curr_mask, skill_count, curr_team, people_skill);

        // Take
        curr_team.push_back(person_index);
        solve(person_index + 1, curr_mask | people_skill[person_index], skill_count, curr_team, people_skill);
        curr_team.pop_back();

        memo[person_index][curr_mask] = curr_team.size();
    }
};
