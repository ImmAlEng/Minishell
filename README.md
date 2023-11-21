![image](https://github.com/ImmAlEng/Minishell/assets/112417315/99e4dff2-1e40-43e4-a672-15ffd7eabbb3)

# Minishell

Minishell is a simple Unix shell implementation written in C. It provides a basic command-line interface that allows users to interact with the operating system by executing commands.

## Features

- **Command Execution**: Minishell can execute various shell commands entered by the user.
- **Piping**: Support for simple command pipelines.
- **Redirection**: Basic input and output redirection.
- **Environment Variables**: Handling and expansion of environment variables.
- **Signal Handling**: Basic signal handling for Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT).

## Getting Started

To compile and run Minishell, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/minishell.git
   cd minishell
   ```

2. **Build the Project:**
   ```bash
   make
   ```

3. **Run Minishell:**
   ```bash
   ./minishell
   ```

## Usage

Once Minishell is running, you can enter commands in the prompt. Basic command execution, piping, and redirection are supported. Use the `exit` command to quit Minishell.

Example:
```bash
$ ./minishell
minishell> ls -l | grep README.md
```
