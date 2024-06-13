#ifndef LIB_H
#define LIB_H

/**
 * @file lib.h
 * @brief This file contains the definitions of the functions used in lib.c
 *
 * This file contains the definitions of the functions used in lib.c
 * The functions are used to create, remove, list, start, run commands, run applications, copy files, define limits and check limits of system resources for LXC containers
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
 * @brief List all the containers
 *
 * @return int 0 on success, -1 on failure
 */
int list_containers(void);

/**
 * @brief Start the connection for a container
 *
 * @param container_name name of the container
 *
 * @return int 0 on success, -1 on failure
 */
int start_connection(const char *container_name);

/**
 * @brief Run a command in a container
 *
 * @param container_name name of the container
 * @param command command to execute
 * @param command_length length of the command
 *
 * @return int 0 on success, -1 on failure
 */
int run_command_in_container(const char *container_name, char *command);

/**
 * @brief Copy a file to a container
 *
 * @param container_name name of the container
 * @param file_name name of the file
 *
 * @return int 0 on success, -1 on failure
 */
int copy_file_to_container(const char *container_name, const char *file_name);

/**
 * @brief Define limits of system resources for a container
 *
 * @param container_name name of the container
 * @param cgroup_subsystem cgroup subsystem (resource)
 * @param cgroup_value cgroup value
 *
 * @return int 0 on success, -1 on failure
 */
int define_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem, const char *cgroup_value);

/**
 * @brief Get the limits defined of a given cgroup subsystem
 *
 * @param container_name name of the container
 * @param cgroup_subsystem cgroup subsystem (resource)
 *
 * @return int 0 on success, -1 on failure
 */
int check_limits_of_system_resources(const char *container_name, const char *cgroup_subsystem);

#endif // LIB_H