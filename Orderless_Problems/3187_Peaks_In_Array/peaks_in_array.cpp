/*
    ============
    === HARD ===
    ============

    ===========================
    3187) Peaks in Array
    ===========================

    ============
    Description:
    ============

    A peak in an array arr is an element that is greater than its previous and
    next element in arr.

    You are given an integer array nums and a 2D integer array queries.

    You have to process queries of two types:

        queries[i] = [1, li, ri], determine the count of peak elements in the

        nums[li..ri].
        queries[i] = [2, indexi, vali], change nums[indexi] to vali.

    Return an array answer containing the results of the queries of the first
    type in order.

    =====
    Note: The first and the last element of an array or a subarray cannot be a
          peak.
    =====

    ====================================================================================
    FUNCTION: vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
    Output: [0]
    Explanation:
    First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
    Second query: The number of peaks in the [3,1,4,4,5] is 0.

    --- Example 2 ---
    Input: nums = [4,1,4,2,1,5], queries = [[2,2,4],[1,0,2],[1,0,4]]
    Output: [0,1]
    Explanation:
    First query: nums[2] should become 4, but it is already set to 4.
    Second query: The number of peaks in the [4,1,4] is 0.
    Third query: The second 4 is a peak in the [4,1,4,2,1].


    *** Constraints ***
    3 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i][0] == 1 or queries[i][0] == 2
    For all i that:
        queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
        queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Segment Tree)

*/

/* Time  Beats: 54.35% */
/* Space Beats: 31.88% */

/* Time  Complexity: O(Q * logN + N) */
/* Space Complexity: O(N)            */
class SegmentTree {
private:
    vector<long long> seg;

public:
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int idx, int low, int high, vector<long long>& arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r)
    {
        if (r < low || high < l)
            return 0;

        if (low >= l && high <= r)
            return seg[idx];

        int mid = (low + high) >> 1;

        int left  = query(2 * idx + 1,   low  ,  mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return left + right;
    }

    void update(int idx, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = (low + high) >> 1;

        if (i <= mid)
            update(2 * idx + 1, low, mid, i, val);

        else
            update(2 * idx + 2, mid + 1, high, i, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
};


class Solution {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        vector<long long> peak(N, 0);

        for (int i = 1; i < N-1; ++i)
        {
            if (nums[i] > nums[i-1] && nums[i] > nums[i+1])
                peak[i] = 1;
        }

        vector<int> result;

        SegmentTree segment_tree(N);
        segment_tree.build(0, 0, N-1, peak);

        for (int i = 0; i < queries.size(); i++)
        {
            int type = queries[i][0];

            if (type == 1)
            {
                int L = queries[i][1];
                int R = queries[i][2];

                if (L == R)
                {
                    result.push_back(0);
                    continue;
                }

                long long red = 0;

                if (peak[L] == 1)
                    red++;

                if (peak[R] == 1)
                    red++;

                int answer = segment_tree.query(0, 0, N-1, L, R);

                result.push_back(answer - red);
            }
            else if (type == 2)
            {
                int idx_to_update = queries[i][1];
                int new_value     = queries[i][2];

                nums[idx_to_update] = new_value;

                if (idx_to_update-1 >= 0 && idx_to_update+1 < N) // checking index p
                {
                    if (nums[idx_to_update] > nums[idx_to_update-1] && nums[idx_to_update] > nums[idx_to_update+1])
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update, 1);
                        peak[idx_to_update] = 1;
                    }
                    else
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update, 0);
                        peak[idx_to_update] = 0;
                    }
                }

                if (idx_to_update-2 >= 0 && idx_to_update < N) // checking index p-1
                {
                    if (nums[idx_to_update-1] > nums[idx_to_update-2] && nums[idx_to_update-1] > nums[idx_to_update])
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update-1, 1);
                        peak[idx_to_update-1] = 1;
                    }
                    else
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update-1, 0);
                        peak[idx_to_update-1] = 0;
                    }
                }

                if (idx_to_update >= 0 && idx_to_update+2 < N) // checking index p+1
                {
                    if (nums[idx_to_update+1] > nums[idx_to_update] && nums[idx_to_update+1] > nums[idx_to_update+2])
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update+1, 1);
                        peak[idx_to_update+1] = 1;
                    }
                    else
                    {
                        segment_tree.update(0, 0, N-1, idx_to_update+1, 0);
                        peak[idx_to_update+1] = 0;
                    }
                }
            }
        }

        return result;
    }
};
