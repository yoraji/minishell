#include "../includes/minishell.h"

#include "../includes/minishell.h"

void execute_pipeline(ASTNode *node, t_data *data)
{
    int pipefd[2];
    int pid;
    int input_fd = 0; // Initialize input_fd to 0 (stdin)
    int status;       // Declare the status variable

    while (node)
    {
        if (node->type == NODE_PIPE)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            // Fork a child process
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0) // Child process
            {
                dup2(input_fd, STDIN_FILENO);  // Redirect input
                dup2(pipefd[1], STDOUT_FILENO); // Redirect output
                close(pipefd[0]); // Close the read end of the pipe
                close(pipefd[1]); // Close the write end of the pipe
                if (node->left->type == NODE_COMMAND)
                    execute_builtin(node->left, data);
                exit(EXIT_SUCCESS);
            }
            else // Parent process
            {
                close(pipefd[1]); // Close the write end of the pipe
                input_fd = pipefd[0]; // Save the read end of the pipe for the next command
            }
            node = node->right;
        }
        else if (node->type == NODE_COMMAND)
        {
            pid = fork();
            if (pid == 0) // Child process
            {
                dup2(input_fd, STDIN_FILENO); // Redirect input
                execute_builtin(node, data);
                exit(EXIT_SUCCESS);
            }
            else // Parent process
            {
                waitpid(pid, &status, 0); // Wait for the child process to finish
                break;
            }
        }
    }
    close(input_fd); // Close the last input_fd
    while (wait(NULL) > 0) // Wait for all child processes to finish
        ;
}
