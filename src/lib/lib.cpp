#include <stdio.h>
#include <lxc/lxccontainer.h>
#include <string.h>
#define MAX_ARGS 100

int create_new_container(const char *container_name)
{
    struct lxc_container *container;
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

    printf("Container %s created\n", container_name);

    if (!container->start(container, 0, NULL))
    {
        fprintf(stderr, "Failed to start the container: %s\n\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

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

    printf("Container %s\n", container_name);
    printf("Current state: %s\n", container->state(container));

    if (!container->destroy(container))
    {
        fprintf(stderr, "Failed to destroy the container: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("Container %s removed\n", container_name);

out:
    lxc_container_put(container);
    return result;
}

int list_containers(void)
{
    struct lxc_container **containers;
    char **containers_names;
    int number_of_active_containers = 0;
    int result = 0;

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

    free(containers_names);
out:
    return result;
}

int start_network_connection(const char *container_name) // TODO: Implement this function
{
    printf("Starting network connection for container %s\n", container_name);
    return 0;
}

int run_command_in_container(const char *container_name, char *command)
{
    int result = 0, token_index = 0;
    struct lxc_container *container;
    char *arguments[MAX_ARGS] = {0}, *token;

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

int define_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem, const char *cgroup_value) // FIXME: Cgroup value is not being set
{
    struct lxc_container *container;
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

    printf("Defining limits of system resources for container %s\n", container_name);

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

int check_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem) // FIXME: Cgroup value is not being retrieved
{
    struct lxc_container *container;
    int result = 0;
    char *cgroup_value = NULL;

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

    printf("Checking limits of system resources for container %s\n", container_name);

    if (container->get_cgroup_item(container, cgroup_subsystem, cgroup_value, 0) < 0)
    {
        fprintf(stderr, "Failed to get cgroup: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("The limit defined in the cgroup subsystem %s is %s\n", cgroup_subsystem, cgroup_value);
    free(cgroup_value);

out:
    lxc_container_put(container);
    return result;
}