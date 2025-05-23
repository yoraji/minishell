

// echo 'hello "world"'
// cmpare the output of the command with the bash command
// echo " ' hello'  welcome whats up " " ' " '

Cases_tests (echo):
/* 
    $? → last exit status.
    $$ → process ID (optional in minishell).
    $VAR where VAR isn’t defined → empty string.
    $VAR → should NOT expand (single quotes prevent expansion).
    "${VAR}" → optional support for braces.
    echo "'hello'  welcome whats up""'"
    echo "hello"
    echo "hello world
    echo 'hello\'world' syntax_error
    echo "'hello \"world\"'"
    echo "hello 'world\'s best' shell"
    echo "She said, \"hello\""
    echo "hello\\world"
    echo 'it'\''s fine'
    echo "hello 'world\'s best' shell"
    cat < input.txt | grep "foo bar" > output.txt
    echo "hello ''world "this is quotes inside quotes"' " " "and even more quotes 'inside more quotes' " "
    echo quotes"' " " "and
    ls -la |grep ".c"
    echo "hello
    echo hello\|world > file\ name
    echo "hello;world" && echo "foo&bar" || echo "baz|qux"
    echo "" '' " " ' '
    echo hello\\
    echo \"hello\"
    echo "hi" ">" "file.txt"
    echo "'\"nested\" quotes'"
    echo "She said, \"hello\""
    echo hello\\world
    echo '"'
    echo "hello; world" | grep "hello" && echo "found" || echo "not found"
    echo "a"'b'
    echo "hello 'nested "quotes"'"
    echo -nnnn -nnnnn -nnndqn adfasf -nnnn
    >
    <
    >>
    <<
    ls >
    cat <
    ls >> | grep foo // !!!
    echo a > > file
    cat <<<< EOF
    ls < > file
    < | > |
    ls | < | echo
    echo hello > | > file
    | | |
    echo hello > file <
    echo hello > file < | echo
    ls > file |
    ls | > file
    ls > > file | grep a
    ls | ; > file
    echo $
    echo $USER$HOME$SHELL
    echo "Path: $PATH is set"
    echo "Your home directory is $HOME"
    echo $SHELL_PATH
    echo \$USER
    echo Hello $USER, welcome to $HOME!
    echo $UNDEFINED_VAR
    echo $USER is logged into $HOME
    echo $USER
    echo $USER$HOME
    echo "hello 'nested "quotes"'"
    ls "-la|grep" ".c"
    ls -la|grep ".c"


    Token: [echo]
    Token: ["'hello']
    / Token: [welcome]
    / Token: [whats]
    / Token: [up""'"]
    Error: Unmatched " quote in token: "'hello'
    echo "hello"

    minishell> echo "hello
    Error: Unmatched " quote in token: hello
    Memory allocation failed: Success

    minishell> echo "hello"
    Token: [echo]
    Token: ["hello"]



    minishell> echo "'hello \"world\"'"
    Token: [echo]
    Token: ["'hello]
    // Token: ["world"'"]

    echo "hello \"world\""

    minishell> echo "hello \"world\""
    Token: [echo]
    Token: ["hello]
    Token: ["world""]
    Error: Unmatched " quote in token: "hello

    echo 'it'\''s fine'

    minishell> echo 'it'\''s fine'
    Token: [echo]
    Token: ['it'''s]
    Token: [fine']
    Error: Unmatched ' quote in token: fine'

    echo "hello 'world\'s best' shell"

    minishell> echo "hello 'world\'s best' shell"
    Token: [echo]
    Token: ["hello]
    Token: ['world's]
    Token: [best']
    Token: ["shell"]
    Error: Unmatched " quote in token: "hello

    minishell> ls -la |grep ".c"
    Token: [ls]
    Token: [-la]
    Token: [|grep]
    Token: [.c]
    Valid Syntax
    minishell>


    cat < input.txt | grep "foo bar" > output.txt

    minishell> cat < input.txt | grep "foo bar" > output.txt
    Token: [cat]
    Token: [<]
    Token: [input.txt]
    Token: [|]
    Token: [grep]
    Token: ["foo]
    Token: [bar"]
    Token: [>]
    Token: [output.txt]
    Error: Unmatched " quote in token: "foo

    cat < input.txt | grep "foo bar" > output.txt
    minishell> cat < input.txt | grep "foo bar" > output.txt
    Token: [cat]
    Token: [<]
    Token: [input.txt]
    Token: [|]
    Token: [grep]
    Token: ["foo]
    Token: [bar"]
    Token: [>]
    Token: [output.txt]
    Error: Unmatched " quote in token: "foo

    echo hello\|world > file\ name

    cat < input.txt > output1.txt >> output2.txt

    echo "hello 'world'" && cat < input.txt | grep "foo" > output.txt || echo "done"

    minishell> echo "hello 'world'" && cat < input.txt | grep "foo" > output.txt || echo "done"
    Token: [echo]
    Token: ["hello]
    Token: ['world'"]
    Token: [&&]
    Token: [cat]
    Token: [<]
    Token: [input.txt]
    Token: [|]
    Token: [grep]
    Token: ["foo"]
    Token: [>]
    Token: [output.txt]

    // echo "hello;world" && echo "foo&bar" || echo "baz|qux"

    //    minishell> echo "hello;world" && echo "foo&bar" || echo "baz|qux"
    //    Token: [echo]
    //    Token: ["hello;world"]
    //    Token: [&&]
    //    Token: [echo]
    //    Token: ["foo&bar"]
    //    Token: [|]
    //    Token: [|]
    //    Token: [echo]
    //    Token: ["baz]
    //    Token: [|]
    //    Token: [qux"]
    Error: Unmatched " quote in token: "baz

    echo "" '' " " ' '
    Token: [echo]
    Token: []
    Token: []
    Token: [ ]
    Token: [ ]

    echo \"hello\"

    echo hello\\

    minishell> echo hello\\
    Token: [echo]
    Token: [hello\]


    minishell> echo \"hello\"
    Token: [echo]
    Token: ["hello"]

    echo "hi" ">" "file.txt"
    minishell> echo "hi" ">" "file.txt"
    Token: [echo]
    Token: [hi]
    Token: [>]
    Token: [file.txt]

    echo "'\"nested\" quotes'"

    minishell> echo "'\"nested\" quotes'"
    Token: [echo]
    Token: ['"nested" quotes']

    echo "it's a "bad" day"

    minishell> echo "it's a "bad" day"
    Token: [echo]
    Token: [it's a bad day]
    Error: Unmatched ' quote in token: it's a bad day

    echo "She said, \"hello\""
    minishell> echo "She said, \"hello\""
    Token: [echo]
    Token: [She said, "hello"]

    echo hello\\world


    echo "he said: 'it'\''s fine'"


    minishell> echo "he said: 'it'\''s fine'"
    Token: [echo]
    Token: [he said: 'it'\''s fine']
    Error: Unmatched ' quote in token: he said: 'it'\''s fine'

    echo "'She said, \"hello\"'"

    #   minishell> echo "'She said, \"hello\"'"
    #   Token: [echo]
    #   Token: ['She said, "hello"']

    // !!!!!!!!! ???
    echo '"'

    minishell> echo '"'
    Token: [echo]
    Token: ["]
    // Error: Unmatched " quote in token: "

    #     minishell> echo test > "my file.txt"
    #     Token: [echo]
    #     Token: [test]
    #     Token: [>]
    #    Token: [my file.txt]


    echo "hello; world" | grep "hello" && echo "found" || echo "not found"

        # minishell> echo "hello; world" | grep "hello" && echo "found" || echo "not found"
        # Token: [echo]
        # Token: [hello; world]
        # Token: [|]
        # Token: [grep]
        # Token: [hello]
        # Token: [&&]
        # Token: [echo]
        # Token: [found]
        # Token: [||]
        # Token: [echo]
        # Token: [not found]

    echo "a"'b'

        minishell> echo "a"'b'
        Token: [echo]
        Token: [ab]

    echo "hello 'nested "quotes"'"

        minishell> echo "hello 'nested "quotes"'"
        Token: [echo]
        Token: [hello 'nested quotes']

        >
        <
        >>
        <<
        ls >
        cat <
        ls >> | grep foo // !!!
        echo a > > file
        cat <<<< EOF
        ls < > file

        < | > |
        ls | < | echo
        echo hello > | > file
        | | |
        echo hello > file <
        echo hello > file < | echo

        ls > file |
        ls | > file
        ls > > file | grep a
        ls | ; > file

        echo $
        echo $USER$HOME$SHELL
        echo "Path: $PATH is set"
        echo "Your home directory is $HOME"
        echo $SHELL_PATH
        echo \$USER
        echo Hello $USER, welcome to $HOME!
        echo $UNDEFINED_VAR
        echo $USER is logged into $HOME
        echo $USER
        echo $USER$HOME

        # minishell> echo "a"'b'
        # Token: [echo]
        # Token: [ab]

    echo "hello 'nested "quotes"'"

        # minishell> echo "hello 'nested "quotes"'"
        # Token: [echo]
        # Token: [hello 'nested quotes']

	# Segmentation fault (core dumped) in this case ?? ehco hello nested quotes

*/