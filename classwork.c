#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int val;
    char string[100];
    struct Node *next;
    struct Node *prev;
} NNode;

void create(NNode **head);
void push_back(NNode *head);
void push_front(NNode **head);
void add_random(NNode **head);
void pop_back(NNode *head);
void pop_front(NNode **head);
void pop_random(NNode **head);
void print(NNode *head);
NNode *concat(NNode *first_list_head, NNode *second_list_head);
int lenght();
void save_file_bin(NNode *head);
void read_file_bin(NNode *head);
NNode *copy_list(NNode *head);

int main()
{
    NNode *first_list;
    NNode *new_list;
    NNode *concat_list;

    create(&first_list);
    create(&new_list);

    push_back(first_list);
    push_back(new_list);

    push_front(&first_list);
    push_front(&new_list);

    add_random(&first_list);
    add_random(&new_list);

    print(first_list);
    print(new_list);

    pop_back(first_list);
    pop_back(new_list);

    pop_front(&first_list);
    pop_front(&new_list);

    print(first_list);
    print(new_list);

    concat_list = concat(first_list, new_list);
    printf("Print Concat");
    print(concat_list);

    save_file_bin(concat_list);
    read_file_bin(concat_list);

    return 0;
}

void create(NNode **head)
{
    printf("** Create **\n\n");

    char *string = (char *)malloc(sizeof(char) * 100);
    *head = (NNode *)malloc(sizeof(NNode));

    (*head)->prev = NULL;
    (*head)->next = NULL;

    printf("Enter int: ");
    scanf("%d", &(*head)->val);
    getchar();

    printf("Enter string: ");
    fgets((*head)->string, 100, stdin);
    if ((*head)->string[strlen((*head)->string) - 1] == '\n')
    {
        (*head)->string[strlen((*head)->string) - 1] = '\0';
    }
}

void push_back(NNode *head)
{
    printf("** Insert Back **\n\n");
    int val;
    char *string = (char *)malloc(sizeof(char) * 100);
    NNode *newnode = (NNode *)malloc(sizeof(NNode));
    NNode *current = head;
    newnode->prev = NULL;

    printf("Enter int: ");
    scanf("%d", &val);
    getchar();
    printf("Enter string: ");
    fgets(string, 100, stdin);
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';

    newnode->val = val;
    strcpy(newnode->string, string);

    while (current->prev != NULL)
        current = current->prev;

    newnode->next = current;
    current->prev = newnode;

    free(string);
}

void push_front(NNode **head)
{
    printf("** Insert Front **\n\n");

    int val;
    char *string = (char *)malloc(sizeof(char) * 100);
    NNode *newnode = (NNode *)malloc(sizeof(NNode));
    newnode->next = NULL;
    newnode->prev = *head;

    printf("Enter int: ");
    scanf("%d", &val);
    getchar();
    printf("Enter string: ");
    fgets(string, 100, stdin);
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';

    newnode->val = val;
    strcpy(newnode->string, string);
    (*head)->next = newnode;
    (*head) = (*head)->next;

    free(string);
}

int lenght(NNode * head)
{
    NNode * current = head;
    int num = 1;

    while(current->prev != NULL)
    {
        num++;
        current = current->prev;
    }

    return num;
}

void print(NNode *head)
{
    printf("** Print **\n\n");
    NNode *current = head;
    int j = 1;

    while (current != NULL)
    {
        printf("Element %d - int: %d\n", j, current->val);
        printf("Element %d - string: %s\n\n\n", j, current->string);
        j++;
        current = current->prev;
    }
}

void add_random(NNode **head)
{
    printf("** Insert Random **\n\n");


    NNode *newnode = (NNode *)malloc(sizeof(NNode));
    NNode *current = *head;
    int pos;
    printf("In what position to insert the new element(The number must be 1 or higher): ");
    scanf("%d", &pos);
    getchar();

    printf("Enter int: ");
    scanf("%d", &newnode->val);
    getchar();

    printf("Enter string: ");
    fgets(newnode->string, 100, stdin);
    if (newnode->string[strlen(newnode->string) - 1] == '\n')
        newnode->string[strlen(newnode->string) - 1] = '\0';

    if (pos == 1)
    {
        newnode->next = NULL;
        newnode->prev = *head;
        *head = newnode;
        return;
    }

    for (int i = 0; i < pos - 2; ++i)
    {
        current = current->prev;
        if (current == NULL)
        {
            printf("\nError!\n");
            return;
        }
    }

    if (current->prev != NULL)
    {   
        NNode * swap = current->prev;
        current->prev = newnode;
        newnode->prev = swap;
        newnode->next = current;
    }
    else if (current->prev == NULL)
    {
        newnode->next = current;
        newnode->prev = NULL;
        current->prev = newnode;
    }
}

void pop_back(NNode *head)
{
    printf("** Pop Back **\n\n");

    NNode *current = head;

    while (current->prev != NULL)
        current = current->prev;

    current->next->prev = NULL;
    free(current);
}

void pop_front(NNode **head)
{
    printf("** Pop Front **\n\n");

    NNode *current = *head;
    *head = (*head)->prev;
    (*head)->next = NULL;

    free(current);
}

void pop_random(NNode **head)
{
    printf("** Pop Random **\n\n");

    NNode *current = *head;
    NNode *pop_item;
    int pos;
    printf("What element to pop: ");
    scanf("%d", &pos);

    if (pos == 1)
    {
        pop_front(head);
        return;
    }

    for (int i = 0; i < pos - 2; ++i)
    {
        current = current->prev;
        if (current == NULL)
        {
            printf("Can't pop this item");
            return;
        }
    }
    pop_item = current->prev;
    current->prev = current->prev->prev;

    free(pop_item);
}

NNode *copy_list(NNode *head)
{
    NNode *current = head;
    NNode *copy = NULL;
    NNode *tail, *tail_cpy;

    while(current != NULL)
    {
        if(copy == NULL)
        {
            copy = (NNode *)malloc(sizeof(NNode));
            copy->val = current->val;
            strcpy(copy->string, current->string);
            copy->next = NULL;
            copy->prev = NULL;
            tail = copy;
        }
        else
        {

            tail->prev = (struct Node*)malloc(sizeof(NNode));
            tail_cpy = tail;
            tail = tail->prev;
            tail->val = current->val;
            strcpy(tail->string, current->string);
            tail->next = tail_cpy;
            tail->prev = NULL;
        }
        current = current->prev;
    }

    return copy;
}

NNode *concat(NNode *first_list_head, NNode *second_list_head)
{
   
    NNode *second_list_head_copy = copy_list(second_list_head); 
    NNode *first_list_head_copy = copy_list(first_list_head);
    NNode *current = second_list_head_copy;

    while (current->prev != NULL)
    {
        current = current->prev;
    }

    current->prev = first_list_head_copy;
    first_list_head_copy->next = current;
    
    return second_list_head_copy;
}

void save_file_bin(NNode *head)
{
    NNode *current = head;

    FILE *fp;
    fp = fopen("binary.bin", "wb");

    while (current != NULL)
    {
        fwrite(&current->val, sizeof(current->val), 1, fp);
        fwrite(current->string, strlen(current->string) + 1, 1, fp);
        current = current->prev;
    }

    fclose(fp);
}

void read_file_bin(NNode *head)
{
    NNode *current = head;

    FILE *fp;
    fp = fopen("binary.bin", "rb");

    while (current != NULL)
    {
        fread(&current->val, sizeof(current->val), 1, fp);
        fread(current->string, strlen(current->string) + 1, 1, fp);
        printf("%d\n", current->val);
        printf("%s\n", current->string);
        current = current->prev;
    }

    fclose(fp);
}