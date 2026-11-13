/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    2910) Minimum Number of Groups to Create a Valid Assignment
    ===========================================================

    ============
    Description:
    ============

    You are given a collection of numbered balls and instructed to sort them
    into boxes for a nearly balanced distribution. There are two rules you must
    follow:

        + Balls with the same box must have the same value. But, if you have
          more than one ball with the same number, you can put them in
          different boxes.

        + The biggest box can only have one more ball than the smallest box.

    Return the fewest number of boxes to sort these balls following these
    rules.

    ==============================================================
    FUNCTION: int minGroupsForValidAssignment(vector<int>& balls);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: balls = [3,2,3,2,3]
    Output: 2
    Explanation:
    We can sort balls into boxes as follows:
        [3,3,3]
        [2,2]
    The size difference between the two boxes doesn't exceed one.


    --- Example 2 ---
    Input: balls = [10,10,10,3,1,1]
    Output: 4
    Explanation:
    We can sort balls into boxes as follows:
        [10]
        [10,10]
        [3]
        [1,1]
    You can't use fewer than four boxes while still following the rules. For
    example, putting all three balls numbered 10 in one box would break the
    rule about the maximum size difference between boxes.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.66% */
/* Space Beats: 55.46% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& balls)
    {
        unordered_map<int, int> freq;
        for (const int& val : balls)
            ++freq[val];

        int smallest_box = INT_MAX;
        for (const auto& [val, frequency] : freq)
            smallest_box = min(smallest_box, frequency);

        for (int box_size = smallest_box; box_size >= 1; box_size--)
        {
            int result = 0;

            bool valid = true;
            for (const auto& [val, frequency] : freq)
            {
                int boxes = (frequency + box_size) / (box_size + 1);

                if (boxes * box_size > frequency)
                {
                    valid = false;
                    break;
                }

                result += boxes;
            }

            if (valid)
                return result;
        }

        return -1;
    }
};
