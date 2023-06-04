
#include <libc.h>

void signal_handler(int signum, siginfo_t *info, void *context) {
    int argument = info->si_int;  // Retrieve the argument from siginfo_t
    printf("Received signal %d with argument %d\n", signum, argument);
    // Handle the signal
    // ...
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;

    // Set up the argument value
    int argument = 42;

    // Pass the argument using sigaction
    sigemptyset(&sa.sa_mask);
    sa.sa_restorer = NULL;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sa.sa_mask = 0;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_restorer = NULL;
    sigaction(SIGINT, &sa, NULL);

    // Rest of your code

    return 0;
}
