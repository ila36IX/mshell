#include "stdbool.h"
#include "stdio.h"
#include "string.h"

bool	cmp_str(char *test_case, const char *got, const char *exp, char *detail)
{
	if (exp == NULL && got == NULL)
		return (true);
	if (exp && got && strcmp(got, exp) == 0)
		return (true);
	printf("Error\n");
	printf("Case: %s\n", test_case);
	if (detail)
		printf("In: %s\n", detail);
	printf("\"%s\" != \"%s\"\n", exp ? exp : "(nil)", got ? got : "(nil)");
	return (false);
}

bool	cmp_nstr(char *test_case, const char *got, const char *exp, size_t n,
		char *detail)
{
	if (exp == NULL && got == NULL)
		return (true);
	if (exp && got && strncmp(got, exp, n) == 0)
		return (true);
	printf("Error\n");
	printf("Case: %s\n", test_case);
	if (detail)
		printf("In: %s\n", detail);
	printf("\"%.*s\" != \"%.*s\"\n", (int)n, exp ? exp : "(nil)", (int)n,
		got ? got : "(nil)");
	return (false);
}

bool	cmp_int(char *test_case, int got, int exp, char *detail)
{
	if (exp == got)
		return (true);
	printf("Error\n");
	printf("\tCase: %s\n", test_case);
	if (detail)
		printf("In: %s\n", detail);
	printf("%d != %d\n", exp, got);
	return (false);
}

bool	cmp_bool(char *test_case, int got, int exp, char *detail)
{
	if (exp == got)
		return (true);
	printf("Error\n");
	printf("\tCase: %s\n", test_case);
	if (detail)
		printf("In: %s\n", detail);
	printf("exp(%s) != got(%s)\n", exp ? "true" : "false", got ? "true" : "false");
	return (false);
}
