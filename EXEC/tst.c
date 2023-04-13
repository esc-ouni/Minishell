#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av, char **env)
{
    int tmpin = dup(0);
    int tmpout = dup(1);

    //set initial
    int	fdin;
    if(infile)
	fdin = open(infile, O_RDONLY);
    else
	fdin = dup(tmpin);
    int ret;
    int	fdout;

    for (i = 0; i < numsimplecommands; i++)
    {
	//redirect input
	dup2(fdin, 0);
	close(fdin);
	//set output
	if (i == numsimplecommands - 1)
	{
	    //last simple command
	    if (outfile)
	    	fdout = open(outfile, O_TRUNC | O_CREAT | O_WRONLY);
        else
            fdout = dup(tmpout);
    }
    else
    {
        int fdpipe[2];
        pipe(fdpipe);
        fdout=fdpipe[1];
        fdin = fdpipe[0];
    }
    dup2(fdout, 1);
    close(fdout);
    }
    printf("%d\n", in);
    printf("%d\n", out);
    while (1);
}
