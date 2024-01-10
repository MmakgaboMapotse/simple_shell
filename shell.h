#ifndef MAIN_H
#define MAIN_H


/**
 * struct exec_status - struct to contain information about
 * file path and command
 * @valid_path: int 1 (valid path) or 0 (invalid/no-existent path)
 * @bin: full path including the command
 */
typedef struct exec_status
{
	int valid_path;
	char *bin;
} node_checker;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>


extern char **environ;
void clean_getline_memory(char *string, size_t size);
int path_verification(char *path);
void free_memory_on_fail(char **memory, int i);
void discharge_command(char **command, char *arg, char **env);
void cleanup_command(char **);
void cleanup_struct(node_checker *);
char *paths();
char **path_token(char *string);
int executable_file_check(char *string);
int verify_bin(char **paths, char *command, node_checker *path_check);
void execute(char **commands, char **env, node_checker *path_check);
int builtin_cmd_check(char **array, char **envs);
int remove_spaces(char *string);
void free_buffer(char *dt, size_t size);
int get_path_count(char *path_string, char *delim);
void command_not_found(char *arg, char **argv);
void errors(char **args);
char **split_command(char *string);
int count_commands(char *, char *delim);
#endif
