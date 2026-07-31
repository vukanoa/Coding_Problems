/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    307) Range Sum Query Mutable
    ============================

    ============
    Description:
    ============


    Given an integer array nums, handle multiple queries of the following types:

        + Update the value of an element in nums.

        + Calculate the sum of the elements of nums between indices left and
          right inclusive where left <= right.

    Implement the NumArray class:

        + NumArray(int[] nums) Initializes the object with the integer array
          nums.

        + void update(int index, int val) Updates the value of nums[index] to
          be val.

        + int sumRange(int left, int right) Returns the sum of the elements of
          nums between indices left and right inclusive (i.e. nums[left] +
          nums[left + 1] + ... + nums[right]).

    ===============================
    CLASS:
    class NumArray {
    public:
        NumArray(vector<int>& nums) {
            
        }
        
        void update(int index, int val) {
            
        }
        
        int sumRange(int left, int right) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["NumArray", "sumRange", "update", "sumRange"]
    [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
    Output
    [null, 9, null, 8]

    Explanation
    NumArray numArray = new NumArray([1, 3, 5]);
    numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
    numArray.update(1, 2);   // nums = [1, 2, 5]
    numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8



    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    -100 <= nums[i] <= 100
    0 <= index < nums.length
    -100 <= val <= 100
    0 <= left <= right < nums.length
    At most 3 * 10^4 calls will be made to update and sumRange.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 71.38% */
/* Space Beats: 39.36% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(N)    */
class SegmentTree {
private:
    vector<int> seg_tree;
    int n;

public:
    SegmentTree(vector<int>& nums)
    {
        n = nums.size();
        seg_tree.resize(4 * n);

        construct_segment_tree(0, 0, n-1, nums);
    }

    void update(int target_idx, int val)
    {
        update_segment_tree(0, 0, n-1, target_idx, val);
    }

    int query(int q_left, int q_right)
    {
        return range_sum_query(0, 0, n-1, q_left, q_right);
    }

private:
    void construct_segment_tree(int idx, int start, int end, vector<int>& nums)
    {
        if (start == end)
        {
            seg_tree[idx] = nums[start];
            return;
        }

        int mid = start + (end - start) / 2;

        construct_segment_tree(2 * idx + 1, start, mid, nums);
        construct_segment_tree(2 * idx + 2, mid+1, end, nums);

        seg_tree[idx] = seg_tree[2 * idx + 1] +
                        seg_tree[2 * idx + 2];
    }

    int range_sum_query(int idx, int start, int end, int q_left, int q_right)
    {
        // Total Overlap
        if (q_left <= start && end <= q_right)
            return seg_tree[idx];

        // No Overlap
        if (q_right < start || end < q_left)
            return 0;

        // Partial Overlap
        int mid = start + (end - start) / 2;

        return range_sum_query(2 * idx + 1, start, mid, q_left, q_right) +
               range_sum_query(2 * idx + 2, mid+1, end, q_left, q_right);
    }

    void update_segment_tree(int idx, int start, int end, int target_idx, int val)
    {
        if (start == end)
        {
            seg_tree[idx] = val;
            return;
        }

        int mid = start + (end - start) / 2;

        if (target_idx <= mid)
            update_segment_tree(2 * idx + 1, start, mid, target_idx, val);
        else
            update_segment_tree(2 * idx + 2, mid+1, end, target_idx, val);

        seg_tree[idx] = seg_tree[2 * idx + 1] +
                        seg_tree[2 * idx + 2];
    }
};

class NumArray {
private:
    SegmentTree seg_tree;

public:
    NumArray(vector<int>& nums)
        : seg_tree(nums) // Call the constructor, O(N)
    {

    }

    // O(logN)
    void update(int target_idx, int val)
    {
        seg_tree.update(target_idx, val);
    }

    // O(logN)
    int sumRange(int q_left, int q_right)
    {
        return seg_tree.query(q_left, q_right);
    }
};
