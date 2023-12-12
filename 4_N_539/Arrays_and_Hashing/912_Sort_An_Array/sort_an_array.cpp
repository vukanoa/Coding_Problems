#include <iostream>
#include <vector>
#include <queue>

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

// TLE - Time Limit Exceeded
class Solution_Quick_Sort {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        bool sorted = true;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i-1] >= nums[i])
            {
                sorted = false;
                break;
            }
        }

        if (sorted)
            return nums;


        quick_sort(nums, -1, 0, nums.size() - 1);

        return nums;
    }

private:
    void quick_sort(std::vector<int>& nums, int i, int j, int pivot)
    {
        if (j >= pivot)
            return;

        int mid = partition(nums, i, j, pivot);

        quick_sort(nums,  i,   j,    mid-1);
        quick_sort(nums, mid, mid+1, pivot);
    }

    int partition(std::vector<int>& nums, int i, int j, int pivot)
    {
        if (j >= pivot)
            return pivot;

        while (j < pivot)
        {
            if (nums[j] <= nums[pivot])
                std::swap(nums[++i], nums[j]);

            j++;
        }
        std::swap(nums[i+1], nums[pivot]);

        return i+1;
    }
};




/* Time  Beats: 9.82% */
/* Space Beats: 5.93% */
class Solution_Merge_Sort {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums;

        return sorted_merge(nums, 0, nums.size()-1);
    }

private:
    std::vector<int> sorted_merge(std::vector<int>& nums, int left, int right)
    {
        if (left >= right)
            return {nums[left]};

        int mid = left + (right - left) / 2;

        std::vector<int> left_part  = sorted_merge(nums, left, mid);
        std::vector<int> right_part = sorted_merge(nums, mid+1,  right);

        return merge(left_part, right_part);
    }

    std::vector<int> merge(std::vector<int>& left_part, std::vector<int>& right_part)
    {
        std::vector<int> sorted;

        int i = 0;
        int j = 0;

        while (i < left_part.size() && j < right_part.size())
        {
            if (left_part[i] <= right_part[j])
                sorted.push_back(left_part[i++]);
            else
                sorted.push_back(right_part[j++]);
        }

        if (i == left_part.size())
            sorted.insert(sorted.end(), right_part.begin() + j, right_part.end());
        else if (j == right_part.size())
            sorted.insert(sorted.end(), left_part.begin() + i, left_part.end());

        return sorted;
    }
};




/* Time  Beats: 74.23% */
/* Space Beats: 60.80% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap(nums.begin(), nums.end());

        nums.clear();
        while (!min_heap.empty())
        {
            nums.push_back(min_heap.top());
            min_heap.pop();
        }

        return nums;
    }
};
