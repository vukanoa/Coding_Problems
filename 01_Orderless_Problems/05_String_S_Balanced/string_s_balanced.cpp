#include <iostream>

/*
	Balanced:
	()
	()(())()
	()()()

	Not Balanced:
	(
	)()(
	))((

	My example:
	) (()) ))(
*/

int
solution(std::string &S)
{
	int cnt = 0;
	int ret = 0;

	for(int i = 0; i < S.length(); i++)
	{
		if (S[i] != '(' && S[i] != ')')
			continue;
		else if (S[i] == '(')
		{
			if (i > 0 && S[i-1] == ')')
				cnt = 0;

			cnt++;
		}
		else if (S[i] == ')')
		{
			cnt--;
			if (cnt < 0)
				ret++;
		}
	}
	ret += cnt;

	return ret;
}

int
main()
{
	/* Balanced with letters */
	// std::string S = "()P";
	// std::string S = "(P)";
	// std::string S = "P()";

	/* Balanced */
	// std::string S = "()";
	// std::string S = "()(())()";
	// std::string S = "()()()";

	/* Not Balanced */
	std::string S = ")(())))(";
	// std::string S = "(";
	// std::string S = ")()(";
	// std::string S = "))((";

	int sol = solution(S);
	std::cout << "\n\n\tString: " << S << "\n\n\n";
	std::cout << "\tSolution is: " << sol << "\n\n\n";


	return 0;
}
