#include "lib/lib.h"
#include <stdio.h>
#include <string.h>

#define CONTAINER_NAME_SIZE 100

int show_options_menu(void)
{
    int option = 0;

    printf("\033[H\033[J"); // Clear the screen
    printf("   ______            __        _                    __  ___                                                  __     ______            __\n");
    printf("  / ____/___  ____  / /_____ _(_)___  ___  _____   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_   /_  __/___  ____  / /\n");
    printf(" / /   / __ \\/ __ \\/ __/ __ `/ / __ \\/ _ \\/ ___/  / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ __ `__ \\/ _ \\/ __ \\/ __/    / / / __ \\/ __ \\/ / \n");
    printf("/ /___/ /_/ / / / / /_/ /_/ / / / / /  __/ /     / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_     / / / /_/ / /_/ / /  \n");
    printf("\\____/\\____/_/ /_/\\__/\\__,_/_/_/ /_/\\___/_/     /_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/ /_/ /_/\\___/_/ /_/\\__/    /_/  \\____/\\____/_/   \n");
    printf("                                                                         /____/                                                         \n");
    printf("1. Add a new Container\n");
    printf("2. Remove a Container\n");
    printf("3. Execute a command in a Container\n");
    printf("4. Establish a network connection with a Container\n");
    printf("5. Execute an application in a Container\n");
    printf("6. Copy a file to a Container\n");
    printf("7. Exit\n\n");
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

int main()
{

    int option = 0;
    char container_name[CONTAINER_NAME_SIZE] = {0};
    do
    {
        option = show_options_menu();
        getchar(); // Clear the newline character from the input buffer

        switch (option)
        {
        case 1: // FIXME: Add a new Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Adding a new Container...\n");

            // Ask for a container name
            printf("Enter the name of the new Container: ");
            if (fgets(container_name, CONTAINER_NAME_SIZE, stdin) == NULL)
            {
                printf("Error: Failed to read the container name.\n");
                break;
            }

            container_name[strcspn(container_name, "\n")] = 0; // Remove the newline character

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
        case 2: // FIXME: Remove a Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Removing a Container...\n");

            // Ask for a container name
            printf("Enter the name of the Container to remove: ");
            if (fgets(container_name, CONTAINER_NAME_SIZE, stdin) == NULL)
            {
                printf("Error: Failed to read the container name.\n");
                break;
            }

            container_name[strcspn(container_name, "\n")] = 0; // Remove the newline character

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
        case 3: // TODO: Execute a command in a Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Executing a command in a Container...\n");

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;
            break;
        }
        case 4: // TODO: Establish a network connection with a Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Establishing a network connection with a Container...\n");

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;
            break;
        }
        case 5: // TODO: Execute an application in a Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Executing an application in a Container...\n");

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;
            break;
        }
        case 6: // TODO: Copy a file to a Container
        {
            printf("\033[H\033[J"); // Clear the screen

            printf("Copying a file to a Container...\n");

            printf("Press ENTER to continue...");
            while (getchar() != '\n') // Clear the input buffer
                ;
            break;
        }
        case 7: // Exit
            printf("Exiting...\n");
            break;
        default:
            printf("Error: Invalid option. Please ENTER a number between 1 and 7.\n");
            break;
        }
    } while (option != 7);

    return 0;
}