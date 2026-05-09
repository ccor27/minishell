# SYSTEM INSTRUCTIONS: STRICT 42 NORMINETTE
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables). **THIS IS CRITICAL.**
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function. No inline initialization.
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.

# BUG REPORT & CONTEXT
File to fix: `src/main/minishell.c`

**Bug 1: Tester Echoing & Parsing Failures**
When the tester pipes commands (non-interactive mode), `isatty(STDIN_FILENO)` is false. 
- If we use `readline("")`, the tester environment automatically echoes the command to stdout, causing duplicate output errors.
- If we use `get_next_line(STDIN_FILENO, 0)`, it solves the echo, but it leaves a `\n` at the end of the string, which completely breaks the `ft_strncmp` parser (e.g., it searches for "echo\n" instead of "echo").

**Bug 2: Norminette Violation**
Fixing this logic previously pushed `ft_main_loop` to 33 lines, which violates the 25-line maximum rule.

# YOUR TASK: THE NORM-COMPLIANT FIX
You must update `src/main/minishell.c` to fix both bugs while strictly passing the 42 Norminette.

1. Create a new helper function: `static char *ft_get_input(void)`
   - Inside this function, check `isatty(STDIN_FILENO)`.
   - If interactive: return `readline("minishell$> ")`.
   - If non-interactive: get the string using `get_next_line(STDIN_FILENO, 0)`. If the string exists and ends with `\n`, replace the `\n` with `\0` to strip it safely. Return the cleaned string.
   - This function MUST be under 25 lines.

2. Update `static void ft_main_loop(t_data *data)`
   - Replace the reading logic by simply calling `input = ft_get_input();`.
   - This will instantly reduce `ft_main_loop` to well under 25 lines.

3. Output the fully updated `src/main/minishell.c` file. Do not provide explanations, only the C code.