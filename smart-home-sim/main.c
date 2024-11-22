#include <stdio.h>
#include <string.h>

#define MAX_DEVICES 3

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
void updateDeviceState(Device devices[]);
void viewDevices(Device devices[]);
void searchDevice(Device devices[]);
void addDevice(Device devices[], int *count);

int main()
{
    Device devices[MAX_DEVICES];
    initializeDevices(devices); // Initialize the devices
    int count = 3;              // Start with 3 initialized devices
    int choice;

    while (1)
    {
        printf("\n1. Update device\n2. View devices\n3. Add Device\n4. Search Device\n5. Exit\n");
        scanf("%d", &choice); // Save scanf result in choice
        switch (choice)
        {
        case 1:
            updateDeviceState(devices);
            break;
        case 2:
            viewDevices(devices);
            break;
        case 3:
            addDevice(devices, &count);
            break;
        case 4:
            searchDevice(devices);
            break;
        case 5:
            printf("Exiting...\n");
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

void updateDeviceState(Device devices[])
{

    printf("\n--- Update Device States ---\n");
    // Loop through all devices and show current states
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        printf("%d. %s (Current State: %s)\n", i + 1, devices[i].name, devices[i].state == 0 ? "Off" : "On");
    }
    int choice;
    printf("Enter the device number you want to update (1-%d): ", MAX_DEVICES);
    scanf("%d", &choice);

    // check for valid input
    if (choice < 1 || choice > MAX_DEVICES)
    {
        printf("Invalid choice.\n");
        return;
    }
    // Toggle the device state
    int deviceIndex = choice - 1; // Array is 0-based
    devices[deviceIndex].state = !devices[deviceIndex].state;

    printf("Device '%s' is now %s.\n", devices[deviceIndex].name, devices[deviceIndex].state == 0 ? "Off" : "On");
}

void viewDevices(Device devices[])
{
    printf("\n--- Devices ---\n");

    for (int i = 0; i < MAX_DEVICES; i++)
    {
        printf("Name: %s.\n", devices[i].name);
        printf("  Type: %s\n", devices[i].type == LIGHT ? "Light" : devices[i].type == THERMOSTAT ? "Thermostat"
                                                                                                  : "Security System");
        printf("State: %s .\n", devices[i].state == 0 ? "Off" : "On");
    }
}

void searchDevice(Device devices[])
{
    // ask for user input
    int choice;
    printf("Choose the devices (1-3): \n");
    for (int i = 0; i < MAX_DEVICES; i++)
    {
        printf("%d. %s \n", i + 1, devices[i].name);
    }
    scanf("%d", &choice);
    int found = 0;
    int i = 0;

    while (i < MAX_DEVICES && found == 0)
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

void addDevice(Device devices[], int *count)
{
    printf("\n---Add new Device ---\n");
    // Check if there's space for a new device
    if (*count >= MAX_DEVICES)
    {
        printf("Device limit reached. Cannot add more devices.\n");
        return;
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

    // add new device to the devices array
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
    devices[*count] = newDevice;
    (*count)++;

    printf("Device '%s' added successfully!\n", newDevice.name);
}