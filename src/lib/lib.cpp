#include <stdio.h>
#include <string.h>
#include <lxc/lxccontainer.h>
#include <unistd.h>
#include <time.h>

#define MAX_COMMAND_ARGS 100

#define LOG_MESSAGE_SIZE 100
#define LOG_FILE_NAME "log.txt"

#define CGROUP_VALUE_BUFFER_SIZE 50

int add_log_message(const char *message, const char *file_name)
{
    FILE *file = fopen(file_name, "a");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        return -1;
    }

    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char time_string[26];
    strftime(time_string, 26, "%c", time_info);

    fprintf(file, "%s - %s\n", time_string, message);

    fclose(file);
    return 0;
}

int create_new_container(const char *container_name)
{
    struct lxc_container *container;
    char log_message[LOG_MESSAGE_SIZE] = {0};
    int result = 0;

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n\n");
        result = -1;
        goto out;
    }

    if (container->is_defined(container))
    {
        fprintf(stderr, "Container already exists\n\n");
        result = -1;
        goto out;
    }

    if (!container->createl(container, "download", NULL, NULL, LXC_CREATE_QUIET, "-d", "ubuntu", "-r", "bionic", "-a", "amd64", NULL))
    {
        fprintf(stderr, "Failed to create container rootfs: %s\n\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: Container %s created", container_name);
    add_log_message(log_message, LOG_FILE_NAME);

    printf("Container %s created\n", container_name);

    if (!container->start(container, 0, NULL))
    {
        fprintf(stderr, "Failed to start the container: %s\n\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: Container %s started", container_name);
    add_log_message(log_message, LOG_FILE_NAME);

    printf("Container %s started\n", container_name);
    printf("Current state: %s\n", container->state(container));
    printf("PID: %d\n", container->init_pid(container));

out:
    lxc_container_put(container);
    return result;
}

int remove_container(const char *container_name)
{
    struct lxc_container *container;
    char log_message[LOG_MESSAGE_SIZE] = {0};
    int result = 0;

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        result = -1;
        goto out;
    }

    if (!container->is_defined(container))
    {
        fprintf(stderr, "Container does not exist\n");
        result = -1;
        goto out;
    }

    if (!container->stop(container))
    {
        fprintf(stderr, "Failed to stop the container: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "WARNING LOG: Container %s stopped", container_name);
    add_log_message(log_message, LOG_FILE_NAME);

    printf("Container %s\n", container_name);
    printf("Current state: %s\n", container->state(container));

    if (!container->destroy(container))
    {
        fprintf(stderr, "Failed to destroy the container: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "WARNING LOG: Container %s destroyed", container_name);
    add_log_message(log_message, LOG_FILE_NAME);

    printf("Container %s removed\n", container_name);

out:
    lxc_container_put(container);
    return result;
}

int list_containers(void)
{
    struct lxc_container **containers;
    char **containers_names, log_message[LOG_MESSAGE_SIZE] = {0};
    int number_of_active_containers = 0, result = 0;

    number_of_active_containers = list_active_containers(NULL, &containers_names, &containers);
    if (number_of_active_containers < 0)
    {
        fprintf(stderr, "Failed to list containers\n\n");
        result = -1;
        goto out;
    }

    if (number_of_active_containers == 0)
    {
        printf("No active containers found!\n\n");
        goto out;
    }

    printf("NUMBER OF CONTAINERS: %d\n\n", number_of_active_containers);
    for (int index = 0; index < number_of_active_containers; index++)
    {
        printf("--- Container %d ---\n", index + 1);
        printf("Name: %s\n", containers_names[index]);
        printf("State: %s\n", containers[index]->state(containers[index]));
        printf("PID: %d\n", containers[index]->init_pid(containers[index]));
        printf("IP: %s\n", *containers[index]->get_ips(containers[index], "eth0", "inet", 0));
    }
    printf("\n");

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: Listed %d active containers", number_of_active_containers);
    add_log_message(log_message, LOG_FILE_NAME);

out:
    free(containers_names);
    return result;
}

int start_connection(const char *container_name)
{
    struct lxc_container *container;
    int result = 0, ttynum = -1; // allocate the first available tty
    char log_message[LOG_MESSAGE_SIZE] = {0};

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n\n");
        result = -1;
        goto out;
    }

    if (!container->is_running(container)) // not running
    {
        printf("Starting the container\n\n");
        if (!container->start(container, 0, NULL))
        {
            fprintf(stderr, "Failed to start the container: %s\n", container->error_string ? container->error_string : "unknown error");
            result = -1;
            goto out;
        }
    }

    printf("Starting connection for container %s\n", container_name);

    if (container->console(container, ttynum, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, 1) < 0)
    {
        fprintf(stderr, "Failed to start connection: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: Connection started for container %s", container_name);
    add_log_message(log_message, LOG_FILE_NAME);

out:
    lxc_container_put(container);
    return result;
}

int run_command_in_container(const char *container_name, char *command)
{
    int result = 0, token_index = 0;
    struct lxc_container *container;
    char *arguments[MAX_COMMAND_ARGS] = {0}, *token, log_message[LOG_MESSAGE_SIZE] = {0};

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        result = -1;
        goto out;
    }

    if (!container->is_running(container)) // not running
    {
        printf("Starting the container\n\n");
        if (!container->start(container, 0, NULL))
        {
            fprintf(stderr, "Failed to start the container: %s\n", container->error_string ? container->error_string : "unknown error");
            result = -1;
            goto out;
        }
    }

    printf("Executing command \"%s\" in container %s\n", command, container_name);

    token = strtok(command, " "); // Tokenizing command
    while (token != NULL)
    {
        arguments[token_index++] = token;
        token = strtok(NULL, " ");
    }
    arguments[token_index] = NULL; // Set the last argument to NULL

    if (container->attach_run_wait(container, NULL, command, arguments) < 0) // Run the command
    {
        fprintf(stderr, "Failed to execute command: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: Command \"%s\" executed in container %s", command, container_name);
    add_log_message(log_message, LOG_FILE_NAME);

out:
    lxc_container_put(container);
    return result;
}

int run_application_in_container(const char *container_name, const char *application) // TODO: Implement this function
{
    printf("Executing application \"%s\" in container %s\n", application, container_name);
    return 0;
}

int copy_file_to_container(const char *container_name, const char *file_name) // TODO: Implement this function
{
    printf("Copying file \"%s\" to container %s\n", file_name, container_name);
    return 0;
}

int define_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem, const char *cgroup_value)
{
    struct lxc_container *container;
    char log_message[LOG_MESSAGE_SIZE] = {0};
    int result = 0;

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        result = -1;
        goto out;
    }

    if (!container->is_running(container)) // not running
    {
        printf("Starting the container\n\n");
        if (!container->start(container, 0, NULL))
        {
            fprintf(stderr, "Failed to start the container: %s\n", container->error_string ? container->error_string : "unknown error");
            result = -1;
            goto out;
        }
    }

    printf("Defining limits of system resources (%s) for container %s\n", cgroup_subsystem, container_name);

    snprintf(log_message, LOG_MESSAGE_SIZE, "INFO LOG: The resource %s of the container %s was defined with value '%s'", cgroup_subsystem, container_name, cgroup_value);
    add_log_message(log_message, LOG_FILE_NAME);


    if (!container->set_cgroup_item(container, cgroup_subsystem, cgroup_value))
    {
        fprintf(stderr, "Failed to set cgroup: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

out:
    lxc_container_put(container);
    return result;
}

int check_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem)
{
    struct lxc_container *container;
    int result = 0, container_pid = -1;
    char cgroup_value[CGROUP_VALUE_BUFFER_SIZE] = {0};

    container = lxc_container_new(container_name, NULL);
    if (container == NULL)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        result = -1;
        goto out;
    }

    if (!container->is_running(container))
    {
        printf("Starting the container\n\n");
        if (!container->start(container, 0, NULL))
        {
            fprintf(stderr, "Failed to start the container: %s\n", container->error_string ? container->error_string : "unknown error");
            result = -1;
            goto out;
        }
    }

    container_pid = container->init_pid(container);
    if (container_pid < 0)
    {
        fprintf(stderr, "Failed to get the PID of the container: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("Checking limits of system resources (%s) for container %s\n with PID %d\n", cgroup_subsystem, container_name, container_pid);

    if (!container->get_cgroup_item(container, cgroup_subsystem, cgroup_value, sizeof(cgroup_value)))
    {
        fprintf(stderr, "Failed to get cgroup: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("Resource Value: %s\n", cgroup_value);

out:
    lxc_container_put(container);
    return result;
}