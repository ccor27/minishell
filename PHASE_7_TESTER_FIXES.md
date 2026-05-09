# SYSTEM INSTRUCTIONS: STRICT 42 NORMINETTE
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables).
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function. No inline initialization.
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.

# YOUR TASK: TESTER EDGE CASES
Our minishell is failing specific edge cases on the automated tester. Update the following logic. Output ONLY the updated `.c` files.

**Task 1: Fix `export` validation (`src/built_in/export.c`)**
- In bash, a valid identifier for export must start with a letter or underscore, and contain only alphanumeric characters or underscores.
- Before adding/updating a variable in `ft_export_arg`, check if the key is a valid identifier.
- If it is invalid, print `minishell: export: `[arg]`: not a valid identifier` to STDERR, and ensure `data->exit_code = 1`. Do not add it to the environment.

**Task 2: Fix `exit` numeric signs (`src/built_in/exit.c`)**
- `ft_is_numeric` currently fails if a number has a sign (`+100` or `-100`).
- Update `ft_is_numeric` to allow a single `+` or `-` at the very beginning of the string (index 0).

**Task 3: Redirection Exit Codes (`src/process/execute_redirect.c` & `src/process/executor.c`)**
- When `open()` fails in `ft_handle_input_redir` or `ft_handle_output_redir`, the function returns `1`. 
- Ensure that in `ft_executor_single` and `ft_handle_child_process`, if `ft_apply_redirections` returns `1`, the execution is halted, and `data->exit_code` is set to `1`.

**Task 4: Error Codes 126 vs 127 (`src/process/execute_external.c`)**
- Currently, if a command isn't found, we exit `127`.
- If the user types a path like `./test_files/invalid_permission` and it exists but lacks execution rights (`access(cmd, F_OK) == 0` but `access(cmd, X_OK) == -1`), or if it is a directory, the shell MUST exit with `126` and print "Permission denied" or "Is a directory".
- Update `ft_execute_external` to check these specific access states and exit with the correct code (`126` or `127`).

**Task 5: Empty Expansion (`src/process/executor.c`)**
- If the user types `$EMPTY` (a variable that doesn't exist), the expander reduces it to an empty string. The executor currently tries to execute it and fails.
- In `ft_executor_single` and `ft_handle_child_process`, add a guard clause: If `cmd->args[0]` is an empty string `""` (or NULL), do not attempt to execute external commands. Set exit code to 0 and return.