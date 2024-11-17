#include <stdio.h>
#include <stdlib.h>

// dynamic array manager
// Define the Purpose :

//     Create a dynamic array that can grow or
//     shrink as elements are added or removed.Dynamically allocate memory and resize it using malloc and realloc

// Declare Function prototypes
void addElement(int **array, int *size, int *capacity, int value);
void displayArray(int *array, int size);

int main()
{
    int *array = NULL; // Pointer to dynamically allocated array
    int size = 0;      // Number of elements currently in the array
    int capacity = 0;  // Current allocated capacity

    int choice, value;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Add Element\n");
        printf("2. Display Array\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to add: ");
            scanf("%d", &value);
            addElement(&array, &size, &capacity, value);
            break;
        case 2:
            displayArray(array, size);
            break;
        case 3:
            free(array); // Free allocated memory before exiting
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

// Function to add an element to the dynamic array
void addElement(int **array, int *size, int *capacity, int value)
{
    if (*size == *capacity)
    {
        // Resize the array if it's full
        // use dereferencing of the pointer to modify its value
        *capacity = (*capacity == 0) ? 1 : (*capacity * 2);
        *array = realloc(*array, *capacity * sizeof(int));
        if (*array == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    (*array)[*size] = value; // Add the new value
    (*size)++;               // Increment the size
    printf("Added %d to the array.\n", value);
}

// Function to display the array
void displayArray(int *array, int size)
{
    if (size == 0)
    {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
