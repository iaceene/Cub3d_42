<h1 align="center">Libft</h1>

Libft is a custom library of standard C functions developed as part of the 42 school curriculum. The goal of this project is to recreate common standard library functions, along with a few additional utilities, to better understand how these functions work internally and to practice writing efficient, reusable code.

## Table of Contents

- [Introduction](#introduction)
- [Functions](#functions)
- [Usage](#usage)
- [Compilation](#compilation)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Source Files](#source-files)

## Introduction

Libft is a foundational project in the 42 curriculum designed to help students build a better understanding of C programming, memory management, pointers, and data structures. The project involves implementing a set of standard functions (such as `strlen`, `memset`, and `strjoin`) and other utility functions that can be used in future projects.

## Functions

Libft includes the following categories of functions:

1. **Libc Functions**: Reimplementations of standard C library functions.
2. **Additional Functions**: Utility functions not present in the standard C library.
3. **Bonus**: Functions for handling linked lists.

### Some of the re-implemented functions include:

- `ft_memset`
- `ft_bzero`
- `ft_memcpy`
- `ft_strlen`
- `ft_strchr`
- `ft_strdup`
- `ft_atoi`
- `ft_toupper`
- `ft_tolower`

For a full list of functions, see the [function list](#).

## Usage

1. Clone the repository:
    ```bash
    git clone https://github.com/iaceene/libft.git
    ```

2. Navigate to the `libft` directory:
    ```bash
    cd libft
    ```

3. Compile the library:
    ```bash
    make
    ```

4. Include the compiled library (`libft.a`) in your C project:
    ```c
    #include "libft.h"
    ```

## Compilation

Libft is compiled using the provided Makefile. The following commands can be used to compile and manage the library:

- `make`: Compiles the library.
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the library.
- `make re`: Recompiles the library from scratch.

## Testing

You can test your `libft` implementation using external testers:

- [libft-unit-test](https://github.com/alelievr/libft-unit-test)
- [libft-war-machine](https://github.com/ska42/libft-war-machine)
- [libft-tester](https://github.com/Tripouille/libftTester)

Simply clone these repositories and run the tests.

## Contributing

Contributions are welcome! If you find any bugs or want to add new features, feel free to open an issue or create a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Source Files

Here are the source files included in the `libft` library:

### Standard Functions (`src`):

- `ft_strlen.c`
- `ft_strrchr.c`
- `ft_toupper.c`
- `ft_bzero.c`
- `ft_isascii.c`
- `ft_memcpy.c`
- `ft_putnbr_fd.c`
- `ft_striteri.c`
- `ft_strmapi.c`
- `ft_strtrim.c`
- `ft_atoi.c`
- `ft_itoa.c`
- `ft_isalpha.c`
- `ft_putendl_fd.c`
- `ft_strdup.c`
- `ft_isdigit.c`
- `ft_memset.c`
- `ft_split.c`
- `ft_strjoin.c`
- `ft_strncmp.c`
- `ft_substr.c`
- `ft_isalnum.c`
- `ft_isprint.c`
- `ft_putchar_fd.c`
- `ft_strchr.c`
- `ft_strlcpy.c`
- `ft_strnstr.c`
- `ft_tolower.c`
- `ft_calloc.c`
- `ft_memchr.c`
- `ft_memcmp.c`
- `ft_memmove.c`
- `ft_putstr_fd.c`
- `ft_strlcat.c`

### Bonus Functions (`b_src`):

- `ft_lstadd_back_bonus.c`
- `ft_lstadd_front_bonus.c`
- `ft_lstclear_bonus.c`
- `ft_lstdelone_bonus.c`
- `ft_lstiter_bonus.c`
- `ft_lstlast_bonus.c`
- `ft_lstnew_bonus.c`
- `ft_lstsize_bonus.c`
- `ft_lstmap_bonus.c`
