# mshell
Hello again shell

![](https://i.imgur.com/5FfYegU.png)

# Lexer

![Imgur](https://i.imgur.com/pVV17oz.png)

The lexer is responsible for taking raw input string `"ls -l /home"` and breaking it down into these meaningful tokens such as:

- **Operators**: `|`, `>>`, `<<`, `&&`, `||`, `>`, `<`
- **Words**: Any sequence of characters not identified as an operator or special delimiter.
- **Quoted Strings**: Handles both double (`"..."`) and single (`'...'`) quoted strings, preserving their content.

## Tests

**Note:** Your source code must not contain any `main` function.

```sh
cd tests
make all # to run all tests
make lexer # to test only the lexer
# more command is comming
```

Available tests are:

`make lexer`: Check if the lexer is producing the expected tokens with expected length and type and white space surrounded  

# G-Collector
### Minimal memory management method

![g-Collector](https://imgs.search.brave.com/QoVxQlpC5Wwcf_XiEH3SKXkn2FwdhpXgWxONvrbmbWE/rs:fit:860:0:0:0/g:ce/aHR0cHM6Ly9jcmFm/dGluZ2ludGVycHJl/dGVycy5jb20vaW1h/Z2UvZ2FyYmFnZS1j/b2xsZWN0aW9uL3Jl/Y3ljbGUucG5n)

## Garbage Collector

### Overview
The garbage collector implements automatic memory management using a singly linked list to track all allocated memory blocks. Each allocation is monitored through a lightweight tracking system that maintains complete visibility over memory usage while providing flexible cleanup options.

### Implementation
When `ft_malloc()` is called, memory is allocated and automatically tracked by adding a new node to the linked list using `ft_gcadd_back()`. Each node contains the address and metadata of the allocated block, creating a comprehensive registry of all active allocations. Individual blocks can be selectively removed from tracking using `ft_gcremove()` for precise memory management.

### Memory Management
The `ft_gc_clear()` function provides bulk cleanup by traversing the entire linked list to deallocate all tracked memory blocks and reset the collector's state. This approach ensures complete memory tracking with minimal overhead, prevents memory leaks, and offers both granular control through selective removal and comprehensive cleanup through bulk operations.
