# SYSTEM INSTRUCTIONS: STRICT 42 NORMINETTE
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables).
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function.
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.

# YOUR TASK: WIRING, INTEGRATION & MAKEFILE
The core execution logic is built, but it is not connected to the main loops, headers, and compiler. You must update the existing files to wire everything together.

**Task 1: Update the `Makefile`**
- Read the provided `Makefile`.
- Locate the `SRCS` list.
- Add the new files generated in the previous steps (e.g., `src/execution/execute_multiple.c`, `src/utils/exec_signals.c`, or wherever you placed the pipeline and signal logic) to the `SRCS` variable so they get compiled.
- Output the fully updated `Makefile`.

**Task 2: Update `minishell.h`**
- Scan all `.c` files in the execution, signal, and cleanup folders.
- Add the prototypes for `ft_execute_multiple`, signal handlers, here-doc cleanup, and any other missing public functions to `minishell.h`.
- Output the fully updated `minishell.h`.

**Task 3: Update `src/process/executor.c`**
- Modify `ft_executor(t_data *data)` so that it correctly routes the execution.
- If `data->cmds->next == NULL`, call `ft_executor_single(data)`.
- If `data->cmds->next != NULL`, call `ft_execute_multiple(data)`.
- Output the fully updated `executor.c`.

**Task 4: Update `src/main/minishell.c`**
- Include the call to the here-doc cleanup function (e.g., `ft_cleanup_heredocs(data.cmds)`) right after `ft_executor(&data)` finishes, so temporary files are deleted.
- Change the final return statement of the `main` function from `return (0);` to `return (data.exit_code);`.
- Non-Interactive Mode: Ensure the `readline` prompt is only printed if `isatty(STDIN_FILENO)` is true. If false, do not print visual effects or the prompt string.
- Output the fully updated `main.c`.

Output ONLY the updated code for `Makefile`, `minishell.h`, `executor.c`, and `main.c`. Do not explain the code.