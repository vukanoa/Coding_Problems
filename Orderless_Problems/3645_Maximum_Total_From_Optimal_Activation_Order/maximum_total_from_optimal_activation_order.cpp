/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    3645) Maximum Total from Optimal Activation Order
    =================================================

    ============
    Description:
    ============

    You are given two integer arrays value and limit, both of length n.

    Initially, all elements are inactive. You may activate them in any order.

        + To activate an inactive element at index i, the number of currently
          active elements must be strictly less than limit[i].

        + When you activate the element at index i, it adds value[i] to the
          total activation value (i.e., the sum of value[i] for all elements
          that have undergone activation operations).

        + After each activation, if the number of currently active elements
          becomes x, then all elements j with limit[j] <= x become permanently
          inactive, even if they are already active.

    Return the maximum total you can obtain by choosing the activation order
    optimally.

    =====================================================================
    FUNCTION: long long maxTotal(vector<int>& value, vector<int>& limit);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: value = [3,5,8], limit = [2,1,3]
    Output: 16

    --- Example 2 ---
    Input: value = [4,2,6], limit = [1,1,1]
    Output: 6

    --- Example 3 ---
    Input: value = [4,1,5,2], limit = [3,3,2,3]
    Output: 12


    *** Constraints ***
    1 <= n == value.length == limit.length <= 10^5
    1 <= value[i] <= 10^5
    1 <= limit[i] <= n

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This problem is waaaaay too confusingly explained. Don't bother.

*/

/* Time  Beats: 28.57% */
/* Space Beats: 71.43% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
private:
    static int comparator(const pair<int, int>& a, const pair<int, int>& b)
    {
        if (a.second != b.second)
            return a.second < b.second;

        return a.first > b.first;
    }

public:
    long long maxTotal(vector<int>& value, vector<int>& limit)
    {
        const int N = value.size();
        vector<pair<int, int>> value_limit_pairs(N, pair<int,int>());

        for (int i = 0; i < N; i++)
            value_limit_pairs.push_back( {value[i], limit[i]} );

        // Sort
        sort(value_limit_pairs.begin(), value_limit_pairs.end(), comparator);

        // MinHeap based on value
        priority_queue<pair<int, int>,
                      vector<pair<int, int>>,
                      greater<pair<int, int>>> min_heap;

        long long total_sum = 0;
        for (const auto& entry : value_limit_pairs)
        {
            const int& curr_value = entry.first;
            const int& curr_limit = entry.second;

            // Remove any element whose limit < current_limit
            while ( ! min_heap.empty() && min_heap.top().second < curr_limit)
                min_heap.pop();

            if (static_cast<int>(min_heap.size()) < curr_limit)
            {
                min_heap.push({curr_value, curr_limit});
                total_sum += curr_value;
            }
            else if ( ! min_heap.empty() && min_heap.top().first < curr_value)
            {
                total_sum += curr_value - min_heap.top().first;
                min_heap.pop();
                min_heap.push({curr_value, curr_limit});
            }
        }

        return total_sum;
    }
};
