#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>


bool
solution(std::vector<int> &A, std::vector<int> &B, int S)
{
	// Invalid input
	if (A.size() != B.size())
		return false;

	// Base case
	if (S < 2 || S > 200000 || A.size() < 1 || A.size() > 100000)
		return false;

	// Less number of doctor's appointments than the number of patients - false
	if (A.size() > S || B.size() > S)
		return false;

	std::map<int, int> map;
	std::unordered_set<int> set;
	std::unordered_set<int> used_indexes;

	// Fill the map with num of occurrence of each number from both vectors
	for(auto x : A)
		map[x]++;

	for(auto x : B)
		map[x]++;

	// If one patient's prefference is a unique number of slot - pick that
	for (auto i : map)
	{
		if (i.second == 1)
			set.insert(i.first); // Remember not to check the index of this element in A & B
	}

	for (int i = 0; i < A.size(); i++)
	{
		if (set.find(A[i]) != set.end())
			used_indexes.insert(i); // K-th element, ignore those afterwards
		else if (set.find(B[i]) != set.end())
			used_indexes.insert(i); // K-th element, ignore those afterwards
	}

	for (int i = 0; i < A.size(); i++)
	{
		// Ignore these, they picked a unique slot
		if (used_indexes.find(i) != used_indexes.end())
			continue;

		if (set.find(A[i]) == set.end())      // A[i] not used yet
			set.insert(A[i]);
		else if (set.find(B[i]) == set.end()) // B[i] not used yet
			set.insert(B[i]);
		else
			return false;
	}

	return true;
}


int
main()
{

	/* Example 1 */
	// std::vector<int> A = {1, 1, 3};
	// std::vector<int> B = {2, 2, 1};
	// int S = 3;

	/* Example 2 */
	// std::vector<int> A = {3, 2, 3, 1};
	// std::vector<int> B = {1, 3, 1, 2};
	// int S = 3;

	/* Example 3 */
	// std::vector<int> A = {2, 5, 6, 5};
	// std::vector<int> B = {5, 4, 2, 2};
	// int S = 8;

	/* Example 4 */
	// std::vector<int> A = {1, 2, 1, 6, 8, 7, 8};
	// std::vector<int> B = {2, 3, 4, 7, 7, 8, 7};
	// int S = 10;

	/* Example 5 */
	std::vector<int> A = {1, 2, 1, 6, 8, 7, 5};
	std::vector<int> B = {2, 3, 4, 7, 7, 8, 7};
	int S = 9;


	bool sol = solution(A, B, S);

	std::cout << "\n\t===================================\n";
	std::cout << "\t===== PATIENTS & APPOINTMENTS =====\n";
	std::cout << "\t===================================\n";

	if (sol)
		std::cout << "\n\tSolution: Possible!\n\n";
	else
		std::cout << "\n\tSolution: NOT Possible!\n\n";

	return 0;
}
