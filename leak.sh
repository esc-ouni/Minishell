while [ 1 ]; do
    output=$(leaks minishell | grep " leaks " | awk '{print $4" "$3}' | grep "leaks")
    echo -ne "\t\033[0;32m${output}\033[0m\r"
done
