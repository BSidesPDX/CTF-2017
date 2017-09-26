#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

struct list_node
{
    uint32_t shellcode;
    struct list_node *next;
};

void append_list_node(struct list_node *list, struct list_node *node)
{
    struct list_node *current_node = list;

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

    current_node->next = node;
}

void main()
{
    fprintf(stdout,"Well, hello there. Do you understand linked lists?\n");
    char shellcode_buffer[1024];
    struct list_node *shellcode_list = NULL, *current_node;
    uint32_t current_chunk, retval;
    size_t bytes_read;

    while ((bytes_read = read(0, &current_chunk, 4)) > 0)
    {
        current_node = malloc(sizeof(*current_node));
        if (!current_node)
        {
            perror("Couldn't allocate shellcode node");
            exit(1);
        }

        current_node->shellcode = current_chunk;
        current_node->next = NULL;

        if (shellcode_list)
        {
            append_list_node(shellcode_list, current_node);
        }
        else
        {
            shellcode_list = current_node;
        }
    }

        __asm__ ("movl %1, %%eax\n\t"
                "call *%%eax\n\t"
                "movl %%eax, %0"
               : "=r" (retval)
               : "r" (&shellcode_list->shellcode)
               : "0");
}
