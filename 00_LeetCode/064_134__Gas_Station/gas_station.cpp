#include <iostream>
#include <vector>
#include <numeric> // for accumulate

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	134) Gas Station
	===========================

	============
	Description:
	============

	There are 'n' gas stations along a circular route, where the amount of gas
	at the i-th is "gas[i]".

	You have a car with an unlimited gas tank and it costs "cost[i]" of gas to
	travel from the i-th station to its next (i + 1)-th station. You begin the
	journey with an empty tank at one of the gas stations.

	Given two integers arrays "gas" and "cost", return the starting gas
	station's index if you can travel around the circuit once in the clockwise
	direction, otherwise return "-1". If there exists a solution, it is
	guaranteed to be unique.

	======================================================================
	FUNCTION: int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
	======================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  gas = [1, 2, 3, 4, 5], cost = [3, 4, 5, 1, 2]
	Output: 3
	Explanation:
	Start at station 3(index 3) and fill up with 4 units of gas.
	Your tank = 0 + 4 = 4;
	Travel to station 4. Your tank = 4 - 1 + 5 = 8
	Travel to station 0. Your tank = 8 - 2 + 1 = 7
	Travel to station 1. Your tank = 7 - 3 + 2 = 6
	Travel to station 2. Your tank = 6 - 4 + 3 = 5
	Travel to station 3. The cost is 5. Your gas is just enough to travel back
	to station 3.
	Therefore, return 3 as the starting index.

	--- Example 2 ---
	Input:  gas = [2, 3, 4], cost = [3, 4, 3]
	Output: -1
	Explanation:
	You can't start at station 0 or 1, as there is not enough gas to travel to
	the next station. Let's start at station 2 and fill up with 4 unit of gas.
	Your tank = 0 + 4 = 4
	Travel to station 0. Your tank = 4 - 3 + 2 = 3
	Travel to station 1. Your tank = 3 - 3 + 3 = 3
	You cannot travel back to station 2, as it requires 4 unit of gas but you
	only have 3.
	Therefore, you can't travel around the circuit once no matter where you
	start.

	*** Constraints ***
	n == gas.length == cost.length
	1 <= n <= 10^5
	0 <= gas[i], cost[i] = 10^4

*/



/*
	============
	=== NOTE ===
	============

	This Problem was taken down from Top 100 Liked Questions on LeetCode.

	This Problem is not intuitive to me at all. It's a very weird form of
	Greedy Algorithm.
	
*/



/*
	------------
	--- IDEA ---
	------------

	They say that this Problem is similar to 53_Maximum_Subarray because it
	also uses Kadane's Algorithm.



	It is said that if there is a solution it is guaranteed to be unique.
	So either there is a solution and it's the only one, or there isn't.

	If our total_gas < total_cost then in that case we can't complete our
	journey, so will return -1.

	Checking:
		if (total_gas is less than total_cost)
	is the same as checking:
		if (total_gas - total_cost is less than 0)

	If total_gas >= total_cost then that means there is only one solution.
	Meaning there is only a single station we could start from to be able
	to successfully complete the cycle.

	To find that gas station will will keep track of the "tank".
	tank = gas[i] - cost[i];

	Let's suppose at any index our "tank"(current gas) became negative so we
	can clearly say that till that index all the gas station between i-th
	starting point are bad, starting point as well.

	That means we can start trying at the next gas station on the i+1 station.


	Example: gas = [1, 2, 3, 4, 5]  cost = [3, 4, 5, 1, 2]

	 i  gas  cost   tank        start
	––– –––  ––––   –––––––––   –––––
	 start = 0              0     0
	 0   1    3    0+1-3 = -2     1    reset tank to 0, start to 0+1 = 1
	 1   2    4    0+2-4 = -2     2    reset tank to 0, start to 1+1 = 2
	 2   3    5    0+3-5 = -2     3    reset tank to 0, start to 2+1 = 3
	 3   4    1    0+4-1 =  3     3
	 4   5    2    3+5-2 =  6     3

*/

/* Time  Beats: 54.90% */
/* Space Beats: 88.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Kadane {
public:
	int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost)
	{
		int total = 0;
		int tank  = 0;
		int start = 0;

		for (int i = 0; i < gas.size(); i++)
		{
			total += gas[i] - cost[i];
			tank  += gas[i] - cost[i];

			if (tank < 0)
			{
				start = i + 1;
				tank = 0;
			}
		}

		return (total >= 0) ? start : - 1;
	}
};



/*
	------------
	--- IDEA ---
	------------

	The "std::accumulate" function takes three arguments:
		1. Starting point of the vector
		2. Ending point of the vector
		3. Initial value
	
	It's equivalent to Python function: sum(array)

	This Problem is not intuitive to me at all. It's a very weird form of
	Greedy Algorithm.

	Important thing to note is that if the total sum of gas isn't greater or
	equal to total sum of cost, then there is NO Solution. In that case just
	return -1.

	We're doing that with std::accumulate.

	However, afterwards, this is absolutely not intuitive.

	In Example 1:
		gas  = [ 1,  2,  3,  4,  5]
		cost = [ 3,  4,  5,  1,  2]
	
		diff = [-2, -2, -2,  3,  3]
	
	Once we start from the index 3, where the value is positive, and we
	continue and not "dip" under the 0 until the end, then THAT index is the
	Solution.
	We DON'T go around trying to subtract the remaining ones. This is why it's
	absolutely not intuitive.


	There are 3 comments that I've found that are explaining this a bit better.

	I)
		Actually, the reason why it works is simple, and it happens because of
		two factors.
			1) If you moved to some value, and your total sum is greater than
			   zero, then it means, that previous values did bring some value
			   to the outcome.

			   For example, we have gas = [2,3,0] and cost = [0,0,5].

			   If we take just solely value 3 without 2, it wouldn't be enough
			   to pass the last station, but previous values definitely bring
			   some value to the outcome.

			2) If we know, that there's definitely has to be a solution.
			   Then, we may assume, that it has to be the smallest possible
			   value, as I said before it may bring the most value to the
			   result.


	
	II) 
		The solution would click if you try to apply the pattern as in:
			Kadane's Algorithm.
		Try to build a solution from the starting index, once you are certain
		that it can no longer be an answer, forget everything and consider the
		next index.
		


	III)
		I will try to explain it in my own way-- please be patient and read it,
		hope you will get the intuition behind the algorithm.

		There are 4 parts to it.

		Part 1) 
			Sum of gas array>=sum of cost array, Therefore: very intuitive, we
			should always have enough gas.


		Part 2)
			We are keeping a total+=gas[i]-cost[i] for each i, and whenever it
			is < 0 we are skipping that point and moving forward,
			making total 0, Therefore, it means we ran out of gas if we started
			at some point which was <= current pos of i, so now we have to find
			a new starting position, which wall be > curr pos of i.

			Now think, why will this new start lie ahead of curr pos i, not
			anywhere before it,  you could think, we started from point
				A------>B(total till +ve)------->C(total<0),
			as per this algo we try to find start ahead of C, what if we
			started from B and skipped A instead, well that won't work.
			You moved from A--------> B with some positive value(or 0), or else
			you would have stopped right at B and made total to 0. So add A
			improved our chances of having a positive total, so there is no
			point in looking for the new position start anywhere behind point
			C.


		Part 3)
			When the total stays +ve, we dn't do anything to the start point,
			our start pointer points to the first index when our total became
			positive.

			Again this is similar to the above explanation.
			Lets suppose we start from
				X(-ve)--->Y(-ve)--->A(+ve)---->B(+ve)---->C(+ve),
			where C is the end of the array, our start(which is also the ans)
			would be A.

			Why not B? why not C?

			It is because we moved from A to B with some +ve value or atleast
			0, whereas if we started from B we would have had only the value of
			B so earlier point added some value to our total, so its more
			favorable to help us reach the ans, hence earliest point is always
			better.


		Part 4)
			Why we just stop at point C and don t complete the cycle and check.

			It is because from Part 1 we would have already identified that if
			the given set of inputs will have an ans, so if we have reached to
			Part 3 it means we surely have an ans, and it is mentioned in the
			question that there is only one valid ans, so we will always choose
			the most favorable ans-- which is also the fundamental idea of
			Greedy Algorithims. There is also a mathematical proof for this,
			that if we got a start point given our total gas >=total cost, we
			will be able to reach back to that point with just enough gas. 

*/

/* Time  Beats: 83.49% */
/* Space Beats: 88.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat {
public:
	int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost)
	{
		int gas_sum  = std::accumulate(gas.begin(),  gas.end(), 0);
		int cost_sum = std::accumulate(cost.begin(), cost.end(), 0);

		/* There is NO Solution */
		if (gas_sum < cost_sum)
			return -1;

		/* There is certainly a Solution */
		int n = gas.size();

		int total = 0;
		int start = 0;

		for (int i = 0; i < n; i++)
		{
			total += gas[i] - cost[i];

			if (total < 0)
			{
				total = 0;
				start = i + 1;
			}
		}

		return start;
	}
};


int
main()
{
	Solution_Kadane sol_kadane;
	Solution_Neat sol_neat;

	/* Example 1 */
	std::vector<int> gas  = {1, 2, 3, 4, 5};
	std::vector<int> cost = {3, 4, 5, 1, 2};

	/* Example 2 */
	// std::vector<int> gas  = {2, 3, 4};
	// std::vector<int> cost = {3, 4, 3};

	/* Example 3 */
	// std::vector<int> gas  = {3, 1, 1};
	// std::vector<int> cost = {1, 2, 2};

	/* Example 4 */
	// std::vector<int> gas  = {7, 1, 0, 11, 4};
	// std::vector<int> cost = {5, 9, 1, 2, 5};

	/* Example 5 */
	// std::vector<int> gas  = {2};
	// std::vector<int> cost = {9};

	/* Example 6 */
	// std::vector<int> gas  = {5};
	// std::vector<int> cost = {3};


	std::cout << "\n\t===================";
	std::cout << "\n\t=== GAS STATION ===";
	std::cout << "\n\t===================\n";


	/* Write input */

	// Gas
	bool first = true;
	std::cout << "\n\tGas:  [";
	for (auto x: gas)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	// Cost
	first = true;
	std::cout << "\n\tCost: [";
	for (auto x: cost)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int solution = sol_kadane.canCompleteCircuit(gas, cost);
	// int solution = sol_neat.canCompleteCircuit(gas, cost);


	/* Write output */
	std::cout << "\n\tStarting Gas Station is: " << solution << "\n\n";


	return 0;
}
