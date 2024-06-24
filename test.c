#include <stdio.h>

#define COLOR_RESET   "\x1b[0m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_PURPLE  "\x1b[35m"
#define COLOR_GREY    "\x1b[37m"

// Variadic Macros for Logging
#define LOGI(...) printf(COLOR_GREEN "INFO: " __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGW(...) printf(COLOR_YELLOW "WARNING: " __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGE(...) printf(COLOR_RED "ERROR: " __VA_ARGS__); printf(COLOR_RESET "\n")

#define LOGG(...) printf(COLOR_GREEN __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGB(...) printf(COLOR_BLUE __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGP(...) printf(COLOR_PURPLE __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGY(...) printf(COLOR_YELLOW __VA_ARGS__); printf(COLOR_RESET "\n")
#define LOGGR(...) printf(COLOR_GREY __VA_ARGS__); printf(COLOR_RESET "\n")


int main(void)
{
    LOGI("This is an info message with value: %d", 10);
    LOGW("This is a warning message");
    LOGE("This is an error message");

    LOGG("This is a green message");
    LOGB("This is a blue message");
    LOGP("This is a purple message");
    LOGY("This is a yellow message");
    LOGGR("This is a grey message");

    return 0;
}