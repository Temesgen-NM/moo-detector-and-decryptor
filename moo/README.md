# MOO
Moo is a simple **unintelligent ransomware-ish** malware.
As stated before it is written for teaching purpose only, however
running this program in a host machine can affect your files. For
this reason one must take the full responsibility of this program while
modifying and running.

# Compilation
## Linux
In order to compile this program on linux, all required is 
a linux operating system with the following programs

- Linux kernel based OS (Ubuntu, Kali, Arch, Fedora...)
- C compiler (GCC, Clang, zig)
- Make
- Shell (bash, zsh, fish)

Once these programs are available on your machine you can simply
compile this program by running the **make** command in the working directory or workspace

## Windows
While this program is written on linux and specifically used **linux based C headers** 
it might be problematic to compile this program on windows.
One of the main problem is that we used the
```code
#include <unistd.h>
#include <sys/file.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
```
One way to overcome this unsettling situation is by installing a **tool or more likely a linux environment**
on you machin. Note that this is not WSL. There are tools like
- MSYS2
- Cygwin

Installing these tools will provide a suitable environment just like linux, but actually one can
develop and run programs on windows as in like linux.
My favorite is **MSYS2** since it provides a package manager that is the same as **ARCH Linux**
known as **pacman**.
With **pacman** in MSYS2 you can install all the necessary packages and tools listed above.

Finally by running the make program in your **MSYS2** environment you can compile and run **moo** for windows.


# Tools
[GNU Make](https://www.gnu.org/software/make/) for building c, c++, rust and other programs

[GCC](https://gcc.gnu.org/) the free **C** compiler for compiling **C** programs.

### windows users can use this linux environment to compile and run your application.
[MSYS2](https://www.msys2.org/) linux like environment for windows
