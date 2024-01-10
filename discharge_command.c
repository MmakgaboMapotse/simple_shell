#include "shell.h"

/**
 * discharge_command - function that discharges the command
 * @command: command to discharge
 * @arg: command passed
 * @env: environmental variable passed from environ
 */

void discharge_command(char **command, char *arg, char **env)
{
	node_checker *path_check;
	char *path, **split_path;
	int cmd_check = 0;

	cmd_check = builtin_cmd_check(command, env);
	if (cmd_check)
		return;
	path_check = malloc(sizeof(node_checker));
	if (!path_check)
		return;
	if (strstr(command[0], "/"))
	{
		path_check->valid_path = executable_file_check(command[0]);
		path_check->bin = strdup(command[0]);
		cmd_check = (path_check->valid_path) ? 1 : 0;
	}
	else
	{
		path = paths();
		split_path = path_token(path);
		cmd_check = verify_bin(split_path, arg, path_check);
		cleanup_command(split_path);
	}
	if (cmd_check)
		execute(command, env, path_check);
	else
		command_not_found(command[0], command);

}


/**
 * executable_file_check - checks if a file path/file exists and can be run
 *
 * @string: command to be verified
 * Return: 0 or 1
 *
 */
int executable_file_check(char *string)
{
	if (access(string, F_OK) != -1)
	{
		if (access(string, X_OK) != -1)
			return (1);
		else
			return (0);
	}
	return (0);
}


/**
 * verify_bin - function to verify the paths and the command
 *
 * @paths: tokenized path from $PATH
 * @command: the command passed by the user (argv[0])
 * @path_check: struct holding info on if the path is valid
 *
 * Return: 0 or 1
 */
int verify_bin(char **paths, char *command, node_checker *path_check)
{
	int i = 0, cmd_len = 0, result;
	char *new_path;

	cmd_len = strlen(command) + 2;
	while (paths[i])
	{
		new_path = malloc(strlen(paths[i]) + cmd_len);
		strcpy(new_path, paths[i]);
		strcat(new_path, "/");
		strcat(new_path, command);
		result = executable_file_check(new_path);
		if (result)
		{
			path_check->valid_path = 1;
			path_check->bin = strdup(new_path);
			free(new_path);
			return (1);
		}
		free(new_path);
		i++;
	}
	return (0);
}

/**
 * execute - function that executes the command
 *
 * @commands: commands to execute
 * @env: environment
 * @path_check: struct containing file status and path
 *
 */
void execute(char **commands, char **env, node_checker *path_check)
{
	int status;
	pid_t child_pid;

	if (path_check->valid_path)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			status = execve(path_check->bin, commands, env);
			if (status == -1)
				errors(commands);
		}
		cleanup_struct(path_check);
		cleanup_command(commands);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
			exit(2);
	}
	else
		command_not_found(commands[0], commands);
}

/**
 * errors - displays error to the terminal
 * @args: commands passed
 */
void errors(char **args)
{
	fprintf(stderr, "%s: cannot access '%s': No such file or directory\n",
	args[0], args[1]);
	cleanup_command(args);
}
