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

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Count:
        1. indegree
        2. outdegree

    of each person(i.e. node) in this Graph. It's a graph problem if you
    haven't noticed.
    (Any time there are "relationships", chances are it's a Graph problem and
     that Input variables represent some sort of Graph)

    Afterwards go through those two lists(which are of the same size) and check
    if there is a person who has an indegree of n-1(meaning everyone, except
    his own self, trust him) and if that person exists check if he has an
    outdegree of 0(he does NOT trust anybody).

*/

/* Time  Beats: 60.13% */
/* Space Beats: 35.66% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V)     */
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust)
    {
        vector<int> indegree (n+1);
        vector<int> outdegree(n+1);

        for (const auto& edge : trust)
        {
            const auto& from = edge[0]; // The one that trusts
            const auto& to   = edge[1]; // The one that is TRUSTED

            outdegree[from]++;
            indegree [to]++; // Because "to" is being TRUSTED
        }

        for (int i = 1; i < n+1; i++)
        {
            if (outdegree[i] == 0 && indegree[i] == n-1)
                return i;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can use one vector instead. A little bit less explicit, but saves a bit
    of Space.

    I believe in production, the above Solution is still prefferable because
    the save in space is not meaningful, however it's much more difficult to
    read and maintaing the code.

    But it's good to be aware that you can actually use a single vector.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.90% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V)     */
class Solution_2 {
public:
    int findJudge(int n, vector<vector<int>>& trust)
    {
        vector<int> delta (n+1);

        for (const auto& edge : trust)
        {
            const auto& from = edge[0]; // The one that trusts
            const auto& to   = edge[1]; // The one that is TRUSTED

            delta[from]--;
            delta[to]++;
        }

        for (int i = 1; i < n+1; i++)
        {
            if (delta[i] == n-1)
                return i;
        }

        return -1;
    }
};
