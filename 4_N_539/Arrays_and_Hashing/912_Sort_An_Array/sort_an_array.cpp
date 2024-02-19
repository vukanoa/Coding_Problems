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




// TLE - Time Limit Exceeded
/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Another_QuickSort {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        quick_sort(nums, 0, nums.size()-1);

        return nums;
    }

private:
    void quick_sort(std::vector<int>& nums, int start, int end)
    {
        if (start >= end)
            return;

        int pivot = partition(nums, start, end);

        quick_sort(nums,     0    , pivot - 1);
        quick_sort(nums, pivot + 1,    end   );
    }

    int partition(std::vector<int>& nums, int start, int end)
    {
        int pivot = end;

        int i = start-1;
        int j = start;

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

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
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

    std::vector<int> merge(std::vector<int>& a, std::vector<int>& b)
    {
        std::vector<int> sorted;

        int i = 0;
        int j = 0;

        while (i < a.size() && j < b.size())
        {
            if (a[i] <= b[j])
                sorted.push_back(a[i++]);
            else
                sorted.push_back(b[j++]);
        }

        if (i == a.size())
            sorted.insert(sorted.end(), b.begin() + j, b.end());
        else if (j == b.size())
            sorted.insert(sorted.end(), a.begin() + i, a.end());

        return sorted;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Just another way of implementing Merge Sort. This one is more intuitive to
    me.

*/

/* Time  Beats: 6.11% */
/* Space Beats: 6.08% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Another_Merge_Sort {
public:
    std::vector<int> sortArray(std::vector<int>& nums)
    {
        return merge_sort(nums);
    }

private:
    std::vector<int> merge_sort(std::vector<int> nums)
    {
        if (nums.size() == 1)
            return nums;

        int half = nums.size() / 2;

        std::vector<int> left_half (nums.begin()       , nums.begin() + half);
        std::vector<int> right_half(nums.begin() + half, nums.end());

        std::vector<int> a = sortArray(left_half);
        std::vector<int> b = sortArray(right_half);

        return merge_two_vectors(a, b);
    }

private:
    std::vector<int> merge_two_vectors(std::vector<int>& a, std::vector<int>& b)
    {
        int i = 0;
        int j = 0;

        std::vector<int> result;

        while (i < a.size() && j < b.size())
        {
            if (a[i] <= b[j])
                result.push_back(a[i++]);
            else
                result.push_back(b[j++]);
        }

        if (i == a.size())
            result.insert(result.end(), b.begin() + j, b.end());
        else
            result.insert(result.end(), a.begin() + i, a.end());

        return result;
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
