#include <iostream>
#include <vector>


/*
	============
	=== HARD ===
	============
	
	===========================
	41) First Missing Positive
	===========================
	
	============
	Description:
	============

	Given an unsorted integer array "nums", return the smallest missing
	positive integer.

	You must implement an algorithm in O(n) time and uses constant extra space.
	
	======================================================
	FUNCTION: int firstMissingPositive(vector<int>& nums);
	======================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [1, 2, 0]
	Output: 3
	
	--- Example 2 ---
	Input:  nums = [3, 4, -1, 1]
	Output: 2
	
	--- Example 3 ---
	Input:  nums = [7, 8, 9, 11, 12]
	Output: 1
	
	*** Constraints ***
	1 <= nums.length <= 10^5
	-2^31 <= nums[i] <= 2^31 - 1

*/


/*
	------------
	--- IDEA ---
	------------

	***********
	**** N ****
	***********

	It's important to notice that the return value has to be from this set of
	values:
		{1, 2, ..., num.size(), nums.size() + 1}
	
	To convince you of that, consider the following example:
	1.a)
		nums = [7, 0, -15, 2]
		smallest = 1            // 1
	
	1.b)
		nums = [10, 11, 12]
		smallest = 1            // 1

	1.c)
		nums = [2, 3, 4]
		smallest = 1            // 1

	2)
		nums = [1, 2, 4]
		smallest = 3            // ...  | Between 1 and "nums.size() + 1"
	
	3)
		nums = [1, 2, 3, 1417]
		smallest = 4            // nums.size()
		
	4)
		nums = [1, 2, 3]
		smallest = 4            // nums.size() + 1

		Notice how both 0 and -15 are ignored since we're told:
			"return the smallest missing positive integer"


	We don't have to sort the elements, we can take the input array nums and
	convert it to Hash Set.
	Why Hash Set? Well, because we could "brute-force" it iterating trough
		[1, 2, ..., nums.size() + 1]
	and we can check if 'i'(index in this [1, ..., nums.size() + 1]) is does
	exist in Hash Set. If yes, then i++ and check that next i, and so on. We
	stop once we've found that current 'i', current possible_values[i] does
	not exist in array nums and we return that.

	If, however, we do not find that, just return nums.size() + 1.
	That is the worst case scenario.

	So since each of this "check" takes O(1) time and we're doing it O(n) times
	that makes it: O(1 * n), however the Space Complexity is O(n) as well which
	isn't what is required by the Description of a problem.

	But we can use this to our advantage. We can devise a Solution where we
	don't need a Hash Set.

	How are we going to do that? We need some extra memory, right?
	True, but it turns out that we can use our array nums as the
	"extra memory", that is, we don't need extra memory really. That doesn't
	count.

	Algorithm Example:
	Use Input Array as "Extra" Memory
		nums = [3, -3, 6, 3]	// Hash Set (kind of)

	Again, remember that our Solution set is: [1, ..., nums.size() + 1]
	So for every value out of [1, ..., nums.size()] (NOT the nums.size() + 1)
	we have a corresponding index in our original array nums.

	1           will be mapped to 0th index
	2           will be mapped to 1st index
	...
	nums.size() will be mapped to (nums.size() - 1)th index
	

	So, how are we going to use this original array as our Hash Set? How are
	we going to use this Input array to tell us, in Constant time, O(1), if
	the values, say, 2, exist in our input array?

	The way we're going to do it is, we're going to say:
		index = 2 - 1
	
	And we're going to check if nums[index] is a NEGATIVE value. Why? Because
	we will make it so that negative integers represent that at that index
	there is a right number.
		At index 2, value 3 is present.
		At index 5, value 4 is present.
	
	If at those indexes are some negative values. It's not like that from the
	outset, from the input array they gave to us, but we're going to modify it
	to be like that.

	Also, it's important to note that negative values at certain indexes aren't
	telling us where are those values in the array. It ONLY tells us that they
	exist in the input array nums.

	But there is one problem - It turns out that this Input array, at the
	beginning, already have negative values in it.

	So, how are we going to handle that?
	It turns out that negative numbers, once we iterate through the array
	trying to find the smallest, are USELESS to us. As well as 0's.

	If we were to take every negative value in the original Input array that
	they gave to us, and crossed it, it would NOT matter.

	So, first thing we're going to do is we're going to go through the array
	and replace every negative number with 0.

	Why 0?
	Well, because 0 is also a USELESS number in the Input array and it's not a
	negative number, which we will use.
	If we were to replace it with, say, 1 that wouldn't not be correct since we
	would change the Input array in the way that matters and that could give us
	different result in the end. Which is, obviously, forbidden.
	And we, obviously, cannot leave a negative value since that would mix with
	the indicators we're trying to devise to help us solve this problem.

	So we only have two options:
		1) 0's
		2) Positive Integers
	
	Since positive integers would change the end result, 0's are the only
	option.

	Look at our example:
		nums = [3, -3, 6, 3]
	if we were to change negative values to, say, 1
		nums = [3, 1, 6, 3]
	
	Now the smallest wouldn't be 1, but 2. Which shows that we would change the
	end result of a given example of that specific Input array which isn't
	right. We can't do that.

	Anyway, after we "scan" through the array and replace it with 0's, we're
	actually going to have to "scan" 2 more times.

	So it's going to be O(3 * n), but that's still O(n). And since we're using
	Input array as the "extra memory", that makes Space Complexity O(1), which
	is exactly what is required.

	So let's see how this works:
	        nums = [3, 0, 6, 3]
	                i
	
	I)
		i = 0
		x = nums[i] - 1
		Mark nums[x] to a negative value of that number if it's not 0 or
		negative value, since we're going to have negative values again because
		in this iteration we're the ones that are going to make them, but they
		will represent something else and they won't be useless.
		(Remember that we changed this Input array to have 0's in the place
		where negative numbers existed)

		So:
			x = nums[0]
			x = 3 - 1 = 2
		
		if (nums[2] > 0)
			nums[2] = -nums[2];
		
		So, once we get to i == 2, we will try to index a negative index, so in
		this whole "for loop" we're actually going to use abs(nums[i]), every
		single time, to avoid "undefined ubehavior".


	II)
		i = 1
		x = abs(nums[i]) - 1 => x = 0 - 1 = -1 => nums[-1] => Out of Bounds

		So we're not going to be filling values that are Out of Bounds.
	

	III)
		i = 2
		x = abs(nums[i]) - 1 = abs(-6) - 1 = 6 - 1 = 5 => nums[5] => Out of 
		Bounds

		We know that it wouldn't be a Solution anyway because it's too big. It
		doesn't not belong in [1, 2, ..., nums.size() + 1] Solution set.
	

	IV)
		i = 3
		x = abs(nums[i]) - 1 = 3 - 1 = 2 => nums[2] == negative value, so it
		means that value 3 does already exist in the array nums. If it's
		already negative, we don't want to change it back to a positive number,
		because, remember, 3 does appear in our array and we still want to know
		in Constant time O(1), that 3 exists in this array nums.

	
	So, for our 3rd loop, we're actually going to be iterating not through the
	Input array nums, but through:
		[1, ..., nums.size()]        // Not [1, ..., nums.size() + 1]
	So that's also O(n).

	Modified Input array:
	        nums = [3, 0, -6, 3]
	
	Loop i [1 ... nums.size()] // Inclusive both sides

	Is nums[i] a NEGATIVE value? No.
		If (Yes) then that means that:
			value: (i + 1) exist in the Input array, so we continue
			iterating with n.

		Else // (No) then we've found our Solution
			return i + 1

	Loop:
		for n from [1..n]
		I)
			n = 1
			i = n - 1 = 1 - 1 = 0

			Is nums[0] a NEGATIVE value? No!
				If (No) then we've found our Solution
					return i + 1

			It means that (i + 1) is the smallest positive integer that is
			absent in out Input array, thus we're returning it.



	There's one edge case:
	        nums = [3, 0, -6, 3]
	
	Notice how -6 was originally 6, but we've changed it to -6, because we
	still wanted to know which value was originally stored. But we also wanted
	it negative so that we could see if 3 existed in our Input array.

	But the Question is - What if the value that we're changing to a negative
	value, to indicated that certain number does appear in the Input array, was
	0?

	What if we had:
	        nums = [3, 0, -6, 3, 2]
	
	We would have to mark that 2 does appear in the Input array. But once we
	try to invert a number on index 1(2 - 1), then we would try to invert a 0.

	What do we do in that case?

	Can we change it to a, say, -1? No! We can't do that because that would,
	again, make a difference on the end result, which is forbidden.

	We would eventually take abs(-1) which is 1 and at index[1] and thus we
	would assume that value of 1 exists in the Input array, which is NOT true.
	Originally, there never existed a positive 1 in the original Input array
	they gave to us.

	So we can't do that since it would change the Solution of the given
	example, which is absurd.

	So, then... How do we get around this?
	We have to change it to a negative value that DOES NOT affect the Solution.

	Remember THE SOLUTION SET COULD ONLY BE from this Set:
		{1, 2, ..., nums.size() + 1}
	
	So if we change it to, say, -(nums.size() + 1), then we're not changing the
	Solution Set.

	Well, technically, abs(-(nums.size() + 1)) could exist in the Solution Set,
	but indexing it would be Out of Bounds:
		abs(-(nums.size() + 1)) = (nums.size() + 1) - 1 = nums.size() =>
		=> nums[nums.size()] Out of Bounds.
	
	So that is a good default value to give it.

	**********************
	*** Maybe we could ***
	**********************
	For the edge case where the original value is 0, in addition to setting
	something out of bounds, could we also just set it to the actual value its
	representing?
	Example:
		when 2 exists in [-1 , 0, ... ], could we set it to -2?
		That way we dont change the values in our input array since 2 is marked
		as existing already at some other place.]
	
	We could, but maybe it would be more confusing for reading.

	So I'm going to leave it like this.

*/

/* ========= */
/* === N === */
/* ========= */

/* Time  Beats: 46.46% */
/* Space Beats: 33.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int firstMissingPositive(std::vector<int>& nums)
	{
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] < 0)
				nums[i] = 0;
		}

		for (int i = 0; i < nums.size(); i++)
		{
			int value = std::abs(nums[i]);
			if (1 <= value && value <= nums.size())
			{
				if (nums[value - 1] > 0)
					nums[value - 1] *= -1;
				else if (nums[value - 1] == 0)
					nums[value - 1] = -1 * (nums.size() + 1);
			}
		}

		for (int i = 1; i < nums.size() + 1; i++)
		{
			if (nums[i - 1] >= 0)
				return i;
		}

		return nums.size() + 1;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Put each number in its right place.
	It's kind of like sorting, but not exactly. We're sure that we will "swap"
	at worst n times, while trying to "sort".
	Thus this makes it O(n) which is required.


	It's important to notice that the return value has to be from this set of
	values:
		{1, 2, ..., num.size(), nums.size() + 1}

	Once we see that, we can come up with this Solution, since we can see that
	we don't have to "sort" values that are greater than "nums.size() + 1".



	We have to put each value at [value - 1]th index in array nums, using the
	"swap" function.
	
	Example:
	We find number 4 in our array "nums" and we should swap it with nums[3]

	Once we have "sorted" the array, the first place where its number is not
	right, return position + 1;

	We iterate through an entire array and check if the number is greater
	than 0 and less or equals to n, since we only consider positive integers.
	And if we have all the positive integers from 1 to n in our array, then
	return n + 1.

	If the number is between 1 and n then if that number(nums[i]) is not in
	the right place, that is:
		nums[nums[i] - 1] != nums[i]
	
	then swap it to a place where its supposed to be. Then again, within the
	while loop do this again - Place the current number under nums[i] to its
	right place in the array. That is:
		nums[nums[i] - 1] = nums[i]
	
	If we are doing multiple swaps for a single value of 'i', and we are
	iterating through an entire array, you may ask - how is it possible that a
	complexity is still O(n)?

	We will have multiple swaps for i == 0(in our example below), but as we
	iterate we will have less and less swap. Sometimes 1, and most of the
	times 0.

	In the end the total amount of swaps in an entire for loop is <= n.

	Our example: (Before 1st Iteration)
	[7, 1, 4, 9, 2, 8, 3, 5]

	1st iteration (i == 0)
		[3, 1, 4, 9, 2, 8, 7, 5]
		[4, 1, 3, 9, 2, 8, 3, 5]
		[9, 1, 3, 4, 2, 8, 7, 5]
	
	2nd iteration (i == 1)
		[1, 9, 3, 4, 2, 8, 7, 5]
	
	3rd iteration (i == 2)
		// Nothing has changed

	4th iteration (i == 3)
		// Nothing has changed

	5th iteration (i == 4)
		[1, 2, 3, 4, 9, 8, 7, 5]

	6th iteration (i == 5)
		[1, 2, 3, 4, 9, 5, 7, 8]
		[1, 2, 3, 4, 5, 9, 7, 8]

	7th iteration (i == 6)
		// Nothing has changed

	8th iteration (i == 7)
		// Nothing has changed


	**************************
	*** Counting the swaps ***
	**************************
	1st iteration
		3 swaps
	
	2nd iteration
		1 swap
	
	3rd iteration
		0 swaps (nums[2] == 3) // It's a CORRECT_SLOT
	
	4th iteration
		0 swaps (nums[3] == 4) // It's a CORRECT_SLOT

	5th iteration
		2 swaps
	
	6th iteration
		1 swap
		
	7th iteration
		0 swaps (nums[6] == 7) // It's a CORRECT_SLOT
	
	8th iteration
		0 swaps (nums[7] == 8) // It's a CORRECT_SLOT

		
	Total number of swaps = 3 + 1 + 2 + 1 = 7 <= n
	
	Therefore - Time Complexity is O(n)
	
	Complexity explained:
	Consider nums[i] = i + 1 as a CORRECT_SLOT

		i) CORRECT_SLOT will never be changed; for CORRECT_SLOT,
		nums[nums[i] - 1] always equals to nums[i].

		ii) For each std::swap, the number of CORRECT_SLOT's increases by
		at least 1.
		Position: nums[nums[i] - 1] = nums[i] becomes CORRECT_SLOT after
		std::swap, and according to i) this MUST be a new CORRECT_SLOT

		iii) The maximum of CORRECT_SLOTs <= n
	
	Therefore, Time complexity is O(n)

	In other words:
	We visit each number once, and each number will be put in its right place
	at most once.
	So, the first part is O(n), and the iterating again through the array is
	also O(n), that makes it:
		O(n) + O(n) => O(2 * n) => O(n).
*/


/* Time  Beats: 72.30% */
/* Space Beats: 50.54% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient{
public:
	int
	firstMissingPositive(std::vector<int>& nums)
	{
		int n = nums.size();

		for (int i = 0; i < n; i++)
		{
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
				std::swap(nums[i], nums[nums[i] - 1]);
		}

		for (int i = 0; i < n; i++)
		{
			if (nums[i] != i + 1)
				return i + 1;
		}

		return n + 1;
	}
};


int
main()
{
	Solution sol;
	Solution_Efficient sol_eff;

	/* Example 1 */
	// std::vector<int> nums = {1, 2, 0};

	/* Example 2 */
	// std::vector<int> nums = {3, 4, -1, 1};

	/* Example 3 */
	// std::vector<int> nums = {7, 8, 9, 11, 12};

	/* Example 4 */
	std::vector<int> nums = {7, 1, 9, 2, 6, 3, 5};

	std::cout << "\n\t==============================";
	std::cout << "\n\t=== FIRST MISSING POSITIVE ===";
	std::cout << "\n\t==============================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	// int first_positive = sol.firstMissingPositive(nums);
	int first_positive = sol_eff.firstMissingPositive(nums);


	/* Write Output */
	std::cout << "\n\tOutput: " << first_positive << "\n\n";

	return 0;
}
