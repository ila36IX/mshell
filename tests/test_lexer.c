#include "../main.h"

typedef struct {
    char  *desc;
    char  *input_string;
    t_token expected_tokens[50];
    int          num_expected_tokens;
} LexerTestCase_t;

LexerTestCase_t test_cases[] = {
    {
	"Empty input string", "", {}, 0
    },
    {
	"Only whitespace", "   \t\n   ", {}, 0
    },
    {
	"Single word", "Heatblast", {
	    {TOKEN_WORD, "Heatblast", 9, false}
	}, 1
    },
    {
	"Two words", "echo Hello", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_WORD, "Hello", 5, true}
	}, 2
    },
    {
	"Words with multiple spaces", "Ben   Ten   Rocks", {
	    {TOKEN_WORD, "Ben", 3, false},
	    {TOKEN_WORD, "Ten", 3, true},
	    {TOKEN_WORD, "Rocks", 5, true}
	}, 3
    },
    {
	"Pipe operator", "ls | wc", {
	    {TOKEN_WORD, "ls", 2, false},
	    {TOKEN_PIPE, "|", 1, true},
	    {TOKEN_WORD, "wc", 2, true}
	}, 3
    },
    {
	"Input redirect", "cat < file.txt", {
	    {TOKEN_WORD, "cat", 3, false},
	    {TOKEN_IN, "<", 1, true},
	    {TOKEN_WORD, "file.txt", 8, true}
	}, 3
    },
    {
	"Output redirect", "echo > out.log", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_OUT, ">", 1, true},
	    {TOKEN_WORD, "out.log", 7, true}
	}, 3
    },
    {
	"Append redirect", "echo >> Omnitrix", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_APPEND, ">>", 2, true},
	    {TOKEN_WORD, "Omnitrix", 8, true}
	}, 3
    },
    {
	"Heredoc redirect", "cat << EOF", {
	    {TOKEN_WORD, "cat", 3, false},
	    {TOKEN_HEREDOC, "<<", 2, true},
	    {TOKEN_WORD, "EOF", 3, true}
	}, 3
    },
    {
	"AND operator", "cmd1 && cmd2", {
	    {TOKEN_WORD, "cmd1", 4, false},
	    {TOKEN_AND, "&&", 2, true},
	    {TOKEN_WORD, "cmd2", 4, true}
	}, 3
    },
    {
	"OR operator", "cmd1 || Vilgax", {
	    {TOKEN_WORD, "cmd1", 4, false},
	    {TOKEN_OR, "||", 2, true},
	    {TOKEN_WORD, "Vilgax", 6, true}
	}, 3
    },
    {
	"Double quoted string", "\"Upgrade\"", {
	    {TOKEN_DQ, "Upgrade", 7, false}
	}, 1
    },
    {
	"Single quoted string", "'Diamondhead'", {
	    {TOKEN_SQ, "Diamondhead", 11, false}
	}, 1
    },
    {
	"Empty double quotes and word", "\"\" Ghostfreak", {
	    {TOKEN_DQ, "", 0, false},
	    {TOKEN_WORD, "Ghostfreak", 10, true}
	}, 2
    },
    {
	"Empty single quotes", "''", {
	    {TOKEN_SQ, "", 0, false}
	}, 1
    },
    {
	"Complex command", "echo \"hello world of XLR8\" | wc -l >> 'Ripjaws Log.txt'", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_DQ, "hello world of XLR8", 19, true},
	    {TOKEN_PIPE, "|", 1, true},
	    {TOKEN_WORD, "wc", 2, true},
	    {TOKEN_WORD, "-l", 2, true},
	    {TOKEN_APPEND, ">>", 2, true},
	    {TOKEN_SQ, "Ripjaws Log.txt", 15, true},
	    {TOKEN_NULL, NULL, 0, false}
	}, 8
    },
    {
	"Operators touching words", "cat<file>out", {
	    {TOKEN_WORD, "cat", 3, false},
	    {TOKEN_IN, "<", 1, false},
	    {TOKEN_WORD, "file", 4, false},
	    {TOKEN_OUT, ">", 1, false},
	    {TOKEN_WORD, "out", 3, false}
	}, 5
    },
    {
	"Operators touching each other", "echo >>| cat", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_APPEND, ">>", 2, true},
	    {TOKEN_PIPE, "|", 1, false},
	    {TOKEN_WORD, "cat", 3, true}
	}, 4
    },
    {
	"Unclosed double quote", "echo \"Waybig is here", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_INVALID, "Enclosing \" or '", 16, true}
	}, 2
    },
    {
	"Unclosed single quote", "echo 'Stinkfly", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_INVALID, "Enclosing \" or '", 16, true}
	}, 2
    },
    {
	"Single quote inside double quote", "word'is'word", {
	    {TOKEN_WORD, "word", 4, false},
	    {TOKEN_SQ, "is", 2, false},
	    {TOKEN_WORD, "word", 4, false},
	}, 3
    },
    {
	"String with operators inside quotes", "echo \"Ben|Gwen > Kevin\"", {
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_DQ, "Ben|Gwen > Kevin", 16, true}
	}, 2
    },
    {
	"Input ending with operator", "FourArms >", {
	    {TOKEN_WORD, "FourArms", 8, false},
	    {TOKEN_OUT, ">", 1, true}
	}, 2
    },
    {
	"Input starting with whitespace", "   Wildmutt \t >>", {
	    {TOKEN_WORD, "Wildmutt", 8, true},
	    {TOKEN_APPEND, ">>", 2, true}
	}, 2
    },
    {
	"Sequential operators with no space", ">>outfile<<infile", {
	    {TOKEN_APPEND, ">>", 2, false},
	    {TOKEN_WORD, "outfile", 7, false},
	    {TOKEN_HEREDOC, "<<", 2, false},
	    {TOKEN_WORD, "infile", 6, false},
	    {TOKEN_NULL, NULL, 0, false},
	    {TOKEN_NULL, NULL, 0, false},
	    {TOKEN_NULL, NULL, 0, false},
	    {TOKEN_NULL, NULL, 0, false},
	    {TOKEN_NULL, NULL, 0, false},
	    {TOKEN_NULL, NULL, 0, false},
	}, 9
    },
    {
	"One double quote", "\"", {
	    {TOKEN_INVALID, "Enclosing \" or '", 16, false}
	}, 1
    },
    {
	"Unclosed quotes at EOF after word", "GreyMatter '\"", {
	    {TOKEN_WORD, "GreyMatter", 10, false},
	    {TOKEN_INVALID, "Enclosing \" or '", 16, true}
	}, 2
    },
    {
	"Unclosed DQ exactly at content_len (no null)",
	"echo \"Oops",{
	    {TOKEN_WORD, "echo", 4, false},
	    {TOKEN_INVALID, "Enclosing \" or '", 16, true}
	}
	, 2
    },
    {
	"Mix of symbols", "Upgrade+Azmuth << ' Galvan Prime ' && Vilgax||'0'Zs'Skayr",
	{
	    {TOKEN_WORD, "Upgrade+Azmuth", 14, false},
	    {TOKEN_HEREDOC, "<<", 2, true},
	    {TOKEN_SQ, " Galvan Prime ", 14, true},
	    {TOKEN_AND, "&&", 2, true},
	    {TOKEN_WORD, "Vilgax", 6, true},
	    {TOKEN_OR, "||", 2, false},
	    {TOKEN_SQ, "0", 1, false},
	    {TOKEN_WORD, "Zs", 2, false},
	    {TOKEN_INVALID, "Enclosing \" or '", 16, false}
	}, 9
    }
    ,{
	"Case of having varaibles staring with '$'", "cat \"$@\" | wc -l >\"$filename\"",
	{
	    {TOKEN_WORD, "cat", 3, false},
	    {TOKEN_DQ, "$@", 2, true},
	    {TOKEN_PIPE, "|", 1, true},
	    {TOKEN_WORD, "wc", 2, true},
	    {TOKEN_WORD, "-l", 2, true},
	    {TOKEN_OUT, ">", 1, true},
	    {TOKEN_DQ, "$filename", 9, false},
	}, 7
    }
    ,{
	"Crazy mix", "''\"\"||><<<0>>|>||w|||<>a><b>> ' c \n\t '  |",
	{
	    {TOKEN_SQ, "", 0, false},
	    {TOKEN_DQ, "", 0, false},
	    {TOKEN_OR, "||", 2, false},
	    {TOKEN_OUT, ">", 1, false},
	    {TOKEN_HEREDOC, "<<", 2, false},
	    {TOKEN_IN, "<", 1, false},
	    {TOKEN_WORD, "0", 1, false},
	    {TOKEN_APPEND, ">>", 2, false},
	    {TOKEN_PIPE, "|", 1, false},
	    {TOKEN_OUT, ">", 1, false},
	    {TOKEN_OR, "||", 2, false},
	    {TOKEN_WORD, "w", 1, false},
	    {TOKEN_OR, "||", 2, false},
	    {TOKEN_PIPE, "|", 1, false},
	    {TOKEN_IN, "<", 1, false},
	    {TOKEN_OUT, ">", 1, false},
	    {TOKEN_WORD, "a", 1, false},
	    {TOKEN_OUT, ">", 1, false},
	    {TOKEN_IN, "<", 1, false},
	    {TOKEN_WORD, "b", 1, false},
	    {TOKEN_APPEND, ">>", 2, false},
	    {TOKEN_SQ, " c \n\t ", 6, true},
	    {TOKEN_PIPE, "|", 1, true},
	    {TOKEN_NULL, NULL, 0, false},
	}, 24
    },
    {
	"Only parentheses", "()",
	{
	    {TOKEN_OPAREN, "(", 1, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_NULL, NULL, 0, false},
	}, 3
    },
    {
	"Words and parentheses", "test(this)",
	{
	    {TOKEN_WORD, "test", 4, false},
	    {TOKEN_OPAREN, "(", 1, false},
	    {TOKEN_WORD, "this", 4, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_NULL, NULL, 0, false},
	}, 5
    },
    {
	"Parentheses inside parentheses", "test((this))",
	{
	    {TOKEN_WORD, "test", 4, false},
	    {TOKEN_OPAREN, "(", 1, false},
	    {TOKEN_OPAREN, "(", 1, false},
	    {TOKEN_WORD, "this", 4, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_NULL, NULL, 0, false},
	}, 5
    },
    {
	"parentheses with operators", "(true | (ls)) && (ls || false)",
	{
	    {TOKEN_OPAREN, "(", 1, false},
	    {TOKEN_WORD, "true", 4, false},
	    {TOKEN_PIPE, "|", 1, true},
	    {TOKEN_OPAREN, "(", 1, true},
	    {TOKEN_WORD, "ls", 2, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_AND, "&&", 2, true},
	    {TOKEN_OPAREN, "(", 1, true},
	    {TOKEN_WORD, "ls", 2, false},
	    {TOKEN_OR, "||", 2, true},
	    {TOKEN_WORD, "false", 5, true},
	    {TOKEN_CPAREN, ")", 1, false},
	    {TOKEN_NULL, NULL, 0, false},
	}, 14
    },
};

int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

bool check_tokens_equality(char *test_case, t_token got, t_token exp)
{
    bool pass;

    pass = true;
    pass = pass && cmp_int(test_case, got.kind, exp.kind, "Token type");
    pass = pass && cmp_int(test_case, got.whitespace_before, exp.whitespace_before, "White space before");
    pass = pass && cmp_int(test_case, got.text_len, exp.text_len, "Token length");
    if (pass)
	pass = pass && cmp_nstr(test_case, got.text, exp.text, got.text_len, "Token text");
    return (pass);
}

bool run_test(LexerTestCase_t test)
{
    t_lexer lexer = lexer_new(test.input_string, ft_strlen(test.input_string));
    t_token token;
    bool pass = true;

    for (int i = 0; i < test.num_expected_tokens; i++)
    {
	token = lexer_next_token(&lexer);
	pass = pass && check_tokens_equality(test.desc, token, test.expected_tokens[i]);
    }
    if (test.num_expected_tokens == 0)
    {
	token = lexer_next_token(&lexer);
	if (token.kind != TOKEN_NULL)
	{
	    pass = false;
	    printf("Error: %s\n", test.desc);
	    printf("No tokens should be return");
	}
    }
    if (pass)
	printf("✅ %s\n", test.desc);
    else
	printf("❌ %s\n", test.desc);
    return (pass);
}

int main()
{
    for (int i = 0; i < num_test_cases; i++)
    {
	run_test(test_cases[i]);
    }
}
