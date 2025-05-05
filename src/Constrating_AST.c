/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constrating_AST.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoraji <yoraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:41:09 by yoraji            #+#    #+#             */
/*   Updated: 2025/04/28 11:01:25 by yoraji           ###   ########.fr       */
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
    ASTNode *last_cmd = NULL;
    int i = 0;

    while (tokens[i])
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            ASTNode *pipe_node = create_node(NODE_PIPE, NULL, NULL);
            if (!pipe_node)
                return NULL;
            pipe_node->left = last_cmd;
            if (!root || root->type != NODE_PIPE)
                root = pipe_node;
            else
               current->right = pipe_node;
            current = pipe_node;
            last_cmd = NULL;
            i++;
        }
        else if (is_redirection(tokens[i]))
        {
            ASTNode *redir_node = create_node(NODE_REDIRECTION, NULL, tokens[i + 1]);
            if (!redir_node)
                return NULL;

            if (!last_cmd->right)
                last_cmd->right = redir_node;
            else
            {
                ASTNode *temp = last_cmd->right;
                while (temp->right)
                    temp = temp->right;
                temp->right = redir_node;
            }

            i += 2;
        }
        else
        {
            char **args = malloc(sizeof(char *) * 256);
            if (!args)
            {
                perror("Memory allocation failed");
                return NULL;
            }
            int arg_index = 0;
            while (tokens[i] && strcmp(tokens[i], "|") != 0 && !is_redirection(tokens[i]))
                args[arg_index++] = strdup(tokens[i++]);
            args[arg_index] = NULL;

            ASTNode *cmd_node = create_node(NODE_COMMAND, args, NULL);
            if (!cmd_node)
                return NULL;

            if (!root)
                root = cmd_node;
            else if (current && current->type == NODE_PIPE)
                current->right = cmd_node;

            last_cmd = cmd_node;
            current = cmd_node;
        }
    }
    return root;
}

void print_ast(ASTNode *node, int depth)
{
    if (!node)
        return;
    // Proper indentation
    for (int i = 0; i < depth; i++)
        printf("  ");
    // Print the current node type
    if (node->type == NODE_COMMAND)
    {
        printf("COMMAND: %s", node->args[0]);
        for (int i = 1; node->args[i]; i++)
            printf(" %s", node->args[i]);
        printf("\n");
    }
    else if (node->type == NODE_PIPE)
        printf("PIPE\n");
    else if (node->type == NODE_REDIRECTION)
        printf("REDIRECTION: %s\n", node->filename);
    else
        printf("UNKNOWN NODE TYPE\n");

    // Recursively print children
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}
