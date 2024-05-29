#include <stdio.h>
#include <lxc/lxccontainer.h>

int create_new_container(const char *container_name)
{
    struct lxc_container *container;
    int result = 0;

    container = lxc_container_new(container_name, NULL);
    if (!container)
    {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        result = -1;
        goto out;
    }

    if (container->is_defined(container))
    {
        fprintf(stderr, "Container already exists\n");
        result = -1;
        goto out;
    }

    if (!container->createl(container, "lxc-local", NULL, NULL, LXC_CREATE_QUIET, "-d", "ubuntu", "-r", "focal", "-a", "amd64", NULL))
    {
        fprintf(stderr, "Failed to create container rootfs: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("Container %s created\n", container_name);
    if (!container->start(container, 0, NULL))
    {
        fprintf(stderr, "Failed to start the container: %s\n", container->error_string ? container->error_string : "unknown error");
        result = -1;
        goto out;
    }

    printf("Container state: %s\n", container->state(container));
    printf("Container PID: %d\n", container->init_pid(container));

out:
    lxc_container_put(container);
    return result;
}

int remove_container(const char *container_name)
{
    struct lxc_container *container;
    int result = 0;

    container = lxc_container_new(container_name, NULL);
    if (!container)
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

int start_network_connection(const char *container_name) // TODO: Implement this function
{
    printf("Starting network connection for container %s\n", container_name);
    return 0;
}

int execute_command_in_container(const char *container_name, const char *command) // TODO: Implement this function
{
    printf("Executing command \"%s\" in container %s\n", command, container_name);
    return 0;
}

int execute_application_in_container(const char *container_name, const char *application) // TODO: Implement this function
{
    printf("Executing application \"%s\" in container %s\n", application, container_name);
    return 0;
}

int copy_file_to_container(const char *container_name, const char *file_name) // TODO: Implement this function
{
    printf("Copying file \"%s\" to container %s\n", file_name, container_name);
    return 0;
}