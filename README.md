# Minishell - Complete Integrated Project

## Overview

This is a complete minishell implementation that combines parsing and execution components with norminette compliance.

## Project Structure

```
minishell/
├── minishell.h           # Unified header with all declarations
├── main_shell.c          # Main shell entry point with signal handling
├── Makefile             # Complete build system
├── test_complete.sh     # Comprehensive test script
│
├── libft/               # Custom C library
│   ├── libft.h
│   ├── Makefile
│   └── *.c              # Standard library functions
│
├── parsing/             # Command parsing module
│   ├── parsing/         # Core parsing logic
│   │   ├── parsing.c    # Main parsing entry point
│   │   ├── parsing2.c   # Token processing
│   │   ├── ft_lst.c     # Token list management
│   │   └── ...
│   ├── expander/        # Variable expansion
│   ├── lexer/          # Syntax validation
│   ├── env_cpy/        # Environment handling
│   └── signals/        # Signal management
│
└── exec/               # Command execution module
    └── srcs/           # Execution source files
        ├── exec.c      # Main execution logic
        ├── pipes.c     # Pipeline handling
        ├── builtins*.c # Built-in commands
        ├── redirection.c # I/O redirection
        └── ...
```

## Key Features

### ✅ **Parsing**
- Command line tokenization
- Pipe recognition (`|`)
- Redirection parsing (`>`, `>>`, `<`, `<<`)
- Quote handling (`'`, `"`)
- Variable expansion (`$VAR`)
- Syntax validation

### ✅ **Execution**
- Process management with fork/exec
- Pipeline implementation
- Built-in commands:
  - `echo` (with -n flag)
  - `cd` (with relative/absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- I/O redirection
- Here documents (`<<`)
- Signal handling (Ctrl+C, Ctrl+\\)

### ✅ **Features**
- Environment variable management
- Command history (readline)
- Error handling and status codes
- Memory management with cleanup
- Norminette compliant code

## Build Instructions

### Prerequisites
```bash
# Install readline library (if not available)
sudo apt-get install libreadline-dev  # Ubuntu/Debian
brew install readline                  # macOS
```

### Build Commands
```bash
# Full build
make

# Clean build
make clean && make

# Complete clean and rebuild
make re

# Clean everything
make fclean

# Run norminette check
make norm
```

## Usage

### Basic Usage
```bash
# Start the shell
./minishell

# Try basic commands
minishell$ echo "Hello World"
minishell$ pwd
minishell$ ls -la
minishell$ exit
```

### Advanced Features
```bash
# Pipes
minishell$ ls | grep .c | wc -l

# Redirections
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
minishell$ ls >> output.log

# Here documents
minishell$ cat << EOF
> line 1
> line 2
> EOF

# Variable expansion
minishell$ export NAME="World"
minishell$ echo "Hello $NAME"

# Built-ins
minishell$ cd /tmp
minishell$ pwd
minishell$ env | head -5
minishell$ export NEW_VAR="value"
minishell$ unset NEW_VAR
```

## Testing

### Automated Tests
```bash
# Run complete test suite
./test_complete.sh

# Test specific features
echo "ls | wc -l" | ./minishell
echo "echo hello" | ./minishell
```

### Manual Testing Checklist
- [ ] Basic commands (`ls`, `cat`, `grep`, etc.)
- [ ] Built-ins (`echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`)
- [ ] Pipes (`cmd1 | cmd2 | cmd3`)
- [ ] Redirections (`>`, `>>`, `<`)
- [ ] Here documents (`<<`)
- [ ] Variable expansion (`$VAR`, `$?`)
- [ ] Quotes (`'single'`, `"double"`)
- [ ] Signal handling (Ctrl+C, Ctrl+\\)
- [ ] Error handling
- [ ] Memory leaks (valgrind)

## Norminette Compliance

The project follows 42 School norminette standards:
- Max 25 lines per function
- Max 80 characters per line
- Max 5 functions per file
- Proper header format
- No global variables (except signal handler)
- Proper variable naming
- No forbidden functions

## Troubleshooting

### Common Issues

1. **Readline not found**
   ```bash
   sudo apt-get install libreadline-dev
   ```

2. **Compilation errors**
   ```bash
   make fclean && make
   ```

3. **Norminette errors**
   ```bash
   make norm
   ```

4. **Pipes not working**
   - Check if commands exist in PATH
   - Verify pipe parsing logic
   - Test with simple commands first

### Debug Mode
```bash
# Compile with debug symbols
make CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address"

# Run with valgrind
valgrind --leak-check=full ./minishell
```

## Architecture

### Parsing Flow
1. **Input** → readline gets user command
2. **Lexical Analysis** → tokenize and validate syntax
3. **Parsing** → create token list with types
4. **Expansion** → expand variables and globs
5. **Token List** → ready for execution

### Execution Flow
1. **Process Tokens** → iterate through token list
2. **Setup** → create pipes and redirections
3. **Fork** → create child processes
4. **Execute** → run commands or built-ins
5. **Cleanup** → wait for processes and clean up

## Contributing

When modifying the code:
1. Follow norminette standards
2. Update function declarations in `minishell.h`
3. Add appropriate source files to `Makefile`
4. Test functionality thoroughly
5. Check for memory leaks

## Files Modified/Created

- ✅ `minishell.h` - Unified header
- ✅ `main_shell.c` - Main executable
- ✅ `Makefile` - Complete build system
- ✅ `test_complete.sh` - Test suite
- ✅ All parsing and execution integration

The project is now ready for use and testing!