#include "wildcard.h"

void handle_wildcard(t_node *node)
{
    if (node->connection_count == 1)
        handle_node_wildcard(node);
    else if (node->connection_count > 1)
    {
        int i = 0;
        while(i < node->connection_count)
        {
            handle_wildcard(node->connections[i]);
            i++;
        }
    }
}

void wildcard(t_node *node)
{
    handle_wildcard(node);
    //print_tree(node);
}