#include "minishell.h"

void printTYPE(t_enum num) 
{
    switch (num) 
	{
        case WH_SP:
		{
            printf("WH_SP\n");
            break;
		}
        case PIP:
		{
            printf("Pipe\n");
            break;
		}
        case SCMD:
		{
            printf("SCMD\n");
            break;
		}
        case ST_SQ:
		{
            printf("ST_SQ\n");
            break;
		}
        case ST_DQ:
		{
            printf("ST_DQ\n");
            break;
		}
        case R_OA:
		{
            printf("R_OA\n");
            break;
		}
        case R_OT:
		{
            printf("R_OT\n");
            break;
		}
        case R_IN:
		{
            printf("R_IN\n");
            break;
		}
        case R_HD:
		{
            printf("R_HD\n");
            break;
		}
        case FIL_NM:
		{
            printf("FIL_NM\n");
            break;
		}
        default:
            printf("Unknown Type\n");
    }
}

void    after_parse2(t_cmd  *cmd)
{
    int i = 0;
    int i2 = 0;
    t_cmd  *node;

    node = cmd;
    if (!cmd)
        return ;
    while(node)
    {
        printf("\n");
        printf("=> t_cmd %d;\n", i);
        printf("   command     : ");
        // i2 = 0;
        while(node->cmd[i2])
        {
            printf("'%s' ", node->cmd[i2]);
            i2++;
        }
        i2 = 0;
        printf("\n");
        printf("   position    : ");
        printf("f:%d ", node->first_cmd);
        printf("l:%d ", node->last_cmd);
        printf("\n");
        printf("   out_files   : ");
        while(node->out_files)
        {
            printf("'%s'->", node->out_files->filename);
            printf("%d ", node->out_files->islast);
            node->out_files = node->out_files->next;
        }
        printf("\n");
        printf("   in_files    : ");
        while(node->in_files)
        {
            printf("'%s'->", node->in_files->filename);
            printf("%d ", node->in_files->islast);
            node->in_files = node->in_files->next;
        }
        printf("\n");
        printf("   cmd_type    : ");
        printf("%d ", node->builtflag); 
        printf("\n\n");
        i++;
        node = node->next;
    }
}

