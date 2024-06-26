#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    327) Count of Range Sum
    ===========================

    ============
    Description:
    ============

    Given an integer array nums and two integers lower and upper, return the
    number of range sums that lie in [lower, upper] inclusive.

    Range sum S(i, j) is defined as the sum of the elements in nums between
    indices i and j inclusive, where i <= j.

    =====================================================================
    FUNCTION: int countRangeSum(vector<int>& nums, int lower, int upper); 
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-2,5,-1], lower = -2, upper = 2
    Output: 3
    Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.

    --- Example 2 ---
    Input: nums = [0], lower = 0, upper = 0
    Output: 1


    *** Constraints ***
    1 <= nums.length <= 105
    -2^31 <= nums[i] <= 2^31 - 1
    -10^5 <= lower <= upper <= 10^5
    The answer is guaranteed to fit in a 32-bit integer.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.84% */
/* Space Beats: 33.75% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countWithMergeSort(vector<long> &sums, int left, int right, int lower, int upper)
    {
        int count = 0;
        
        if (right - left <= 1)
        {
            if(right - left == 1)
                return (lower <= sums[left] && sums[left] <= upper);
            else
                return 0;
        }
        
        int mid = (left + right)/2;
        
        int leftSideSum  = countWithMergeSort(sums, left, mid, lower, upper);
        int rightSideSum = countWithMergeSort(sums, mid, right, lower, upper);
        
        int i = left;
        int j = mid;
        
        int n = 0;
        int m = 0;
        
        std::vector<long> cache(right - left, 0);
        
        int k = 0;
        while (i < mid)
        {
            while (mid+n < right && sums[mid+n] < sums[i]+lower)
                n++;
            
            while (mid+m < right && sums[mid+m] <= sums[i] + upper)
                m++;
            
            while (j < right && sums[j] < sums[i])
                cache[k++] = sums[j++];
            
            cache[k++] = sums[i++];
            
            count += m-n;
        }
        
        
        while (j < right)
            cache[k++] = sums[j++];
        
        for(int idx = 0; idx<cache.size(); idx++)
            sums[left + idx] = cache[idx];

        return leftSideSum + rightSideSum + count;
    }
    
    int countRangeSum(vector<int>& nums, int lower, int upper)
    {
        const int n = nums.size();

        std::vector<long> prefixSum(n, 0);
        prefixSum[0] = nums[0];

        for(int i = 1; i<nums.size(); i++)
            prefixSum[i] = nums[i] + prefixSum[i-1];

        return countWithMergeSort(prefixSum, 0, n, lower, upper);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.43% */
/* Space Beats: 83.89% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class SegmentTree {
private:
    int n;
    std::vector<int> arr;
public:
    SegmentTree(int size)
        : n(size), arr(2*size)
    {
        arr[0] = 0;
        for(int i = 0; i < n; ++i)
            arr[i+n] = 1;

        for(int i = n-1; i > 0; --i)
            arr[i] = arr[2*i]+arr[2*i+1];
    }

    void add_value(int idx, int val)
    {
        idx += n;
        arr[idx] += val;

        while (idx > 1)
        {
            if (idx % 2)
                arr[idx/2] = arr[idx-1] + arr[idx];
            else
                arr[idx/2] = arr[idx] + arr[idx+1];

            idx >>= 1;
        }
    }

    int getSum(int left, int right)
    {
        int count = 0;
        left  += n;
        right += n;

        while (left <= right)
        {
            if (left % 2)
                count += arr[left++];

            if (right % 2 == 0)
                count += arr[right--];

            left  >>= 1;
            right >>= 1;
        }

        return count;
    }
};

//Time O(NlogN), Space O(N)
class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper)
    {
        std::vector<long long> sum(nums.size()+1, 0);

        for (int i = 0; i < nums.size(); ++i)
            sum[i+1] = sum[i] + nums[i];

        std::vector<long long> A(sum.begin(), sum.end());

        std::sort(A.begin(), A.end());

        SegmentTree tree(A.size());
        int count = 0;
        for (const auto &x : sum)
        {
            int idx = lower_bound(A.begin(), A.end(), x)-A.begin();
            int lower_idx = std::lower_bound(A.begin(), A.end(), x+lower)-A.begin();
            int upper_idx = std::upper_bound(A.begin(), A.end(), x+upper)-A.begin()-1;

            tree.add_value(idx, -1);
            count += tree.getSum(lower_idx, upper_idx);
        }

        return count;
    };
};


