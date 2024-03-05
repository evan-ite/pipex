## Pipex 42 Project


**Description:**
The pipex project is about handling pipes in a Unix-like environment. This program executes bash commands with their parameters, using input/output redirection via pipes to transfer data between commands and files. The program aims to mimic the behavior of pipes in bash.

---

**Installation:**

1. Clone the repository:
   ```bash
   git@github.com:evan-ite/pipex.git
   ```

2. Navigate to the project directory:
   ```bash
   cd pipex
   ```

3. Compile the project using make:
   ```bash
   make
   ```

---

**Usage:**

Run the game by executing the following command:
```bash
./pipex file1 cmd1 cmd2 file2
```
- `file1` : input file name, example file 'in' is already in the directory.
- `cmnd1`: First bash command with parameters.
- `cmnd2`: Second bash command with parameters.
- `file2` : output file name, file will be created if it doesn't exist.

The behavior of pipex mimics the following shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

---

**Examples:**

```bash
./pipex in "ls -l" "wc -l" out
```

```bash
./pipex in "cat" "grep sun" out
```

---

**Bonus**

The bonus part involves handling multiple pipes. This allows the program to execute a chain of shell commands.

Compile the bonus using make:
   ```bash
   make bonus
   ```

Usage:
   ```bash
  ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
   ```
---

**Author:**

Elise van iterson
e.vaniterson98@gmail.com
