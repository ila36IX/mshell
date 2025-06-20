# define UNIMPLEMENTED(...)                                                  \
	printf("%s:%d: UNIMPLEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define UNREACHABLE(...)                                                  \
	printf("%s:%d: UNREACHABLE: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define TODO(...)                                                  \
	printf("%s:%d: TODO: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

# define PANIC(...)                                                  \
	printf("%s:%d: PANIC: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);
