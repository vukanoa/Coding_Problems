#include <iostream>
#include <functional>

#include <vector>
#include <queue>

/*

    Given an int array nums of length n. Split it into strictly decreasing
    subsequences. Output the min number of subsequences you can get by
    splitting.

    Example 1:

    Input: [5, 2, 4, 3, 1, 6]
    Output: 3
    Explanation: You can split this array into: [5, 2, 1], [4, 3], [6]. And
    there are 3 subsequences you get.  Or you can split it into [5, 4, 3], [2,
    1], [6]. Also 3 subsequences.  But [5, 4, 3, 2, 1], [6] is not legal
    because [5, 4, 3, 2, 1] is not a subsuquence of the original array.




    Example 2:

    Input: [2, 9, 12, 13, 4, 7, 6, 5, 10]
    Output: 4
    Explanation: [2], [9, 4], [12, 10], [13, 7, 6, 5]




    Example 3:

    Input: [1, 1, 1]
    Output: 3
    Explanation: Because of the strictly descending order you have to split it
    into 3 subsequences: [1], [1], [1]


*/


class Solution_My_Own_Bin_Search {
public:
    int solution(std::vector<int>& nums)
    {
        std::vector<int> piles(nums.size());
        int size = 0;

        for (int& num : nums)
        {
            int pile = binary_search(piles, 0, size, num);

            piles[pile] = num;

            if (pile == size)
                size++;
        }

        return size;
    }

private:
    int binary_search(std::vector<int>& nums, int left, int right, int target)
    {
        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] <= target)
                left  = mid + 1;
            else
                right = mid;
        }

        return left;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

   Ohhh, I get it! The number of decreasing subsequence partitions is equal to
   the length of the longest non-decreasing subsequence, because every
   non-decreasing number represents a point where a continuation of a previous
   decreasing subsequence is impossible. We don't care what the subsequences
   are, so the length is enough to tell us how many times a new decreasing
   subsequence is required.

   This is also called "Patience Sort". It's a very important algorithm.

*/

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_STL_Upper_Bound {
public:
    int solution(std::vector<int>& nums)
    {
        const int N = nums.size();

        std::deque<int> piles;
        piles.push_back(nums[N-1]);

        for (int i = N-2; i >= 0; i--)
        {
            auto upper = std::upper_bound(piles.begin(), piles.end(), nums[i]);

            if (upper != piles.begin())
            {
                if (*(upper-1) == nums[i])
                    piles.push_front(nums[i]);
                else
                {
                    upper--;
                    *upper = nums[i];
                }
            }
            else
                piles.push_front(nums[i]);
        }

        return piles.size();
    }
};


int
main()
{
    Solution_My_Own_Bin_Search   sol_my_bin;
    Solution_STL_Upper_Bound     sol_stl;


    /* Example 1 */
    // std::vector<int> nums = {5, 2, 4, 3, 1, 6};

    /* Example 2 */
    std::vector<int> nums = {2, 9, 12, 13, 4, 7, 6, 5, 10};

    /* Example 3 */
    // std::vector<int> nums = {1, 1, 1};


    std::cout << "\n\t===============================";
    std::cout << "\n\t=== DECREASING SUBSEQUENCES ===";
    std::cout << "\n\t===============================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tnums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int  result = sol_my_bin.solution(nums);
    int  result = sol_stl.solution(nums);


    /* Write Output */
    std::cout << "\n\tResult: " << result;


    std::cout << "\n\n";
    return 0;
}
