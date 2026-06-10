/*
    ============
    === HARD ===
    ============

    =====================================
    3691) Maximum Total Subarray Value II
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer k.

    You must select exactly k distinct nums[l..r] of nums. Subarrays may
    overlap, but the exact same subarray (same l and r) cannot be chosen more
    than once.

    The value of a subarray nums[l..r] is defined as: max(nums[l..r]) -
    min(nums[l..r]).

    The total value is the sum of the values of all chosen subarrays.

    Return the maximum possible total value you can achieve.

    ============================================================
    FUNCTION: long long maxTotalValue(vector<int>& nums, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2], k = 2
    Output: 4
    Explanation:
    One optimal approach is:

        Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
        Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.

    Adding these gives 2 + 2 = 4.


    --- Example 2 ---
    Input: nums = [4,2,5,1], k = 3
    Output: 12
    Explanation:
    One optimal approach is:

        Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
        Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
        Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.

    Adding these gives 4 + 4 + 4 = 12.



    *** Constraints ***
    1 <= n == nums.length <= 5 * 10^4
    0 <= nums[i] <= 109
    1 <= k <= min(105, n * (n + 1) / 2)

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.68% */
/* Space Beats: 58.87% */

/* Time  Complexity: O(N * logN  +  k * log^2(N)) */
/* Space Complexity: O(N)                         */
class Solution {
    struct State {
        int left;
        int right;
        long long diff;

        State(int left, int right, long long diff)
            : left(left), right(right), diff(diff)
        {}
    };

    struct Compare {
        bool operator() (const State& a, const State& b) const
        {
            return a.diff < b.diff; // Max Heap
        }
    };

    class SegmentTree {
        struct Node {
            int start;
            int end;
            int mini;
            int maxi;

            Node* left  = nullptr;
            Node* right = nullptr;

            Node(int s, int e)
                : start(s), end(e), mini(INT_MAX), maxi(INT_MIN)
            {}
        };

        Node* root;

        Node* construct_segment_tree(vector<int>& nums, int start, int end)
        {
            Node* node = new Node(start, end);

            if (start == end)
            {
                node->mini = nums[start];
                node->maxi = nums[start];
                return node;
            }

            int mid = (start + end) / 2;

            node->left  = construct_segment_tree(nums, start, mid);
            node->right = construct_segment_tree(nums, mid+1, end);

            node->mini = min(node->left->mini, node->right->mini);
            node->maxi = max(node->left->maxi, node->right->maxi);

            return node;
        }

        pair<int, int> get(Node* node, int left, int right)
        {
            if (node == nullptr)
                return {INT_MAX, INT_MIN};

            if (left <= node->start && node->end <= right)
                return {node->mini, node->maxi};

            if (node->end < left || right < node->start)
                return {INT_MAX, INT_MIN};

            auto left_result  = get(node->left , left, right);
            auto right_result = get(node->right, left, right);

            int mini = min(left_result.first , right_result.first);
            int maxi = max(left_result.second, right_result.second);

            return {mini, maxi};
        }

    public:
        SegmentTree(vector<int>& nums)
        {
            const int N = nums.size();
            root = construct_segment_tree(nums, 0, N - 1);
        }

        pair<int, int> get(int left, int right)
        {
            return get(root, left, right);
        }
    };

public:
    long long maxTotalValue(vector<int>& nums, int k)
    {
        const int N = nums.size();

        SegmentTree seg(nums);

        priority_queue<State, vector<State>, Compare> max_heap;

        for (int left = 0; left < N; left++)
        {
            int right = N - 1;

            auto pair = seg.get(left, right);
            long long diff = 1LL * pair.second - pair.first;

            max_heap.push(State(left, right, diff));
        }

        long long sum = 0;

        while (k > 0)
        {
            State curr = max_heap.top();
            max_heap.pop();

            sum += curr.diff;

            int left  = curr.left;
            int right = curr.right - 1;

            if (left <= right)
            {
                auto pair = seg.get(left, right);

                long long diff = 1LL * pair.second - pair.first;

                max_heap.push(State(left, right, diff));
            }

            // Decrement
            k--;
        }

        return sum;
    }
};
