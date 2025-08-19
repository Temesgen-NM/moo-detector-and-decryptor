# BOO

`boo` is a program designed to decrypt files that have been encrypted by `MOO`. It can also be used as a general-purpose file encryptor.

This program is intended for educational purposes. Please be aware of the potential impact on your files and take full responsibility when modifying and running it.

# Compilation
## Linux
To compile this program on Linux, you will need:

- A Linux-based operating system (e.g., Ubuntu, Kali, Arch, Fedora)
- A C compiler (e.g., GCC, Clang)
- Make
- A shell (e.g., bash, zsh)

With these tools installed, you can compile the program by running the `make` command in the project directory.

## Windows

Compiling this program on Windows can be challenging because it uses Linux-specific C headers such as `<unistd.h>`, `<sys/file.h>`, `<sys/fcntl.h>`, and `<sys/stat.h>`.

To resolve this, you can use a Linux-like environment on Windows, such as:
- MSYS2
- Cygwin

I recommend **MSYS2**, which includes the **pacman** package manager (from Arch Linux). You can use it to install all the necessary tools listed above.

Once your environment is set up, you can compile and run `boo` on Windows by executing the `make` command within the MSYS2 terminal.


# Tools
- [GNU Make](https://www.gnu.org/software/make/): A tool for automating the build process.
- [GCC](https://gcc.gnu.org/): The GNU Compiler Collection for C programs.
- [MSYS2](https://www.msys2.org/): A Linux-like environment for Windows that helps with compiling and running this application.