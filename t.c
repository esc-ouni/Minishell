#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void sigint_handler(int signum) {
    printf("Custom SIGINT handler\n");
}

int main() {
    struct sigaction new_action;
	struct sigaction prev_action;
    sigaction(SIGINT, &new_action, &prev_action);

    // Set up the new action for SIGINT
    new_action.sa_handler = sigint_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    // Save the previous action

    // Run your code with the modified signal behavior
    printf("Running with modified SIGINT handler. Press Ctrl+C...\n");
    // Your code here
	pause();

    // Restore the previous action
    sigaction(SIGINT, &prev_action, NULL);

    // Run your code with the original signal behavior
    printf("Restored the original SIGINT handler. Press Ctrl+C...\n");
    // Your code here
	pause();

    return 0;
}
