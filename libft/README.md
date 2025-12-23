# Libft

## 📚 Project Overview

The `Libft` project is a fundamental part of the 42 curriculum. Its primary goal is to re-implement a selection of standard C library functions from scratch, as well as create some additional utility functions. This project serves as an introduction to C programming, memory management, and the creation of custom libraries.

By completing `Libft`, students solidify their understanding of:

* **C Language Fundamentals:** Pointers, arrays, strings, data types, and control flow.
* **Memory Management:** Proper use of `malloc`, `free`, `calloc`, and understanding memory allocation/deallocation.
* **Function Reimplementation:** Deep dive into how common standard library functions work under the hood.
* **Static Libraries:** Learning to compile source files into a `.a` static library for reuse in future projects.
* **Makefile Usage:** Mastering `Makefile` creation for efficient compilation and project management.

## ⚙️ Supported Functions (Mandatory Part)

The mandatory part of `Libft` includes reimplementing a variety of `libc` functions, categorized as:

* **`ctype.h` functions:** `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`
* **`string.h` functions:** `ft_strlen`, `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_memchr`, `ft_memcmp`, `ft_strnstr`, `ft_atoi`, `ft_strdup`
* **`stdlib.h` functions:** `ft_calloc`
* **Additional functions:** `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`, `ft_striteri`, `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

Each function is prefixed with `ft_` to denote its custom implementation.

## ✨ Bonus Part (Linked List Functions)

The bonus part extends the library with a set of functions for manipulating **singly linked lists**. These functions are crucial for understanding data structures and are frequently used in subsequent 42 projects.

The `t_list` structure is defined as:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
```

## New features

* **printf:** function that works as print() function but just wiht numbers, strings and pointers
