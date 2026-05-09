# MINISHELL MASTER PLAN - FINAL PHASES

## SYSTEM PERSONA & STRICT 42 NORMINETTE RULES
Act as an expert C programmer and a strict evaluator for the 42 School "Minishell" project.
You must strictly adhere to the following rules for all code generation:
1. Maximum 5 functions per `.c` file.
2. Maximum 25 lines of code per function (excluding header, braces, and variables).
3. Maximum 4 local variables declared per function.
4. Maximum 4 parameters per function.
5. All variables must be declared at the very top of the function. No inline initialization (e.g., `int i = 0;` is FORBIDDEN).
6. Only `while` loops are allowed. NO `for` loops. NO ternary operators.
7. Include a brief Doxygen-style comment above every function.

## ARCHITECTURE CONTEXT
The Initialization, Lexer, Parser, Expander, Built-ins, and Single Command Execution are fully complete.
- Data struct: `t_data` holds `env`, `cmds`, `tokens`, and `exit_code`.
- Command struct: `t_cmd` is a linked list where each node has `args`, `redirects`, and a pointer to the `next` command.
- Existing tools available to use: `ft_apply_redirections(t_cmd *cmd)`, `ft_execute_builtin(...)`, `ft_execute_external(...)`.

---

## EXECUTION INSTRUCTIONS
Wait for me to prompt you with "Execute Phase X" before generating any code. Only generate the code requested in that specific phase. Do not write ahead.

### PHASE 1: The Pipeline Engine Basics (`ft_execute_multiple`)
**Goal:** Create the main loop to handle piped commands.
- Create a new file `src/execution/execute_multiple.c`.
- Write the function `void ft_execute_multiple(t_data *data)`.
- Loop through the `data->cmds` linked list.
- Use `pipe()` to create an array of 2 integers (`fd[2]`) for every command except the last one.
- Use `fork()` to create a child process for each command.
- In the parent process: close the write-end of the pipe, and save the read-end into a variable (e.g., `prev_fd`) to pass it to the next iteration of the loop. 

### PHASE 2: Child Process Routing (Inside the Pipeline)
**Goal:** Wire the inputs/outputs and run the command.
- Write a helper function: `void ft_handle_child_process(t_cmd *cmd, t_data *data, int *fd, int prev_fd)`.
- If `prev_fd` exists (not the first command), use `dup2()` to connect it to `STDIN`.
- If `cmd->next` exists (not the last command), use `dup2()` to connect the pipe's write-end (`fd[1]`) to `STDOUT`.
- Close all unused pipe file descriptors in the child to prevent hanging.
- Call `ft_apply_redirections(cmd)` (this will overwrite `dup2` if the user provided specific `<` or `>` symbols).
- If `ft_execute_builtin()` returns false/0, call `ft_execute_external()`. Call `exit()` appropriately.

### PHASE 3: Parent Process Waiting & Exit Status
**Goal:** Wait for the pipeline to finish and capture `$?`.
- Write a helper function called at the very end of `ft_execute_multiple` (after the loop finishes).
- Use a `while` loop with `waitpid(-1, &status, 0)` to wait for ALL child processes.
- We only care about the exit status of the *last* command in the pipeline. Capture `WEXITSTATUS(status)` when the PID returned by `waitpid` matches the PID of the last command forked.
- Save this final status into `data->exit_code`.

### PHASE 4: Signal Overrides & Here-Doc Cleanup
**Goal:** Polish the execution behavior to match Bash exactly.
- Write a function `void ft_exec_signals(void)` to update signal handlers during execution: `SIGINT` (Ctrl-C) should print a newline, and `SIGQUIT` (Ctrl-\) should print "Quit: 3". Neither should kill the parent shell.
- Call `ft_exec_signals()` right before executing commands, and restore the default interactive signals right after the wait loop finishes.
- Write `void ft_cleanup_heredocs(t_cmd *cmds)` to loop through all commands and redirections. If a redirection is `HERE_DOC`, use `unlink(redir->file)` to delete the temporary `.tmp_heredoc_*` files from the hard drive.