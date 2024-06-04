#ifndef LIB_H
#define LIB_H

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
 * @brief Run an application in a container
 *
 * @param container_name name of the container
 * @param application application to execute
 * 
 * @return int 0 on success, -1 on failure
 */
int run_application_in_container(const char *container_name, const char *application);

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