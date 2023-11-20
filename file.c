/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:49:37 by idouni            #+#    #+#             */
/*   Updated: 2023/11/20 16:03:38 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
int exit_with_error(char *err_msg);
int cd(char **cd_command, int count);
int execute(char **current_commad, char **env, int count);






int exit_with_error(char *err_msg){
	if (err_msg){
		for (int i = 0; err_msg[i]; i++){
			write(2, &err_msg[i], 1);
		}
	}
	return (1);
}

int cd(char **argv, int idx){
	if (idx != 2)
		return (exit_with_error("cd error\n"));
	if (chdir(argv[1]) == -1)
		return (exit_with_error("error : cannot cd "), exit_with_error(argv[1]), exit_with_error("\n"));
	return (0);
}

int execute(char **argv, char **env, int idx){
	int fds[2];
	int pid = 1;
	int there_is_pipe = 0;

	// CHECK IF THERE'S A PIPE
	if (argv[idx] && !strcmp(argv[idx], "|")){
		there_is_pipe = 1;
		// CREATE A PIPE
		if(pipe(fds) == -1){
			return (exit_with_error("error fatal: pipe failed\n"));
		}
	}

	// FORK
	pid = fork();
	if (!pid){
		// SET THE END OF THE COMMAND TO NULL
		argv[idx] = NULL;
		// DUP THE STDOUT TO THE PIPE && CLOSE PIPE'S ENDS
		if (there_is_pipe){
			if(dup2(fds[1], 1) == -1 || close(fds[0]) == -1 || close(fds[1]) == -1)
				return (exit_with_error("error fatal\n"));
		}
		// EXECUTE THE COMMAND
		if (execve(*argv, argv, env) == -1){
			return (exit_with_error("cannot execute "), exit_with_error(*argv), exit_with_error("\n"));
		}
	}
	// WAUT FOR THE COMMAND AND SAVE IT'S RETURN 
	waitpid(pid, NULL, 0);
	// DUP THE STDIN TO THE PIPE && CLOSE PIPE'S ENDS
	if (there_is_pipe){
		if (dup2(fds[0], 0) == -1 || close(fds[1]) == -1 || close(fds[0]) == -1)
			return (exit_with_error("error fatal\n"));
	}
	return (0);
}

int main(int argc, char **argv, char **envp) {
    int status = 0;

    if (argc <= 1) {
        return 0; // No commands to process
    }

	// SKIP THE EXECUTABLE NAME
    char **current_cmd = argv + 1;
    char **next_cmd = NULL;
	
    int i;

    while (current_cmd) {
        i = 0;
		// SEARCH FOR ; OR | 
        while (current_cmd[i] && strcmp(current_cmd[i], "|") != 0 && strcmp(current_cmd[i], ";") != 0) {
            i++;
        }

		// SET NEXT COMMAND
        if (current_cmd[i] && current_cmd[i+1]) {
            current_cmd[i] = NULL;
            next_cmd = current_cmd + i + 1; // Skip the separator
        } else {
            next_cmd = NULL;
        }

		// EXECUTE THE COMMAND IF IT'S CD OR ELSE
        if (!strcmp(*current_cmd, "cd")) {
            status = cd(current_cmd, i);
        } else {
            status = execute(current_cmd, envp, i);
        }
		
		// TO THE NEXT COMMAND
        current_cmd = next_cmd;
    }
	// RETURN THE STATUS OF THE LAST EXECUTED PROCCESS
    return status;
}
