#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>


/*
	==========
	Complexity
	==========
	
	O(n*logn) - Time
	O(R)      - Space, where R is Number of Unique elements in Original array
*/

int
solution(std::vector<int>& A)
{
	/* Set & Map */
	std::unordered_set<int> set;
	std::map<int, int> map;

	// O(n*logn)       // O(logn) is the time for insert in Red-Black Tree
	for(const int& x: A)
		set.insert(x); // Fill with unique elements

	// O(n)
	for(const int& x: A) // Fill hash table with occurence per each unique element
		map[x]++;

	// O(R), where R is Number of Unique elements, R <= N -> O(N)
	// for (auto x : map)
	// 	std::cout << "[" << x.first << "] = " << x.second << std::endl;


	set.clear();

	/* Maps */
	std::map<int, int> occur;
	std::map<int, int> to_del;

	int ret_count = 0;
	int tmp = 0;


	std::vector<int>::iterator it;

	// O(n*logn)
	for(it = A.begin(); it != A.end();)
	{
		int index = std::distance(A.begin(), it);
		if (!set.count(*it)) // If exists in the set
		{
			if (occur[map[*it]] == 0) // If that num of occurence hasn't happened
			{
				occur[map[*it]] = *it;
				set.insert(*it); // O(logn)
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

				set.insert(*it); // O(logn)
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
