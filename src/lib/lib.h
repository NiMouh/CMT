#ifndef LIB_H
#define LIB_H

/**
 * @file lib.h
 * @brief This file contains the definitions of the functions used in lib.c regarding LXC containers operations
 *
 * This file contains the definitions of the functions used in lib.c
 * The functions are used to create, remove, list, start, run commands, run applications, copy files, define limits and check limits of system resources on these containers
 *
 * @author Simão Andrade
 * @date 2024-06-13
 */

/**
 * @brief Create a new LXC container object
 *
 * @param container_name name of the container
 * @return int 0 on success, -1 on failure
 */
int create_new_container(const char *container_name);

/**
 * @brief Remove an existing LXC container object
 *
 * @param container_name name of the container
 *
 * @return int 0 on success, -1 on failure
 */
int remove_container(const char *container_name);

/**
 * @brief List all the active LXC containers
 *
 * @return int 0 on success, -1 on failure
 */
int list_containers(void);

/**
 * @brief Connect to the shell of a given LXC container
 *
 * @param container_name name of the container
 *
 * @return int 0 on success, -1 on failure
 */
int start_connection(const char *container_name);

/**
 * @brief Run a shell command in a LXC container
 *
 * @param container_name name of the container
 * @param command shell command to execute
 * @param command_length length of the command
 *
 * @return int 0 on success, -1 on failure
 */
int run_command_in_container(const char *container_name, char *command);

/**
 * @brief Copy a file to a LXC container home directory
 *
 * @param container_name name of the container
 * @param file_name name of the file
 *
 * @return int 0 on success, -1 on failure
 */
int copy_file_to_container(const char *container_name, const char *file_name);

/**
 * @brief Define limits of system resources for a LXC container by setting cgroup values
 *
 * @param container_name name of the container
 * @param cgroup_subsystem cgroup subsystem (resource)
 * @param cgroup_value cgroup value
 *
 * @return int 0 on success, -1 on failure
 */
int define_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem, const char *cgroup_value);

/**
 * @brief Get the limits of system resources for a LXC container by showing the current cgroup values
 *
 * @param container_name name of the container
 * @param cgroup_subsystem cgroup subsystem (resource)
 *
 * @return int 0 on success, -1 on failure
 */
int check_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem);

#endif // LIB_H