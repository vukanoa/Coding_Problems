/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    912) Sort an Array
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums, sort the array in ascending order and
    return it.

    You must solve the problem without using any built-in functions in
    O(nlog(n)) time complexity and with the smallest space complexity possible.

    ===================================================
    FUNCTION: vector<int> sortArray(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,2,3,1]
    Output: [1,2,3,5]
    Explanation: After sorting the array, the positions of some numbers are not
    changed (for example, 2 and 3), while the positions of other numbers are
    changed (for example, 1 and 5).


    --- Example 2 ---
    Input: nums = [5,1,1,2,0,0]
    Output: [0,0,1,1,2,5]
    Explanation: Note that the values of nums are not necessairly unique.


    *** Constraints ***
    1 <= nums.length <= 5 * 10^4
    -5 * 104 <= nums[i] <= 5 * 10^4

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

   Fundamental Quick-Sort algorithm.

    TLE - Time Limit Exceeded, because QuickSort with "Lomuto-Partitioning
    gives an O(N^2) in the worst case.

*/
class Solution_Quick_Sort_using_Lomuto_Partitioning {
public:
    vector<int> sortArray(vector<int>& nums)
    {
        const int N = nums.size();

        quick_sort(0, N-1, nums);
        return nums;
    }

private:
    void quick_sort(int start, int end, vector<int>& nums)
    {
        if (start >= end)
            return;

        int pivot_idx = end;

        int i = start - 1;
        int j = start;
        while (j < pivot_idx)
        {
            if (nums[j] < nums[pivot_idx])
                swap(nums[++i], nums[j]);

            // Increment
            j++;
        }
        swap(nums[i+1], nums[pivot_idx]);

        quick_sort(start,   i, nums); // Sort left  part
        quick_sort(  i+2, end, nums); // Sort right part
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Merge-Sort algorithm.

*/

/* Time  Beats: 5.61% */
/* Space Beats: 7.37% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Another_Merge_Sort {
public:
    vector<int> sortArray(vector<int>& nums)
    {
        return merge_sort(nums);
    }

private:
    vector<int> merge_sort(vector<int> nums)
    {
        const int N = nums.size();

        if (N == 1)
            return nums;

        int half = nums.size() / 2;

        vector<int> a(nums.begin()       , nums.begin() + half);
        vector<int> b(nums.begin() + half, nums.end());

        a = merge_sort(a);
        b = merge_sort(b);

        return merge_two_vectors(a, b);
    }

private:
    vector<int> merge_two_vectors(vector<int>& a, vector<int>& b)
    {
        const int A_SIZE = a.size();
        const int B_SIZE = b.size();
        int i = 0;
        int j = 0;

        vector<int> result;

        while (i < A_SIZE && j < B_SIZE)
        {
            if (a[i] <= b[j])
                result.push_back(a[i++]);
            else
                result.push_back(b[j++]);
        }

        if (i == A_SIZE)
            result.insert(result.end(), b.begin() + j, b.end());
        else
            result.insert(result.end(), a.begin() + i, a.end());

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is kind of "cheating". Although we're not explicitly using any
    built-in SORTING function, we kind of are because this data structure, by
    its design, keeps the lowest or greatest element at the "top", i.e. at
    index 0.

*/

/* Time  Beats: 74.23% */
/* Space Beats: 60.80% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Kind_of_Cheating {
public:
    vector<int> sortArray(vector<int>& nums)
    {
        priority_queue<int, vector<int>, greater<int>> min_heap(nums.begin(), nums.end());

        nums.clear();
        while ( ! min_heap.empty())
        {
            nums.push_back(min_heap.top());
            min_heap.pop();
        }

        return nums;
    }
};
