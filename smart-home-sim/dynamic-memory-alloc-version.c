#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For malloc, realloc, free

// Define an enum for device types
typedef enum
{
    LIGHT,
    THERMOSTAT,
    SECURITY
} DeviceType;

typedef struct
{
    char name[30];
    DeviceType type;
    int state; // 0 = off, 1 = on, or a number for temperature
} Device;

void initializeDevices(Device devices[]);
void updateDeviceState(Device *devices, int count);
void viewDevices(Device *devices, int count);
void searchDevice(Device *devices, int count);
void addDevice(Device **devices, int *count, int *maxDevices);
void saveToJSON(Device *devices, int count);

int main()
{
    int maxDevices = 3;
    int count = 3; // Current number of devices

    Device *devices = malloc(maxDevices * sizeof(Device)); // Dynamically allocate memory
    if (devices == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    initializeDevices(devices); // Initialize the devices

    int choice;
    while (1)
    {
        printf("\n1. Update device\n2. View devices\n3. Add Device\n4. Search Device\n5. Exit\n");
        scanf("%d", &choice); // Save scanf result in choice
        switch (choice)
        {
        case 1:
            updateDeviceState(devices, count);
            break;
        case 2:
            viewDevices(devices, count);
            break;
        case 3:
            addDevice(&devices, &count, &maxDevices);
            break;
        case 4:
            searchDevice(devices, count);
            break;
        case 5:
            saveToJSON(devices, count);
            break;
        case 6:
            printf("Exiting...\n");
            free(devices); // Free allocated memory

            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void initializeDevices(Device devices[])
{
    // Initialize the first device: Light
    strcpy(devices[0].name, "Living Room Light"); // Set name
    devices[0].type = LIGHT;                      // Set type
    devices[0].state = 0;                         // Set initial state (off)

    // Initialize the second device: Thermostat
    strcpy(devices[1].name, "Thermostat"); // Set name
    devices[1].type = THERMOSTAT;          // Set type
    devices[1].state = 22;                 // Set initial state (22°C)

    // Initialize the third device: Security System
    strcpy(devices[2].name, "Security System"); // Set name
    devices[2].type = SECURITY;                 // Set type
    devices[2].state = 0;                       // Set initial state (disarmed)
};

void updateDeviceState(Device *devices, int count)
{

    printf("\n--- Update Device States ---\n");
    // Loop through all devices and show current states
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s (Current State: %s)\n", i + 1, devices[i].name, devices[i].state == 0 ? "Off" : "On");
    }
    int choice;
    printf("Enter the device number you want to update (1-%d): ", count);
    scanf("%d", &choice);

    // check for valid input
    if (choice < 1 || choice > count)
    {
        printf("Invalid choice.\n");
        return;
    }
    // Toggle the device state
    int deviceIndex = choice - 1; // Array is 0-based
    devices[deviceIndex].state = !devices[deviceIndex].state;

    printf("Device '%s' is now %s.\n", devices[deviceIndex].name, devices[deviceIndex].state == 0 ? "Off" : "On");
}

void viewDevices(Device *devices, int count)
{
    printf("\n--- Devices ---\n");

    for (int i = 0; i < count; i++)
    {
        printf("Name: %s.\n", devices[i].name);
        printf("  Type: %s\n", devices[i].type == LIGHT ? "Light" : devices[i].type == THERMOSTAT ? "Thermostat"
                                                                                                  : "Security System");
        printf("State: %s .\n", devices[i].state == 0 ? "Off" : "On");
    }
}

void searchDevice(Device *devices, int count)
{
    // ask for user input
    int choice;
    printf("Choose the devices (1-3): \n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s \n", i + 1, devices[i].name);
    }
    scanf("%d", &choice);
    int found = 0;
    int i = 0;

    while (i < count && found == 0)
    {
        // search for the index in the array that matches 'choice'
        if (choice == i + 1)
        {
            printf("\nDevice Found:\n");
            printf("  Name: %s\n", devices[i].name);
            printf("  Type: %s\n", devices[i].type == LIGHT ? "Light" : devices[i].type == THERMOSTAT ? "Thermostat"
                                                                                                      : "Security System");
            printf("  State: %s\n", devices[i].state == 0 ? "Off" : devices[i].type == THERMOSTAT ? "Temperature"
                                                                                                  : "On");
            found = 1;
            break; // Exit the loop once the device is found
        }
        i++;

        if (!found)
        {
            printf("No device found.\n");
        }
    }
}

void addDevice(Device **devices, int *count, int *maxDevices)
{
    printf("\n---Add new Device ---\n");

    // Check if we need to expand the array
    if (*count >= *maxDevices)
    {
        *maxDevices *= 2; // Double the capacity
        *devices = realloc(*devices, (*maxDevices) * sizeof(Device));
        if (devices == NULL)
        {
            printf("Memory reallocation failed.\n");
            exit(1); // Exit the program on failure
        }
        printf("Device limit increased to %d.\n", *maxDevices);
    }

    // initialize the new Device
    Device newDevice;
    printf("Enter device name: ");
    scanf(" %[^\n]", newDevice.name); // Read string with spaces
    printf("Enter device type (0: Light, 1: Thermostat, 2: Security): ");
    int typeChoice;
    scanf("%d", &typeChoice);
    // validate the type choice
    if (typeChoice > 2 || typeChoice < 0)
    {
        printf("Invalid device type.\n");
        return;
    }

    newDevice.type = (DeviceType)typeChoice;

    // Set initial state based on device type
    if (newDevice.type == THERMOSTAT)
    {
        printf("Enter initial temperature (°C): ");
        scanf("%d", &newDevice.state);
    }
    else
    {
        printf("Enter initial state (0: Off, 1: On): ");
        scanf("%d", &newDevice.state);
        if (newDevice.state != 0 && newDevice.state != 1)
        {
            printf("Invalid state. Setting default state to Off.\n");
            newDevice.state = 0;
        }
    }

    // Add to the array and increment the count
    (*devices)[*count] = newDevice;
    (*count)++;

    printf("Device '%s' added successfully!\n", newDevice.name);
}

void saveToJSON(Device *devices, int count)
{
    // read every single Device from devices
    if (count == 0)
    {
        printf("No devices to add to a file.\n");
        return;
    }

    // Opens a file named contacts.json in write mode
    FILE *fptr = fopen("devices.json", "w");
    if (!fptr)
    {
        perror("Failed to open file.");
        return;
    }
    fprintf(fptr, "[\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(fptr, "  {\n");
        fprintf(fptr, "    \"name\": \"%s\",\n", devices[i].name);
        fprintf(fptr, "    \"type\": \"%s\"\n", devices[i].type == LIGHT ? "Light" : devices[i].type == THERMOSTAT ? "Thermostat"
                                                                                                                   : "Security System");
        fprintf(fptr, "  }%s\n", (i < count - 1) ? "," : "");
    }
    fprintf(fptr, "]\n");

    fclose(fptr);
    printf("Contacts exported to 'devices.json' successfully!\n");

    return;
}