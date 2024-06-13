/**
 * @file main.cpp
 * @brief Main program that provides a menu to interact with the Container Manager.
 *
 * This program provides a menu to interact with the Container Manager. The user can add a new Container, remove a Container, list all Containers, execute a command in a Container, define limits of system resources, check limits of system resources, establish a network connection with a Container, execute an application in a Container, copy a file to a Container, and exit the program.
 *
 * The program uses the functions from the Container Manager library to interact with the Containers.
 *
 * @author Simão Andrade
 * @date 2024-06-13
 */

#include "lib/lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EXIT_OPTION 10
#define CONTAINER_NAME_SIZE 100

// 4.
#define COMMAND_BUFFER_SIZE 1024

// 5.
#define CGROUP_LIMITS_BUFFER_SIZE 10

// 8.
#define FILENAME_BUFFER_SIZE 100

void clear_screen(void)
{
    printf("\033[H\033[J");
}

void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int show_options_menu(void)
{
    int option = 0;

    clear_screen();
    printf("   ______            __        _                    __  ___                                                  __     ______            __\n");
    printf("  / ____/___  ____  / /_____ _(_)___  ___  _____   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_   /_  __/___  ____  / /\n");
    printf(" / /   / __ \\/ __ \\/ __/ __ `/ / __ \\/ _ \\/ ___/  / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ __ `__ \\/ _ \\/ __ \\/ __/    / / / __ \\/ __ \\/ / \n");
    printf("/ /___/ /_/ / / / / /_/ /_/ / / / / /  __/ /     / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_     / / / /_/ / /_/ / /  \n");
    printf("\\____/\\____/_/ /_/\\__/\\__,_/_/_/ /_/\\___/_/     /_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/ /_/ /_/\\___/_/ /_/\\__/    /_/  \\____/\\____/_/   \n");
    printf("                                                                         /____/                                                         \n");
    printf("1. Add a new Container\n");
    printf("2. Remove a Container\n");
    printf("3. List all Containers\n");
    printf("4. Execute a command in a Container\n");
    printf("5. Define limits of system resources\n");
    printf("6. Check limits of system resources\n");
    printf("7. Establish connection with a Container\n");
    printf("8. Copy a file to a Container\n");
    printf("10. Exit\n\n");
    printf("Choose an option: ");

    if (scanf("%d", &option) != 1)
    {
        printf("Error: Invalid input. Please ENTER a number.\n");
        while (getchar() != '\n') // Clear the input buffer
            ;
        return -1; // Error
    }

    return option;
}

int read_input(char *buffer, int buffer_size)
{
    if (fgets(buffer, buffer_size, stdin) == NULL)
    {
        printf("Error: Failed to read the input.\n");
        return -1;
    }

    buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character

    return 0;
}

int main(void)
{

    int option = 0;
    char container_name[CONTAINER_NAME_SIZE] = {0};
    do
    {
        option = show_options_menu();
        getchar(); // Clear the newline character from the input buffer

        switch (option)
        {

        case 1: // Add a new Container
        {
            clear_screen();

            printf("Adding a new Container...\n");

            // Ask for a container name
            printf("Enter the name of the new Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            // Create the new Container
            if (create_new_container(container_name) == 0)
            {
                printf("Container %s created successfully.\n", container_name);
            }
            else
            {
                printf("Error: Failed to create Container %s.\n", container_name);
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case 2: // Remove a Container
        {
            clear_screen();

            printf("Removing a Container...\n");

            // Ask for a container name
            printf("Enter the name of the Container to remove: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            // Remove the Container
            if (remove_container(container_name) == 0)
            {
                printf("Container %s removed successfully.\n", container_name);
            }
            else
            {
                printf("Error: Failed to remove Container %s.\n", container_name);
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case 3: // List all Containers
        {
            clear_screen();

            printf("Listing all Containers...\n");

            // List all Containers
            if (list_containers() == 0)
            {
                printf("Containers listed successfully.\n");
            }
            else
            {
                printf("Error: Failed to list Containers.\n");
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;
            break;
        }

        case 4: // Execute a command in a Container
        {
            clear_screen();

            printf("Executing a command in a Container...\n");

            char command[COMMAND_BUFFER_SIZE] = {0};
            int command_length = 0;

            printf("Enter the name of the Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            printf("Enter the command to execute: ");
            if (fgets(command, COMMAND_BUFFER_SIZE, stdin) == NULL)
            {
                printf("Error: Failed to read the command.\n");
                break;
            }

            command[strcspn(command, "\n")] = 0; // Remove the newline character

            command_length = strlen(command);
            if (command_length == 0)
            {
                printf("Error: Command is empty.\n");
                break;
            }

            if (run_command_in_container(container_name, command) == 0) // execute the command
            {
                printf("Command \"%s\" executed successfully in Container %s.\n", command, container_name);
            }
            else
            {
                printf("Error: Failed to execute command \"%s\" in Container %s.\n", command, container_name);
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case 5: // Define limits of system resources (cgroups)
        {
            clear_screen();

            printf("Defining limits of system resources...\n");

            printf("Enter the name of the Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            char cgroup_limit[CGROUP_LIMITS_BUFFER_SIZE] = {0};
            int cgroup_option = 0;
            char avaliable_cgroups[4][25] = {"cpu.cfs_quota_us", "memory.limit_in_bytes", "blkio.weight", "net_cls.classid"};

            printf("Enter the resource to limit:\n 1. Number of CPU shares\n 2. Memory limit\n 3. Block I/O weight\n 4. Network class ID\n");
            printf("Choose an option: ");
            if (scanf("%d", &cgroup_option) != 1)
            {
                printf("Error: Invalid input. Please ENTER a number.\n");
                while (getchar() != '\n') // Clear the input buffer
                    ;
                break;
            }

            clear_input_buffer();

            if (cgroup_option < 1 || cgroup_option > 4)
            {
                printf("Error: Invalid option. Please ENTER a number between 1 and 4.\n");
                break;
            }

            char *chosen_cgroup = avaliable_cgroups[cgroup_option - 1];

            printf("Enter the value for the resource limit: ");
            if (read_input(cgroup_limit, CGROUP_LIMITS_BUFFER_SIZE) < 0)
                break;

            if (define_limits_of_system_resources(container_name, chosen_cgroup, cgroup_limit) == 0)
            {
                printf("System resources limits defined successfully.\n");
            }
            else
            {
                printf("Error: Failed to define system resources limits.\n");
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case 6: // Check limits of system resources (cgroups)
        {
            clear_screen();
            printf("Checking limits of system resources...\n");

            printf("Enter the name of the Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            int cgroup_option = 0;
            char available_cgroups[4][25] = {"cpu.cfs_quota_us", "memory.limit_in_bytes", "blkio.weight", "net_cls.classid"};

            printf("Enter the resource to check:\n 1. Number of CPU shares\n 2. Memory limit\n 3. Block I/O weight\n 4. Network class ID\n");
            printf("Choose an option: ");
            if (scanf("%d", &cgroup_option) != 1)
            {
                printf("Error: Invalid input. Please ENTER a number.\n");
                while (getchar() != '\n')
                    ; // Clear the input buffer
                break;
            }

            clear_input_buffer();

            if (cgroup_option < 1 || cgroup_option > 4)
            {
                printf("Error: Invalid option. Please ENTER a number between 1 and 4.\n");
                break;
            }

            char *chosen_cgroup = available_cgroups[cgroup_option - 1];

            if (check_limits_of_system_resources(container_name, chosen_cgroup) == 0)
            {
                printf("System resources limits checked successfully.\n");
            }
            else
            {
                printf("Error: Failed to check system resources limits.\n");
            }

            printf("Press ENTER to continue..."); // STOP HERE
            while (getchar() != '\n')
                ; // Clear the input buffer
            break;
        }

        case 7: // Establish a connection with a Container
        {
            clear_screen();

            printf("Enter the name of the Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            if (start_connection(container_name) == 0)
            {
                printf("Connection established successfully with Container %s.\n", container_name);
            }
            else
            {
                printf("Error: Failed to establish connection with Container %s.\n", container_name);
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case 8: // Copy a file to a Container
        {
            clear_screen();

            printf("Enter the name of the Container: ");
            if (read_input(container_name, CONTAINER_NAME_SIZE) < 0)
                break;

            char file_name[FILENAME_BUFFER_SIZE] = {0};

            printf("Enter the name of the file to copy: ");
            if (fgets(file_name, FILENAME_BUFFER_SIZE, stdin) == NULL)
            {
                printf("Error: Failed to read the file name.\n");
                break;
            }

            file_name[strcspn(file_name, "\n")] = 0; // Remove the newline character

            if (copy_file_to_container(container_name, file_name) == 0) // copy the file
            {
                printf("File \"%s\" copied successfully to Container %s.\n", file_name, container_name);
            }
            else
            {
                printf("Error: Failed to copy file \"%s\" to Container %s.\n", file_name, container_name);
            }

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;

            memset(container_name, 0, CONTAINER_NAME_SIZE); // clear name buffer

            break;
        }

        case EXIT_OPTION:
            printf("Exiting...\n");
            break;
        default:
            printf("Error: Invalid option. Please ENTER a number between 1 and %d.\n", EXIT_OPTION);
            break;
        }
    } while (option != EXIT_OPTION);

    return 0;
}