#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *next;
};

typedef struct Node Node;

void insert(Node **head_ref, int new_data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void display(Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    Node *head = NULL;
    int income;
    int i;

    printf("Enter your monthly income: ");
    scanf("%d", &income);

    printf("Enter your monthly expenses:\n");
    for (i = 0; i < 12; i++)
    {
        int expense;
        printf("Month %d: ", i + 1);
        scanf("%d", &expense);
        insert(&head, expense);
    }

    // Calculate total expenses and savings
    Node *temp = head;
    int total_expenses = 0;
    while (temp != NULL)
    {
        total_expenses += temp->data;
        temp = temp->next;
    }
    int savings = income * 12 - total_expenses;

    // Display results
    printf("\n");
    printf("Total income: %d\n", income);
    printf("Total expenses: ");
    display(head);
    printf("\n");
    printf("Total savings: %d\n", savings * -1);
    // Save data to file
    char filename[100];
    printf("Enter a name for the finance file: ");
    scanf("%s", filename);
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    fprintf(fp, "Income: %d\n", income);
    fprintf(fp, "Expenses: ");
    temp = head;
    while (temp != NULL)
    {
        fprintf(fp, "%d ", temp->data);
        temp = temp->next;
    }
    fprintf(fp, "\n");
    fprintf(fp, "Savings: %d\n", savings);
    fclose(fp);

    // Read data from file and allow user to edit it
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    printf("The content of the %s file is:\n\n", filename);

    char line[100];
    while (fgets(line, 100, fp))
    {
        printf("%s", line);
    }
    printf("\n");

    printf("Enter the line number you want to edit: ");
    int line_num;
    scanf("%d", &line_num);

    // Move file pointer to the beginning of the line to be edited
    fseek(fp, 0, SEEK_SET);
    for (i = 1; i < line_num; i++)
    {
        fgets(line, 100, fp);
    }
    printf("The current content of the line is: %s", line);

    // Edit the line
    printf("Enter the new content: ");
    char new_content[100];
    scanf("%s", new_content);
    fseek(fp, -(strlen(line)), SEEK_CUR);
    fprintf(fp, "%s", new_content);

    // Display the updated content of the file
    fseek(fp, 0, SEEK_SET);
    printf("\nThe updated content of the file is:\n\n");
    while (fgets(line, 100, fp))
    {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}
