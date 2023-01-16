#include <iostream>
#include <vector>

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
	------------
	--- IDEA ---
	------------

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


/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
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

int
main()
{
	Solution sol;

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
	int solution = sol.canCompleteCircuit(gas, cost);

	/* Write output */
	std::cout << "\n\tStarting Gas Station is: " << solution << "\n\n";

	return 0;
}
