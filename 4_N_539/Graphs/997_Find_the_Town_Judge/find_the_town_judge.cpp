#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    997) Find The Town Judge
    ===========================

    ============
    Description:
    ============

    In a town, there are n people labeled from 1 to n. There is a rumor that
    one of these people is secretly the town judge.

    If the town judge exists, then:

        + The town judge trusts nobody.

        + Everybody (except for the town judge) trusts the town judge.
          There is exactly one person that satisfies properties 1 and 2.

    You are given an array trust where trust[i] = [ai, bi] representing that
    the person labeled ai trusts the person labeled bi. If a trust relationship
    does not exist in trust array, then such a trust relationship does not
    exist.

    Return the label of the town judge if the town judge exists and can be
    identified, or return -1 otherwise.

    ===========================================================
    FUNCTION: int findJudge(int n, vector<vector<int>>& trust);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, trust = [[1,2]]
    Output: 2

    --- Example 2 ---
    Input: n = 3, trust = [[1,3],[2,3]]
    Output: 3

    --- Example 3 ---
    Input: n = 3, trust = [[1,3],[2,3],[3,1]]
    Output: -1


    *** Constraints ***
    1 <= n <= 1000
    0 <= trust.length <= 10^4
    trust[i].length == 2
    All the pairs of trust are unique.
    ai != bi
    1 <= ai, bi <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    Count:
        1. indegree  (i.e. "num_of_people_who_trust_person") and
        2. outdegree (i.e. "trusts_of_person")

    of each person(i.e. node) in this Graph. It's a graph problem if you
    haven't noticed.
    (Any time there are "relationships", chances are it's a Graph problem and
     that Input variables represent some sort of Graph)

    Afterwards go through those two lists(which are of the same size) and check
    if there is a person who has an indegree of n-1(meaning everyone, except
    his own self, trust him) and if that person exists check if he has an
    outdegree of 0(he does NOT trust anybody).

*/

/* Time  Beats: 52.52% */
/* Space Beats: 86.09% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust)
    {
        if (n == 1)
            return trust.empty() ? 1 : -1;

        vector<int> num_of_people_who_trust_person(n+1, 0);
        vector<int> trusts_of_person(n+1, 0);

        for (const auto& entry : trust)
        {
            trusts_of_person[entry[0]]++;
            num_of_people_who_trust_person[entry[1]]++;
        }

        for (int i = 0; i < n+1; i++)
        {
            if (num_of_people_who_trust_person[i] == n-1 && trusts_of_person[i] == 0)
                return i;
        }

        return -1;
    }
};
