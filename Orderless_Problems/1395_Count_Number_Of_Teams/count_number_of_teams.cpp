#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <functional>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1395) Count Number of Teams
    ===========================

    ============
    Description:
    ============

    There are n soldiers standing in a line. Each soldier is assigned a unique
    rating value.

    You have to form a team of 3 soldiers amongst them under the following
    rules:

        + Choose 3 soldiers with index (i, j, k) with rating
          (rating[i], rating[j], rating[k]).

        + A team is valid if: (rating[i] < rating[j] < rating[k]) or
          (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).

    Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).

    ============================================
    FUNCTION: int numTeams(vector<int>& rating);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rating = [2,5,3,4,1]
    Output: 3
    Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).

    --- Example 2 ---
    Input: rating = [2,1,3]
    Output: 0
    Explanation: We can't form any team given the conditions.

    --- Example 3 ---
    Input: rating = [1,2,3,4]
    Output: 4


    *** Constraints ***
    n == rating.length
    3 <= n <= 1000
    1 <= rating[i] <= 10^5
    All the integers in rating are unique.

*/

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    It's a Greedy approach. You won't believe that you wasn't able to come up
    with this once you see the impementation. It's self-explanatory.

    Essentialy - Start at the middle instead of at the beginning and then try
    to find smaller elements to the left and larger to the right.

    And for descending do the opposite - Try to find larger elements to the
    left and smaller elements to the right.

*/

/* Time  Beats: 80.51% */
/* Space Beats: 51.74% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution_Greedy {
public:
    int numTeams(vector<int>& rating)
    {
        const int N = rating.size();

        int result = 0;

        for (int mid = 1; mid < N-1; mid++)
        {
            int left_smaller = 0;
            int right_larger = 0;

            for (int i = 0; i < mid; i++)
            {
                if (rating[i] < rating[mid])
                    left_smaller++;
            }

            for (int i = mid+1; i < N; i++)
            {
                if (rating[i] > rating[mid])
                    right_larger++;
            }

            result += left_smaller * right_larger;

            int left_larger   = mid - left_smaller;
            int right_smaller = (N - mid - 1) - right_larger;

            result += left_larger * right_smaller;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Binary Index Tree)

*/

/* Time  Beats: 98.95% */
/* Space Beats: 26.87% */

/*
    Time  Complexity: O(n * logn)

        + Sorting the soldiers takes O(n log n) time.

        + We iterate through all soldiers once, and for each soldier, we
          perform constant number of BIT operations, each taking O(log n) time.

        + Therefore, the overall time complexity is O(n log n).
*/
/*
    Space Complexity: O(n)

        + We use additional space for the list of soldiers, the index map, and
          the BIT, each of size O(n).

        + Therefore, the overall space complexity is O(n).
*/
class Solution {
public:
    int numTeams(vector<int>& rating)
    {
        const int N = rating.size();

        if (N < 3)
            return 0;

        vector<pair<int, int>> soldiers;

        for (int i = 0; i < N; i++)
            soldiers.push_back({rating[i], i});

        sort(soldiers.begin(), soldiers.end());

        vector<int> index_map(N);
        for (int i = 0; i < N; i++)
            index_map[soldiers[i].second] = i;

        return count_teams(index_map, N, true) + count_teams(index_map, N, false);
    }

private:
    int count_teams(const vector<int>& index_map, int N, bool ascending)
    {
        vector<int> bit(N + 1, 0);
        int teams = 0;

        for (int i = 0; i < N; i++)
        {
            int rank  = index_map[i] + 1;

            int left  = ascending ? get_sum(bit, rank - 1) : get_sum(bit, N) - get_sum(bit, rank);
            int right = ascending ? N - rank - (get_sum(bit, N) - get_sum(bit, rank)) : rank - 1 - get_sum(bit, rank - 1);

            teams += left * right;
            update(bit, rank, 1);
        }

        return teams;
    }

    void update(vector<int>& bit, int index, int val)
    {
        while (index < bit.size())
        {
            bit[index] += val;
            index += index & (-index);
        }
    }

    int get_sum(const vector<int>& bit, int index)
    {
        int sum = 0;
        while (index > 0)
        {
            sum += bit[index];
            index -= index & (-index);
        }

        return sum;
    }
};
