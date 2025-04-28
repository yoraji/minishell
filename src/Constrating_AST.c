/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constrating_AST.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:41:09 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/27 06:16:53 by yoraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ASTNode *create_node(NodeType type, char **args, char *filename)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node)
    {
        perror("Memory allocation failed");
        return NULL;
    }
    node->type = type;
    node->args = args;
    node->filename = filename;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
    Example AST Structure:
        echo hello | grep hello > output.txt
            PIPE
            /    \
         ls -l   COMMAND
                  (grep)
                    |
          grep ".c" > output.txt
*/

int is_redirection(char *tokens)
{
    return ( ft_strcmp(tokens, ">") == 0 ||
             ft_strcmp(tokens, ">>") == 0 ||
             ft_strcmp(tokens, "<") == 0 ||
             ft_strcmp(tokens, "<<") == 0 );
}

ASTNode *build_node(char **tokens)
{
    ASTNode *root = NULL;
    ASTNode *current = NULL;
    int i = 0;

    while (tokens[i])
    {
        printf("Creating node: %s\n", tokens[i]);
        if (ft_strcmp(tokens[i], "|") == 0)
        {
            // Create a PIPE node
            ASTNode *pipe_node = create_node(NODE_PIPE, NULL, NULL);
            if (!pipe_node)
                return NULL;
            if (!root)
                root = pipe_node;
            else
                current->right = pipe_node;

            pipe_node->left = current; // Link the current command to the pipe node
            current = pipe_node; // Move current to the new pipe node
        }
        else if (tokens[i] && is_redirection(tokens[i]))
        {
            // Create a REDIRECTION node
            if (!tokens[i + 1])
            {
                printf("Syntax error: Missing file for redirection\n");
                return NULL;
            }

            ASTNode *redir_node = create_node(NODE_REDIRECTION, NULL, tokens[i + 1]);
            if (!redir_node)
                return NULL;

            if (!current)
            {
                printf("Syntax error: Redirection without command\n");
                return NULL;
            }

            if (!current->right)
                current->right = redir_node;
            else
            {
                ASTNode *temp = current->right;
                while (temp->right)
                    temp = temp->right;
                temp->right = redir_node;
            }
            i++; // Skip the filename token
        }
        else
        {
            // Create a COMMAND node
            char **args = malloc(sizeof(char *) * 256);
            if (!args)
            {
                perror("Memory allocation failed");
                return NULL;
            }

            int arg_index = 0;
            while (tokens[i] && is_redirection(tokens[i]))
            {
                args[arg_index++] = ft_strdup(tokens[i]);
                i++;
            }
            args[arg_index] = NULL;
            ASTNode *cmd_node = create_node(NODE_COMMAND, args, NULL);
            if (!cmd_node)
                return NULL;

            if (!root)
                root = cmd_node;
            else if (current && current->type == NODE_PIPE)
                current->right = cmd_node;
            current = cmd_node;
            continue; // Skip the increment of `i` since it's already handled
        }
        i++;
    }

    return root;
}

void print_ast(ASTNode *node, int depth)
{
    if (!node || !node->left || !node->right)
        return;
    // // Print indentation based on depth
    // for (int i = 0; i < depth; i++)
    //     printf("  ");

    // Print the node type and relevant information
    if (node->type == NODE_COMMAND)
    {
        printf("COMMAND: ");
        for (int i = 0; node->args && node->args[i]; i++)
        {
            printf("%s", node->args[i]);
            if (node->args[i + 1])
                printf(" ");
        }
        printf("\n");
    }
    else if (node->type == NODE_PIPE)
    {
        printf("PIPE\n");
    }
    else if (node->type == NODE_REDIRECTION)
    {
        printf("REDIRECTION: %s\n", node->filename);
    }
    // Recursively print left and right children
    if (node->left)
        print_ast(node->left, depth + 1);
    if (node->right)
        print_ast(node->right, depth + 1);
}
