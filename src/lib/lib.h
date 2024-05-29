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
 * @return int 0 on success, -1 on failure
 */
int remove_container(const char *container_name);

/**
 * @brief Start the network connection for a container
 *
 * @param container_name name of the container
 * @return int 0 on success, -1 on failure
 */
int start_network_connection(const char *container_name);

/**
 * @brief Execute a command in a container
 *
 * @param container_name name of the container
 * @param command command to execute
 * @return int 0 on success, -1 on failure
 */
int execute_command_in_container(const char *container_name, const char *command);

/**
 * @brief Execute an application in a container
 *
 * @param container_name name of the container
 * @param application application to execute
 * @return int 0 on success, -1 on failure
 */
int execute_application_in_container(const char *container_name, const char *application);

/**
 * @brief Copy a file to a container
 *
 * @param container_name name of the container
 * @param file_name name of the file
 * @return int 0 on success, -1 on failure
 */
int copy_file_to_container(const char *container_name, const char *file_name);

#endif // LIB_H