#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool	cmp_str(char *test_case, const char *got, const char *exp, char *detail);
bool	cmp_nstr(char *test_case, const char *got, const char *exp, size_t n, char *detail);
bool	cmp_int(char *test_case, int got, int exp, char *detail);
bool	cmp_bool(char *test_case, int got, int exp, char *detail);
bool wildcmp(char *s1, size_t sz1, char *s2, size_t sz2);

typedef struct {
    char  *desc;
    char  *text;
    char  *pattern;
    bool  expexted;
} WildCmpTestCases_t;

WildCmpTestCases_t tests_cases[] = {
    {"0", "main.c", "main.*", true},
    {"1", "main.c", "*.c", true},
    {"2", "main.c", "m*a*i*n*.*c*", true},
    {"3", "main.c", "main.c", true},
    {"4", "main.c", "m*c", true},
    {"5", "main.c", "ma********************************c", true},
    {"6", "main.c", "*", true},
    {"7", "main.c", "***", true},
    {"8", "main.c", "m.*c", false},
    {"9", "main.c", "**.*c", true},
    {"10", "main-main.c", "ma*in.c", true},
    {"11", "main", "main*d", false},
    {"12", "abc", "*b", false},
    {"13", "file.txt", "*.txt", true},
    {"14", "file.txt", "f*e*t*", true},
    {"15", "file.txt", "f*x", false},
    {"16", "file.txt", "*file.txt", true},
    {"17", "file.txt", "file.txt*", true},
    {"18", "file.txt", "*file.txt*", true},
    {"19", "file.txt", "*file*txt*", true},
    {"20", "file.txt", "*.*", true},
    {"21", "file.txt", "*file*", true},
    {"22", "file.txt", "*f*i*l*e*.*t*x*t*", true},
    {"23", "file.txt", "f*", true},
    {"24", "file.txt", "*t", true},
    {"25", "file.txt", "*x", false},
    {"26", "*", "*", true},
    {"27", "b", "b", true},
    {"28", "a", "a", true},
    {"29", "", "a*", false},
    {"30", "abcd", "*a*", true},
    {"31", "abcd", "*z*", false},
    {"32", "abcd", "*b*d", true},
    {"33", "abcd", "*bc*d", true},
    {"34", "abcd", "*abcde*", false},
    {"35", "a.c", "*.c", true},
    {"36", "a.c", "*.*", true},
    {"37", "a.c", "*.", false},
    {"38", "a.c", "a*", true},
    {"39", "a.c", "*c", true},
    {"40", "t.c", "t*.cpp", false},
    {"41", "main.c", "m*a*i*n*.*c*", true},
    {"42", "main.c", "m*a*i*n*******.*", true},
    {"43", "main.c", ".*", false},
    {"44", ".git", ".", false},
    {"45", "aabcdefgh", "abcd*", false},
};

int main()
{
    WildCmpTestCases_t test;
    bool r;

    for (int i = 0; i < sizeof(tests_cases) / sizeof(tests_cases[0]); i++)
    {
	test = tests_cases[i];
	r = wildcmp(test.text, strlen(test.text), test.pattern, strlen(test.pattern));
	if (cmp_bool(test.desc, r, test.expexted, NULL))
	    printf("✅ %s\n", test.desc);
	else 
	{
	    printf("IN (INPUT): `%s`\n", test.text);
	    printf("IN (PASTERN): `%s`\n", test.pattern);
	    return (1);
	}
    }
    return (0);
}

