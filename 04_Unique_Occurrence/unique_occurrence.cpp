#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>


/*
	==========
	Complexity
	==========
	
	O(n)      - Time // If we get reeeeally unlucky then O(n^2)
	O(R)      - Space, where R is Number of Unique elements in Original array
*/

int
solution(std::vector<int>& A)
{
	/* Map */
	std::map<int, int> map;

	// O(n)
	for(const int& x: A) // Fill hash table with occurence per each unique element
		map[x]++;

	// O(R), where R is Number of Unique elements, R <= N -> O(N)
	// for (auto x : map)
	// 	std::cout << "[" << x.first << "] = " << x.second << std::endl;


	/* Maps & Set*/
	std::map<int, int> occur;
	std::map<int, int> to_del;
	std::unordered_set<int> set;

	int ret_count = 0;
	int tmp = 0;


	std::vector<int>::iterator it;

	// O(n) // O(n^2) in the very worst case where we have disastrous hash table
	for(it = A.begin(); it != A.end();)
	{
		int index = std::distance(A.begin(), it);
		if (!set.count(*it)) // If exists in the set, O(1), unlikely to be O(n)
		{
			if (occur[map[*it]] == 0) // If that num of occurence hasn't happened
			{
				occur[map[*it]] = *it;
				set.insert(*it); // O(1), it's unlikely that we would have O(n)
				it++;
			}
			else
			{
				tmp = map[*it];
				while (occur[map[*it]] != 0 && map[*it] > 0)
				{
					map[*it]--;
					ret_count++;
				}

				if (map[*it] > 0)
					occur[map[*it]] = *it;

				set.insert(*it); // O(1), it's unlikely that we would have O(n)
				to_del[*it] = tmp - map[*it]; 
				to_del[*it]--;

				A.erase(it);
			}
		}
		else if(to_del[*it] > 0)
		{
			to_del[*it]--;
			A.erase(it);
		}
		else
		{
			it++;
		}
	}

	return ret_count;
}

int
main()
{
	/* Vectors */
	std::vector<int> A = {1, 1, 1, 2, 2, 2};
	// std::vector<int> A = {5, 3, 3, 2, 5, 2, 3, 2};
	// std::vector<int> A = {127, 15, 3, 8, 10};
	// std::vector<int> A = {10000000, 10000000, 5, 5, 5, 2, 2, 2, 1, 1};

	std::cout << "\n\n";
	std::cout << "\tBEFORE:";
	std::cout << "\n\t\t";

	// Print the array BEFORE the call of function solution
	for(const int& x : A)
		std::cout << x << " ";


	int sol = solution(A);
	
	std::cout << "\n\n\n";
	std::cout << "\tSolution is: " << sol;
	std::cout << "\n\n\n";

	std::cout << "\tAFTER:";
	std::cout << "\n\t\t";

	// Print the array AFTER the call of function solution
	for(const int& x : A)
		std::cout << x << " ";

	std::cout << "\n\n";

	return 0;
}
