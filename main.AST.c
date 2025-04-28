#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef  enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIRECTION,
    NODE_ARGUMENT,
    NODE_ENV_VAR
} NodeType;

typedef struct ASTNode
{
    NodeType type;
    char **args; // Arguments for the command
    char *filename; // Filename for redirection
    struct ASTNode *left; // Left child
    struct ASTNode *right; // Right child
} ASTNode;

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	ft_count_word(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	*free_all(char **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	*ft_allocate_word(const char **s, char c)
{
	const char	*start = *s;
	int			len;
	char		*word;

	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = calloc((ft_count_word(s, c) + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			ptr[i] = ft_allocate_word(&s, c);
			if (!ptr[i])
				return (free_all(ptr, i));
			i++;
		}
	}
	return (ptr);
}


int is_redirection(char *tokens)
{
    return ( strcmp(tokens, ">") == 0 ||
             strcmp(tokens, ">>") == 0 ||
             strcmp(tokens, "<") == 0 ||
             strcmp(tokens, "<<") == 0 );
}

// ---------------------------------------

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
            // if (!last_cmd)
            // {
            //     printf("Syntax error: Pipe without preceding command\n");
            //     return NULL;
            // }
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
            // if (!tokens[i + 1])
            // {
            //     printf("Syntax error: Missing file for redirection\n");
            //     return NULL;
            // }

            // if (!last_cmd)
            // {
            //     printf("Syntax error: Redirection without a command\n");
            //     return NULL;
            // }

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


void printf_AST(ASTNode *node, int depth)
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
    printf_AST(node->left, depth + 1);
    printf_AST(node->right, depth + 1);
}


int main()
{
    char *input = "cat < input.txt | grep foo > output.txt";
    char **tokens = ft_split(input, ' '); // Tokenize the input
    ASTNode *root = build_node(tokens); // Build the AST

    printf_AST(root, 0); // Print the AST

    // Free allocated memory (not shown here)
    return 0;
}
