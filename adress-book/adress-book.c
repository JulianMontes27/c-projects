#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Contact structure
typedef struct
{
    char name[50];  // Max length for a name is 49 characters + null terminator
    char phone[15]; // Max length for a phone number is 14 characters + null terminator
} Contact;

// Function prototypes
void addContact(Contact **contacts, int *count, int *capacity);
void viewContacts(Contact *contacts, int count);
void searchContact(Contact *contacts, int count);
void deleteContact(Contact **contacts, int *count, int *capacity);
void sortContacts(Contact *contacts, int count);
void updateContact(Contact **contact, int *count);
void exportToJSON(Contact *contacts, int count);

int main()
{
    int capacity = 0;         // Current allocated size of the array
    int count = 0;            // Number of contacts in the array
    Contact *contacts = NULL; // Pointer to the array of contacts
    int choice;

    while (1)
    {
        printf("\n1. Add Contact\n2. View Contacts\n3. Search Contact\n4. Delete Contact\n5. Sort Contacts\n6. Update Contact\n7. Export to JSON\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addContact(&contacts, &count, &capacity);
            break;
        case 2:
            viewContacts(contacts, count);
            break;
        case 3:
            searchContact(contacts, count);
            break;
        case 4:
            deleteContact(&contacts, &count, &capacity);
            break;
        case 5:
            sortContacts(contacts, count);
            break;
        case 6:
            updateContact(&contacts, &count);
            break;
        case 7:
            exportToJSON(contacts, count);
            break;
        case 8:
            free(contacts); // Free allocated memory before exiting
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Add a new contact
void addContact(Contact **contacts, int *count, int *capacity)
{
    if (*count == *capacity)
    {
        *capacity = (*capacity == 0) ? 1 : (*capacity * 2);
        // Contact *temp = realloc(*contacts, (*capacity) * sizeof(Contact));
        // if (temp == NULL)
        // {
        //     perror("Failed to allocate memory");
        //     free(*contacts);
        //     exit(1);
        // }
        // *contacts = temp;

        // reallocate memory in the array to add a new element
        *contacts = realloc(*contacts, (*capacity) * (sizeof(Contact)));
        if (*contacts == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    // add the new values
    printf("Enter Name: ");
    scanf(" %[^\n]", (*contacts)[*count].name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", (*contacts)[*count].phone);
    (*count)++;
    printf("Contact added successfully!\n");
}

// View all contacts
void viewContacts(Contact contacts[], int count)
{
    if (count == 0)
    {
        printf("No contacts to display.\n");
        return;
    }
    printf("\n=== Contact List ===\n");
    for (int i = 0; i < count; i++)
    {
        printf("Name: %s, Phone: %s\n", contacts[i].name, contacts[i].phone);
    }
}

// Search for a contact by name
void searchContact(Contact *contacts, int count)
{
    if (count == 0)
    {
        printf("No contacts available to search.\n");
        return;
    }
    char searchName[50];
    printf("Enter the name of the contact: ");
    scanf(" %[^\n]", searchName);

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(contacts[i].name, searchName) == 0)
        {
            printf("Contact Found: Name: %s, Phone: %s\n", contacts[i].name, contacts[i].phone);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("No contact found with the name '%s'.\n", searchName);
    }
}

// Delete a contact by name
void deleteContact(Contact **contacts, int *count, int *capacity)
{
    if (*count == 0)
    {
        printf("No contacts to delete.\n");
        return;
    }

    char deleteName[50];
    printf("Enter the name of the contact to delete: ");
    scanf(" %[^\n]", deleteName);

    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp((*contacts)[i].name, deleteName) == 0) // compare both strings
        {
            found = 1;

            // Shift remaining contacts to fill the gap
            // To delete the contact, we need to "shift" all subsequent contacts one position up in the array. Starting at the position i of the contact to delete, each subsequent contact is copied to the previous position.This overwrites the contact to be deleted.

            for (int j = i; j < *count - 1; j++)
            {
                (*contacts)[j] = (*contacts)[j + 1];
            }
            (*count)--;

            // Shrink the memory if needed
            if (*count > 0 && *count <= *capacity / 4)
            {
                *capacity /= 2;
                Contact *temp = realloc(*contacts, (*capacity) * sizeof(Contact));
                if (temp == NULL)
                {
                    perror("Failed to shrink memory");
                    free(*contacts);
                    exit(1);
                }
                *contacts = temp;
            }

            printf("Contact '%s' deleted successfully!\n", deleteName);
            break;
        }
    }
    if (!found)
    {
        printf("No contact found with the name '%s'.\n", deleteName);
    }
}

// sort contacts alphabetically
void sortContacts(Contact *contacts, int count)
{
    if (count < 2)
    {
        printf("Not enough contacts to sort.\n");
        return;
    }
    // bubble sort
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(contacts[i].name, contacts[j + 1].name) > 0)
            {
                // Swap contacts[j] and contacts[j+1]
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    printf("Contacts sorted alphabetically by name!\n");
}

void updateContact(Contact **contacts, int *count)
{
    if (*count == 0)
    {
        printf("No contacts to update.\n");
        return;
    }

    // Ask the user to type in a contact name
    char updateName[50];
    printf("Enter the contact's name to update: \n");
    scanf(" %[^\n]", updateName);

    // Loop to find the contact
    for (int i = 0; i < *count; i++)
    {
        if (strcmp((*contacts)[i].name, updateName) == 0)
        {
            // Update the name
            char newName[50];
            printf("Enter the new name for the contact: \n");
            scanf(" %[^\n]", newName);
            strcpy((*contacts)[i].name, newName); // Use strcpy for string assignment

            printf("Contact updated to: %s\n", (*contacts)[i].name);
            return; // Exit after updating
        }
    }

    // If contact is not found
    printf("Contact with the name '%s' not found.\n", updateName);
}

void exportToJSON(Contact *contacts, int count)
{
    if (count == 0)
    {
        printf("No contacts to export.\n");
        return;
    }
    // Opens a file named contacts.json in write mode
    FILE *file = fopen("contacts.json", "w");
    if (!file)
    {
        perror("Failed to open file.");
        return;
    }
    fprintf(file, "[\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "  {\n");
        fprintf(file, "    \"name\": \"%s\",\n", contacts[i].name);
        fprintf(file, "    \"phone\": \"%s\"\n", contacts[i].phone);
        fprintf(file, "  }%s\n", (i < count - 1) ? "," : "");
    }
    fprintf(file, "]\n");

    fclose(file);
    printf("Contacts exported to 'contacts.json' successfully!\n");
}