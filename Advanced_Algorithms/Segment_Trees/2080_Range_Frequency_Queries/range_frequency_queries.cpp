/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    2080) Range Frequency Queries
    =============================

    ============
    Description:
    ============

    Design a data structure to find the frequency of a given value in a given
    subarray.

    The frequency of a value in a subarray is the number of occurrences of that
    value in the subarray.

    Implement the RangeFreqQuery class:

        + RangeFreqQuery(int[] arr) Constructs an instance of the class with
          the given 0-indexed integer array arr.

        + int query(int left, int right, int value) Returns the frequency of
          value in the subarray arr[left...right].

    A subarray is a contiguous sequence of elements within an array.
    arr[left...right] denotes the subarray that contains the elements of nums
    between indices left and right (inclusive).

    ===============================
    CLASS:
    class RangeFreqQuery {
    public:
        RangeFreqQuery(vector<int>& arr) {
            
        }
        
        int query(int left, int right, int value) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["RangeFreqQuery", "query", "query"]
    [[[12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]], [1, 2, 4], [0, 11, 33]]
    Output
    [null, 1, 2]

    Explanation
    RangeFreqQuery rangeFreqQuery = new RangeFreqQuery([12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]);
    rangeFreqQuery.query(1, 2, 4); // return 1. The value 4 occurs 1 time in the subarray [33, 4]
    rangeFreqQuery.query(0, 11, 33); // return 2. The value 33 occurs 2 times in the whole array.


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i], value <= 10^4
    0 <= left <= right < arr.length
    At most 10^5 calls will be made to query

*/

#include <unordered_map>
#include <vector>
using namespace std;

/* Time  Beats: 9.88% */
/* Space Beats: 9.24% */

/* Time  Complexity: O(Q * logN) */
/* Space Complexity: O(N * logN) */
class SegmentTree {
private:
    int n;
    vector<int> nums;
    vector<unordered_map<int,int>> seg_tree;

public:
    SegmentTree(vector<int>& arr)
    {
        nums = arr;
        n = arr.size();

        seg_tree.resize(4 * n);

        construct_segment_tree(0, 0, n-1);
    }

    void construct_segment_tree(int idx, int start, int end)
    {
        if (start == end)
        {
            seg_tree[idx][nums[start]] = 1;
            return;
        }

        int mid = start + (end - start) / 2;

        // 0-indexed
        construct_segment_tree(2 * idx + 1, start, mid);
        construct_segment_tree(2 * idx + 2, mid+1, end);

        // Merge children into parent
        for (auto& [val, freq] : seg_tree[2 * idx + 1])
            seg_tree[idx][val] += freq;

        for (auto& [value, freq] : seg_tree[2 * idx + 2])
            seg_tree[idx][value] += freq;
    }

    int range_frequency_query(int idx, int start, int end, int q_left, int q_right, int val)
    {
        if (q_left <= start && end <= q_right) // Total Overlap
            return seg_tree[idx][val];

        if (q_right < start || end < q_left)   // No Overlap
            return 0;

        // Partial Overlap
        int mid = start + (end - start) / 2;

        return range_frequency_query(2 * idx + 1, start, mid, q_left, q_right, val) +
               range_frequency_query(2 * idx + 2, mid+1, end, q_left, q_right, val);
    }

    int query_frequency(int q_left, int q_right, int value)
    {
        return range_frequency_query(0, 0, n-1, q_left, q_right, value);
    }
};

class RangeFreqQuery {
private:
    SegmentTree seg_tree;

public:

    RangeFreqQuery(vector<int>& arr)
        : seg_tree(arr) // Call the constructor
    {

    }

    int query(int left, int right, int value)
    {
        return seg_tree.query_frequency(left, right, value);
    }
};
