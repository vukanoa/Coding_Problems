/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1865) Finding Pairs With a Certain Sum
    ======================================

    ============
    Description:
    ============


    You are given two integer arrays nums1 and nums2. You are tasked to
    implement a data structure that supports queries of two types:

        1. Add a positive integer to an element of a given index in the array
           nums2.

        2. Count the number of pairs (i, j) such that nums1[i] + nums2[j]
           equals a given value (0 <= i < nums1.length and
           0 <= j < nums2.length).

    Implement the FindSumPairs class:

        + FindSumPairs(int[] nums1, int[] nums2) Initializes the FindSumPairs
          object with two integer arrays nums1 and nums2.

        + void add(int index, int val) Adds val to nums2[index], i.e., apply
          nums2[index] += val.

        + int count(int tot) Returns the number of pairs (i, j) such that
          nums1[i] + nums2[j] == tot.

    ===============================
    CLASS:
    class FindSumPairs {
    public:
        FindSumPairs(vector<int>& nums1, vector<int>& nums2) {

        }

        void add(int index, int val) {

        }

        int count(int tot) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
    [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
    Output
    [null, 8, null, 2, 1, null, null, 11]

    Explanation
    FindSumPairs findSumPairs = new FindSumPairs([1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]);
    findSumPairs.count(7);  // return 8; pairs (2,2), (3,2), (4,2), (2,4), (3,4), (4,4) make 2 + 5 and pairs (5,1), (5,5) make 3 + 4
    findSumPairs.add(3, 2); // now nums2 = [1,4,5,4,5,4]
    findSumPairs.count(8);  // return 2; pairs (5,2), (5,4) make 3 + 5
    findSumPairs.count(4);  // return 1; pair (5,0) makes 3 + 1
    findSumPairs.add(0, 1); // now nums2 = [2,4,5,4,5,4]
    findSumPairs.add(1, 1); // now nums2 = [2,5,5,4,5,4]
    findSumPairs.count(7);  // return 11; pairs (2,1), (2,2), (2,4), (3,1), (3,2), (3,4), (4,1), (4,2), (4,4) make 2 + 5 and pairs (5,3), (5,5) make 3 + 4


    *** Constraints ***
    1 <= nums1.length <= 1000
    1 <= nums2.length <= 10^5
    1 <= nums1[i] <= 10^9
    1 <= nums2[i] <= 10^5
    0 <= index < nums2.length
    1 <= val <= 10^5
    1 <= tot <= 10^9
    At most 1000 calls are made to add and count each.

*/

#include <algorithm>
#include <vector>
#include <unordered_map>

/*
    ------------
    --- IDEA ---
    ------------

    This is a "wrapped" Two-Sum problem. Pretty straightforward.

*/

/* Time  Beats: 57.39% */
/* Space Beats: 88.13% */

/* Space Complexity: O(M) */
class FindSumPairs {
private:
    std::unordered_map<int, int> freq;
    std::vector<int> nums1;
    std::vector<int> nums2;

public:
    /* Time  Complexity: O(M) */
    FindSumPairs(std::vector<int>& nums1, std::vector<int>& nums2)
        : nums1(nums1), nums2(nums2)
    {
        for (const auto& n2 : nums2)
            freq[n2]++;
    }


    /* Time  Complexity: O(1) */
    void add(int index, int val)
    {
        int curr_val = nums2[index];

        freq[curr_val]--;
        if (freq[curr_val] == 0)
            freq.erase(curr_val);

        nums2[index] += val;
        curr_val += val;

        freq[curr_val]++;
    }

    /* Time  Complexity: O(N) */
    int count(int tot)
    {
        const int N = nums1.size();
        int result = 0;

        for (int i = 0; i < N; i ++)
        {
            int target = tot - nums1[i];

            if (freq.find(target) != freq.end())
                result += freq[target];
        }

        return result;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */




/*
    ------------
    --- IDEA ---
    ------------

    Since nums1 is not changed, we can sort it.
    Later it can be used binary search for a shortened searching range.

    That's the optimization.

     If the use case involves frequent queries on a mostly stable dataset, then
     FindSumPairs2 is faster, even if our Big O notation is SLOWER than the
     above Solution.

*/

/* Space Complexity: O(M) */
class FindSumPairs2{
public:
    std:: vector<int> nums1, nums2;
    std:: unordered_map<int, int> freq;

    int N;
    int max_val_from_nums2 = 0;


    /* Time  Complexity: O(N * logN + M) */
    FindSumPairs2(std::vector<int>& nums1, std::vector<int>& nums2)
        : nums1(nums1), nums2(nums2), N(nums1.size())
    {

        /* Sort */
        std::sort(this->nums1.begin(), this->nums1.end());

        freq.reserve(100000);

        for (int n2: nums2)
        {
            freq[n2]++;
            max_val_from_nums2 = std::max(max_val_from_nums2, n2);
        }
    }

    /* Time  Complexity: O(1) */
    void add(int index, int val)
    {
        int curr_val = nums2[index];

        if (--freq[curr_val]==0)
            freq.erase(curr_val);

        nums2[index] += val;
        freq[curr_val+val]++;

        if (curr_val + val > max_val_from_nums2)
            max_val_from_nums2 = curr_val + val;
    }

    /* Time  Complexity: O(N) */
    int count(int tot)
    {
        int result = 0;
        int target = std::max(1, tot - max_val_from_nums2);

        auto iter = lower_bound(nums1.begin(), nums1.end(), target);
        int i0 = iter - nums1.begin();

        for (int i = i0; i < N; i++)
        {
            const int n1 = nums1[i];

            if (n1 >= tot)
                break;

            result += freq[tot - n1];
        }

        return result;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
