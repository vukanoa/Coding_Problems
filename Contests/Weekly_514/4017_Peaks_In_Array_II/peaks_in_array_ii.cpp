/*
    ============
    === HARD ===
    ============

    ===========================
    4017) Peaks in Array II
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D integer array
    queries.

    A subarray nums[i..j] is called a peak subarray if:

        + Its length is at least 3.
        + There exists an index k such that i < k < j and:
            nums[k] > nums[k - 1]
            nums[k] > nums[k + 1]

    You have to process queries of two types:

        + [1, li, ri]: Calculate the number of peak subarrays fully contained
                       within nums[li..ri].

        + [2, indexi, vali]: Update nums[indexi] to vali. This update applies
                             to all subsequent queries.

    Return an array answer, where answer[i] is the answer to the ith query of
    type 1 in the order they appear.

    ==========================================================================================
    FUNCTION: vector<long long> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries);
    ==========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,4], queries = [[1,0,3],[2,1,1],[1,0,3]]
    Output: [2,0]
    Explanation:
        Query [1, 0, 3]:
            [1, 3, 2]: choose k = 1. Then nums[k] = 3, nums[k - 1] = 1, and
                       nums[k + 1] = 2. Since 3 > 1 and 3 > 2, this is a peak
                       subarray.

            [1, 3, 2, 4]: choose k = 1. Then nums[k] = 3, nums[k - 1] = 1, and
                          nums[k + 1] = 2. Since 3 > 1 and 3 > 2, this is a
                          peak subarray.

        Query [2, 1, 1]: Update nums[1] to 1. The array becomes [1, 1, 2, 4].

        Query [1, 0, 3]: There are no peak subarrays now.

        Thus, answer = [2, 0].




    --- Example 2 ---
    Input: nums = [9,8,9,8], queries = [[1,1,3],[2,2,1],[1,0,2]]
    Output: [1,0]
    Explanation:
        Query [1, 1, 3]: nums[1..3] = [8, 9, 8]: choose k = 2. Then nums[k] =
                         9, nums[k - 1] = 8, and nums[k + 1] = 8. Since 9 > 8
                         and 9 > 8, this is a peak subarray.

        Query [2, 2, 1]: Update nums[2] to 1. The array becomes [9, 8, 1, 8].

        Query [1, 0, 2]: There are no peak subarrays.

        Thus, answer = [1, 0].




    --- Example 3 ---
    Input: nums = [3,6,2,7,1], queries = [[1,1,3],[2,3,0],[1,0,4]]
    Output: [0,3]
    Explanation:
        Query [1, 1, 3]: The only subarray of length at least 3 is [6, 2, 7].
                         Its only possible peak index is k = 2, but nums[2] = 2
                         is less than both nums[1] = 6 and nums[3] = 7, so it
                         is not a peak subarray.

        Query [2, 3, 0]: Update nums[3] to 0. The array becomes [3, 6, 2, 0, 1]
        Query [1, 0, 4]:
            [3, 6, 2]: choose k = 1. Then nums[k] = 6, nums[k - 1] = 3, and
                       nums[k + 1] = 2. Since 6 > 3 and 6 > 2, this is a peak
                       subarray.

            [3, 6, 2, 0]: choose k = 1. Then nums[k] = 6, nums[k - 1] = 3, and
                          nums[k + 1] = 2. Since 6 > 3 and 6 > 2, this is a
                          peak subarray.

            [3, 6, 2, 0, 1]: choose k = 1. Then nums[k] = 6, nums[k - 1] = 3,
                             and nums[k + 1] = 2. Since 6 > 3 and 6 > 2, this
                             is a peak subarray.

        Thus, answer = [0, 3].



    *** Constraints ***
    3 <= n == nums.length <= 10^5
    0 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i] = [1, li, ri] or queries[i] = [2, indexi, vali]
    0 <= li < ri <= n - 1
    0 <= indexi <= n - 1
    0 <= vali <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.93% */
/* Space Beats: 76.54% */

/* Time Complexity:  O((N + Q) log N) */
/* Space Complexity: O(N)             */
class SegmentTree {
public:
    struct Node {
        int first = -1;
        int last  = -1;
        long long sum = 0;
    };

    int tree_size;
    vector<Node> seg_tree;

    // count_subarrays_of_length_at_least_two(long long segment_length)
    long long count_subarrays(long long length)
    {
        if (length <= 0)
            return 0;

        return (length-1) * (length-2) / 2;
    }

    Node merge(const Node& L, const Node& R)
    {
        if (L.first == -1)
            return R;

        if (R.first == -1)
            return L;

        return {L.first, R.last, L.sum + R.sum + count_subarrays(R.first - L.last + 1)};
    }

    void construct_segment_tree(int idx, int start, int end, vector<int>& peak)
    {
        const int N = peak.size();

        if (start == end)
        {
            if (start < N && peak[start])
                seg_tree[idx] = {start, start, 0};

            return;
        }

        int mid = start + (end - start) / 2;

        construct_segment_tree(2*idx + 1, start, mid, peak);
        construct_segment_tree(2*idx + 2, mid+1, end, peak);

        seg_tree[idx] = merge(seg_tree[2*idx + 1],
                              seg_tree[2*idx + 2]);
    }

    void init(vector<int>& peak)
    {
        int N = peak.size();

        tree_size = 1;
        while (tree_size < N)
            tree_size <<= 1;

        seg_tree.resize(2*tree_size - 1);

        construct_segment_tree(0, 0, tree_size-1, peak);
    }

    void update_segment_tree(int idx, int start, int end, int pos, bool is_peak)
    {
        if (start == end)
        {
            seg_tree[idx] = is_peak ? Node{start, start, 0} : Node{};

            return;
        }

        int mid = start + (end - start) / 2;

        if (pos <= mid)
            update_segment_tree(2*idx + 1, start, mid, pos, is_peak);
        else
            update_segment_tree(2*idx + 2, mid+1, end, pos, is_peak);

        seg_tree[idx] = merge(seg_tree[2*idx + 1],
                              seg_tree[2*idx + 2]);
    }

    Node range_query(int idx, int start, int end, int q_left, int q_right)
    {
        if (q_left <= start && end <= q_right)
            return seg_tree[idx];

        if (end < q_left || q_right < start)
            return Node{};

        int mid = start + (end - start) / 2;

        return merge(range_query(2*idx + 1, start, mid, q_left, q_right),
                     range_query(2*idx + 2, mid+1, end, q_left, q_right));
    }
};

class Solution {
public:
    vector<long long> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries)
    {
        int N = nums.size();
        vector<long long> answer;

        vector<int> peak(N, 0);
        for (int i = 1; i < N - 1; i++)
        {
            peak[i] = nums[i] > nums[i - 1] && nums[i] > nums[i + 1];
        }


        SegmentTree seg_tree;
        seg_tree.init(peak);

        for (auto& query : queries)
        {
            int type = query[0];

            if (type == 1)
            {
                int L = query[1];
                int R = query[2];

                if (R - L + 1 < 3)
                {
                    answer.push_back(0);
                    continue;
                }

                auto node = seg_tree.range_query(0, 0, seg_tree.tree_size-1, L+1, R-1);

                if (node.first == -1)
                {
                    answer.push_back(0);
                    continue;
                }

                long long total = SegmentTree().count_subarrays(R - L + 1);

                long long no_peak = node.sum + seg_tree.count_subarrays(node.first - L + 1)
                                             + seg_tree.count_subarrays(R - node.last + 1);

                answer.push_back(total - no_peak);
            }
            else
            {
                int idx   = query[1];
                nums[idx] = query[2];

                for (int i = max(1, idx - 1); i <= min(N - 2, idx + 1); i++)
                {
                    peak[i] = nums[i] > nums[i - 1] &&
                              nums[i] > nums[i + 1];

                    seg_tree.update_segment_tree(0, 0, seg_tree.tree_size-1, i, peak[i]);
                }
            }
        }

        return answer;
    }
};
