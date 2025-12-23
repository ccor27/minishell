#include "minishell.h"

// Function to print the startup banner
void print_header(void)
{
    // \033[1;36m = Bold Cyan Color
    printf("\033[1;36m");
    printf("\n");
    // The ASCII Art (notice the double backslashes \\)
    printf("  __  __ _       _     _          _ _          \033[1;33m[o_o]\033[1;36m \n");
    printf(" |  \\/  (_)     (_)   | |        | | |        \033[1;33m/[\033[1;36m_\033[1;33m]\\\033[1;36m \n");
    printf(" | \\  / |_ _ __  _ ___| |__   ___| | |         \033[1;33md b\033[1;36m \n");
    printf(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |        \n");
    printf(" | |  | | | | | | \\__ \\ | | |  __/ | |        \n");
    printf(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|        \n");
    printf("\n");
    // \033[0m = Reset color back to normal
    printf("\033[0m");
}
