> Kyro : Your in control
* name change was made to fit the purpose o this operating system... "The name "Kyro" comes from the Greek word "kyrios," meaning "lord" or "master." This name suggests that the user is in control of their own data and privacy, which aligns with the principles of a privacy OS."

### **Want to contribute?**
* I would love help with the development of this project. Create a request! <3

### Need to:
* Implement a logging system to track events, errors, and user actions. This helps with debugging and user support.
* Enhance error handling throughout your code, providing more informative messages for users.
* Password hashing (e.g., bcrypt or SHA-256) for better security.
* Expand user roles with permissions to manage file access and operations based on role.
* Implement a more sophisticated file system that can handle directories, permissions, and file attributes.
* Implement more file operations (copy, move, edit) and error handling for file actions.
* Develop a simple networking stack for basic connectivity (e.g., TCP/IP).
* Consider implementing secure remote access capabilities (e.g., SSH).
* Implement tab completion and command history in the terminal.
* Consider adding a basic GUI for improved user experience. not till later
* Implement system monitoring tools to check CPU usage, memory, and file system health.
* Provide user feedback on system performance and potential bottlenecks.
* Create user-friendly documentation to help new users understand your OS and its features.

  a simple and user-friendly operating system designed with privacy and security in mind. This document provides an overview of how to install, configure, and use Privacy OS effectively.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Getting Started](#getting-started)
- [User Management](#user-management)
- [File System](#file-system)
- [Terminal Commands](#terminal-commands)
- [Networking](#networking)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](https://github.com/CPScript/os/LICENSE)

### Features

- **User Management**: Create and manage user accounts with admin and regular user roles.
- **File System**: A simple file system to create, delete, and manage files and directories.
- **Terminal Interface**: Command-line interface to interact with the OS and execute commands.
- **Networking**: Basic networking capabilities to install and run services like Tor for enhanced privacy.

### Installation

To install Privacy OS, follow these steps:

1. **Clone the Repository**:
   ```
   git clone <repository-url>
   cd Privacy-OS
   ```
   
2. **Build the OS Image**: Make sure you have the necessary tools installed (`nasm`, `gcc`, and `ld`):
   ```
   make
   ```
   
3. **Run the OS**:
   ```
   qemu-system-x86_64 -drive file=os-image.bin,format=raw
   ```
   
### Getting Started
* Upon booting Privacy OS, you'll see the welcome message, followed by a terminal prompt. From here, you can execute commands to manage users, files, and more.

### User Management
**Creating Users**:
* To create a new user, use the `adduser` command:
  ```
  adduser <username> <password>
  ```

**Logging In**:
* To log in as an existing user, use:
  ```
  login <username> <password>
  ```

**User Roles**:
* Admin Users: Have full access to all commands and can manage other users.
* Regular Users: Have limited permissions to maintain privacy.

### File System
**Creating Files and Directories**:
* To create a file:
  ```
  create <file_name>
  ```

* To create a directory:
  ```
  mkdir <dir_name>
  ```

**Deleting Files and Directories**:
* To delete a file:
  ```
  delete <file_name>
  ```

* To remove a directory:
  ```
  rmdir <dir_name>
  ```

**Listing Files**:
* To list all files and directories in the current location:
  ```
  ls
  ```

**Reading File Contents**:
* To read the contents of a file:
  ```
  cat <file_name>
  ```

### Terminal Commands
**Here's a list of available commands**:

* `adduser <username> <password>`: Create a new user.
* `login <username> <password>`: Log in to your account.
* `create <filename>`: Create a new file.
* `mkdir <dirname>`: Create a new directory.
* `delete <filename>`: Delete a file.
* `rmdir <dirname>`: Remove a directory.
* `ls`: List files and directories.
* `cat <filename>`: Display the contents of a file.
* `help`: Display a list of available commands.

### Networking
This OS supports basic networking capabilities. Upon first boot, it will check for Tor installation. If not installed, it will prompt for installation.


**Starting Tor**
* Tor can be started automatically upon initialization or manually by running:
  ```
  start_tor
  ```
This will help anonymize your internet traffic.

### Troubleshooting
* **OS Won't Boot**: Ensure you built the OS image correctly. If your using a VM to boot then make sure you are using the appropriate emulator settings.
* **User Commands Not Working**: Check that you're logged in as a user with sufficient permissions.
* **File Operations Fail**: Ensure that the file or directory exists and that you have the necessary permissions.
