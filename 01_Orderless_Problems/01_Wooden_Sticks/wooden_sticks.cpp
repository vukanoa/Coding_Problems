#include <iostream>

int solution (int A, int B);

int
main()
{
	// int x = solution(10, 21);
	// int x = solution(21, 10);
	// int x = solution(5, 21);
	// int x = solution(4, 21);

	// int x = solution(2, 1);
	// int x = solution(1, 8);

	// int x = solution(15, 18);
	// int x = solution(13, 31);
	int x = solution(13, 13);

	std::cout << "\n\tSolution is: " << x << std::endl << std::endl;

	return 0;
}


int
solution (int a, int b)
{
	if (a <= 0 && b <= 0)
		return 0;
	else if (a <= 0 && b <= 3)
		return 0;
	else if (a <= 3 && b <= 0)
		return 0;
	else if (a + b <= 3)
		return 0;
	
	int t_a = a;
	int t_b = b;
	
	if (a < b)
	{
		while (b / a < 3)
			a--;

		if (a < b/4)
			return b/4;
		else
		{
			if (a < t_a/2)
				return t_a/2;

			return a;
		}
	}
	else
	{
		while (a / b < 3)
			b--;

		if (b < a/4)
			return a/4;
		else
		{
			if (b < t_b/2)
				return t_b/2;

			return b;
		}

	}

	return 0;
}
