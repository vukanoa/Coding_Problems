#include <iostream>
#include <vector>
#include <climits>

/*
	============
	=== HARD ===
	============

	==============================
	4) Median of Two Sorted Arrays
	==============================

	============
	Description:
	============

	Given two sorted arrays nums1 and nums2 of size m and n respectively,
	return the median of the two sorted arrays.

	The overall run time complexity should be O(log (m + n)).

	================================================================================
	FUNCTION: double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
	================================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums1 = [1, 3], nums2 = [2]
	Output: 2.00000
	Explanation: merged array = [1, 2, 3] and median is 2

	--- Example 2 ---
	Input:  nums1 = [1, 2], nums2 = [3, 4]
	Output: 2.50000

	*** Constraints ***
	nums1.length == m
	nums2.length == n
	0 <= m <== 1000
	0 <= n <== 1000
	1 <= m + n <= 2000
	-10^6 <= nums1[i], nums2[i] <= 10^6

*/


/* Time  Beats: 97.61% */
/* Space Beats: 91.10% */
/* Time  Complexity: O(log(min(m, n))) */
/* Space Complexity: O(1) */
class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
	{
        if(nums1.size()>nums2.size())
            return findMedianSortedArrays(nums2,nums1);

		int total = nums1.size() + nums2.size();

        int left = 0;
		int right = nums1.size();

        while(left <= right)
		{
            int i = (right - left) / 2 + left;
            int j = (total + 1) / 2 - i;

            int A_left  = (i == 0)            ? INT_MIN : nums1[i - 1];
            int A_right = (i == nums1.size()) ? INT_MAX : nums1[i];
            int B_left  = (j == 0)            ? INT_MIN : nums2[j - 1];
            int B_right = (j == nums2.size()) ? INT_MAX : nums2[j];

            if(A_left <= B_right && B_left <= A_right)
			{
                if(total & 1)
                    return (double) std::max(A_left, B_left);
                else
                    return (double)(std::max(A_left,B_left) + std::min(A_right,B_right))/2;

            }
			else if(A_left > B_right)
                right = i - 1;
            else
                left = i + 1;
        }

        return -1.0;
    }
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums1 = {1, 3};
	// std::vector<int> nums2 = {2};

	/* Example 2 */
	// std::vector<int> nums1 = {1, 2};
	// std::vector<int> nums2 = {3, 4};

	/* Example 3 */
	// std::vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8};
	// std::vector<int> nums2 = {1, 2, 3, 4, 5};

	/* Example 4 */
	std::vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> nums2 = {1, 2, 3, 4};

	std::cout << "\n\t===================================";
	std::cout << "\n\t=== MEDIAN OF TWO SORTED ARRAYS ===";
	std::cout << "\n\t===================================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tNums 1: [";
	for (auto x: nums1)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	first = true;
	std::cout << "\n\tNums 2: [";
	for (auto x: nums2)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	double output = sol.findMedianSortedArrays(nums1, nums2);

	/* Write Output */
	printf("\n\tOutput: %lf\n\n", output);
	// std::cout << "\n\tOutput: " << output << "\n\n";

	return 0;
}
