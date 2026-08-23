/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    4008) Minimum Initial Strength to Defeat All Monsters
    =====================================================

    ============
    Description:
    ============

    You are given an integer array monsters, where monsters[i] represents the
    strength of the ith monster.

    You are also given a 2D integer array boosts, where boosts[i] = [li, ri,
    vi] indicates that vi is added to your temporary bonus while fighting any
    monster whose index lies in [li, ri]. Boost ranges may overlap, and the
    values of all applicable boosts are added together.

    You start with a non-negative initial strength and fight the monsters from
    left to right.

    For each monster at index i:

        + Let bonus be the sum of the values of all boosts that apply to
          monster i.

        + You can defeat the monster only if your current strength plus bonus
          is at least monsters[i].

        + After defeating the monster, only your current strength decreases by
          monsters[i]. If it becomes negative, it is set to 0.

    Return the minimum initial strength required to defeat all monsters.

    =====
    Note: The temporary bonus is used only to determine whether the current
          monster can be defeated. It does not otherwise change your current
          strength. 
    =====

    ===========================================================================================
    FUNCTION: long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: monsters = [5,10,15], boosts = [[1,1,10]]
    Output: 30
    Explanation:
    Let's start with an initial strength of 30.
        monsters[0] = 5: At index 0, the bonus is 0. Since 30 + 0 >= 5, this monster can be defeated. The strength becomes 30 - 5 = 25.
        monsters[1] = 10: At index 1, the bonus is 10. Since 25 + 10 >= 10, this monster can be defeated. The strength becomes 25 - 10 = 15.
        monsters[2] = 15: At index 2, the bonus is 0. Since 15 + 0 >= 15, this monster can be defeated. The strength becomes 15 - 15 = 0.
    Thus, the minimum initial strength required is 30.

    --- Example 2 ---
    Input: monsters = [5,10,15], boosts = [[1,2,10],[1,2,5]]
    Output: 5
    Explanation:
    Let's start with an initial strength of 5.
        monsters[0] = 5: The bonus is 0. Since 5 + 0 >= 5, the monster can be defeated. The strength becomes 5 - 5 = 0.
        monsters[1] = 10: The two overlapping boosts provide bonus = 10 + 5 = 15. Since 0 + 15 >= 10, the monster can be defeated. The strength remains 0.
        monsters[2] = 15: The two overlapping boosts again provide bonus = 15. Since 0 + 15 >= 15, the monster can be defeated. The strength remains 0.
    Thus, the minimum initial strength required is 5.


    *** Constraints ***
    1 <= monsters.length <= 5 * 10^4
    1 <= monsters[i] <= 10^9
    0 <= boosts.length <= 5 * 10^4
    boosts[i] == [li, ri, vi]
    0 <= li <= ri < monsters.length
    1 <= vi <= 10^9

*/

#include <climits>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.08% */
/* Space Beats: 74.19% */

/* Time  Complexity: O(M  +  N * log(LLONG_MAX)) */
/* Space Complexity: O(N)                        */
class Solution {
public:
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts)
    {
        const int N = monsters.size();
        const int M = boosts.size();

        vector<long long> sweep_line(N+1, 0LL);
        for (const vector<int>& boost : boosts)
        {
            const int& l = boost[0];
            const int& r = boost[1];
            const int& v = boost[2];

            sweep_line[l]   += v;
            sweep_line[r+1] -= v;
        }

        long long total_sum = accumulate(monsters.begin(), monsters.end(), 0LL);

        long long low  = 0; // Non-negative initial strength
        long long high = LLONG_MAX;

        while (low < high)
        {
            long long mid = 1LL * low + (high - low) / 2; // Low-leaning mid

            if ( ! can_defeat_all_monsters(mid, monsters, sweep_line))
                low  = mid + 1;
            else
                high = mid;
        }

        return low; // Or "high" it does NOT matter since they're equal here.
    }

private:
    bool can_defeat_all_monsters(long long power, vector<int>& monsters, vector<long long>& sweep_line)
    {
        const int N = monsters.size();

        long long curr_bonus = 0LL;
        for (int i = 0; i < N; i++)
        {
            curr_bonus += sweep_line[i];

            if ((power + curr_bonus) < monsters[i])
                return false;

            power -= monsters[i];

            if (power < 0)
                power = 0;
        }

        return true;
    }
};
