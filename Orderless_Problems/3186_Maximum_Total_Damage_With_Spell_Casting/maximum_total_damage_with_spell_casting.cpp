/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3186) Maximum Total Damage With Spell Casting
    =============================================

    ============
    Description:
    ============

    A magician has various spells.

    You are given an array power, where each element represents the damage of a
    spell. Multiple spells can have the same damage value.

    It is a known fact that if a magician decides to cast a spell with a damage
    of power[i], they cannot cast any spell with a damage of:

        power[i] - 2,
        power[i] - 1,
        power[i] + 1, or
        power[i] + 2.

    Each spell can be cast only once.

    Return the maximum possible total damage that a magician can cast.

    ===========================================================
    FUNCTION: long long maximumTotalDamage(vector<int>& power);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: power = [1,1,3,4]
    Output: 6
    Explanation:
    The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.

    --- Example 2 ---
    Input: power = [7,1,6,6]
    Output: 13
    Explanation:
    The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.


    *** Constraints ***
    1 <= power.length <= 10^5
    1 <= power[i] <= 10^9

*/

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    THis is almost to-a-T exactly the same problem as:

        LeetCode 760 "Delete and Earn"

    The only difference is the in "Delete and Earn" you have to worry only
    about one below and one above, whereas here you have to worry one more down
    and one more up.

    That's it. And, of course, the wording and the story is different.

    But you're being asked to do the same thing and it's done in the exact same
    way.

    If you do not understand that, please go and learn that one first.
    This technique in DP is so cmmon that it's considered a DP of its own type,
    called literally "Delete and Earn".

    That's how fundamental it is.

*/

/* Time  Beats: 12.27% */
/* Space Beats:  8.18% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power)
    {
        const int N = power.size();
        long long result = 0;

        unordered_map<int,int> counter;
        for (int i = 0; i < N; i++)
            counter[power[i]]++;

        unordered_set<int> unique(power.begin(), power.end());

        vector<int> sorted_uniq(unique.begin(), unique.end());
        sort(sorted_uniq.begin(), sorted_uniq.end());

        vector<int> vec_unique(2, -1000);
        vector<long long> dp(2, 0);

        vec_unique.insert(vec_unique.end(), sorted_uniq.begin(), sorted_uniq.end());

        dp.push_back(1LL * sorted_uniq[0] * counter[sorted_uniq[0]]);

        for (int i = 3; i < vec_unique.size(); i++)
        {
            int curr_power = vec_unique[i];

            long long max_possible_so_far;
            long long curr_addition;
            long long now;

            if (counter.find(curr_power - 2) == counter.end() &&
                counter.find(curr_power - 1) == counter.end())
            {
                max_possible_so_far = max({dp[i-3], dp[i-2], dp[i-1]});
                curr_addition       = curr_power * counter[curr_power];

                now = max_possible_so_far + curr_addition;
            }
            else
            {
                if (vec_unique[i-1] < curr_power - 2)
                {
                    max_possible_so_far = max({dp[i-3], dp[i-2], dp[i-1]});
                    curr_addition       = curr_power * counter[curr_power];

                    now = max_possible_so_far + curr_addition;
                }
                else if (vec_unique[i-2] < curr_power - 2)
                {
                    max_possible_so_far = max(dp[i-3], dp[i-2]);
                    curr_addition       = curr_power * counter[curr_power];

                    now = max_possible_so_far + curr_addition;
                }
                else
                {
                    max_possible_so_far = dp[i-3];
                    curr_addition       = curr_power * counter[curr_power];

                    now = max_possible_so_far + curr_addition;
                }
            }

            dp.push_back( max(now, dp[i-1]));
        }

        return *max_element(dp.begin(), dp.end());
    }
};
