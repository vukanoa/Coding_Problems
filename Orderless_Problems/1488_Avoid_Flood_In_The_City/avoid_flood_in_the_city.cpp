/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1488) Avoid Flood in The City
    =============================

    ============
    Description:
    ============

    Your country has an infinite number of lakes. Initially, all the lakes are
    empty, but when it rains over the nth lake, the nth lake becomes full of
    water. If it rains over a lake that is full of water, there will be a
    flood. Your goal is to avoid floods in any lake.

    Given an integer array rains where:

        + rains[i] > 0 means there will be rains over the rains[i] lake.

        + rains[i] == 0 means there are no rains this day and you can choose
          one lake this day and dry it.

    Return an array ans where:

        + ans.length == rains.length
        + ans[i] == -1 if rains[i] > 0.
        + ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.

    If there are multiple valid answers return any of them. If it is impossible
    to avoid flood return an empty array.

    Notice that if you chose to dry a full lake, it becomes empty, but if you
    chose to dry an empty lake, nothing changes.

    =====================================================
    FUNCTION: vector<int> avoidFlood(vector<int>& rains);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rains = [1,2,3,4]
    Output: [-1,-1,-1,-1]
    Explanation: After the first day full lakes are [1]
    After the second day full lakes are [1,2]
    After the third day full lakes are [1,2,3]
    After the fourth day full lakes are [1,2,3,4]
    There's no day to dry any lake and there is no flood in any lake.

    --- Example 2 ---
    Input: rains = [1,2,0,0,2,1]
    Output: [-1,-1,2,1,-1,-1]
    Explanation: After the first day full lakes are [1]
    After the second day full lakes are [1,2]
    After the third day, we dry lake 2. Full lakes are [1]
    After the fourth day, we dry lake 1. There is no full lakes.
    After the fifth day, full lakes are [2].
    After the sixth day, full lakes are [1,2].
    It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.

    --- Example 3 ---
    Input: rains = [1,2,0,1,2]
    Output: []
    Explanation: After the second day, full lakes are  [1,2]. We have to dry
                 one lake in the third day. After that, it will rain over lakes
                 [1,2]. It's easy to prove that no matter which lake you choose
                 to dry in the 3rd day, the other one will flood.


    *** Constraints ***
    1 <= rains.length <= 10^5
    0 <= rains[i] <= 10^9

*/

#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.76% */
/* Space Beats: 24.52% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains)
    {
        vector<int> result; // Store the final answer here.
        const int N = rains.size(); 

        // Lake number -> day on which it became full.
        unordered_map<int, int> full_lakes;

        // Set of available days that can be used for drying a full lake.
        set<int> drydays;

        for (int i = 0; i < N; i++)
        {
            if (rains[i] == 0)
            {
                drydays.insert(i);
                result.push_back(1);
            }
            else
            {
                int lake = rains[i]; 
                if (full_lakes.find(lake) != full_lakes.end())
                {
                    auto it = drydays.lower_bound(full_lakes[lake]);
                    if (it == drydays.end())
                        return {};

                    int dryday = *it;
                    result[dryday] = lake;
                    drydays.erase(dryday);
                }

                full_lakes[lake] = i;
                result.push_back(-1);
            }
        }

        return result;
    }
};
