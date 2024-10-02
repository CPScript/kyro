// main.c

#include <stdio.h>
#include <string.h>

int main(void) {
    printf("Kyro OS started\n");

    // Initialize the operating system
    init_os();

    // Start the command-line interface
    start_cli();

    return 0;
}

void init_os(void) {
    // Initialize the operating system
    // Initialize the file system
    init_fs();

    // Initialize the process manager
    init_pm();

    // Initialize the memory manager
    init_mm();
}

void start_cli(void) {
    // Start the command-line interface
    // Print the command prompt
    printf("> ");

    // Read the command
    char command[256];
    fgets(command, 256, stdin);

    // Execute the command
    execute_command(command);
}

void init_fs(void) {
    // Initialize the file system
    // Create the root directory
    mkdir("/");

    // Create the /bin directory
    mkdir("/bin");

    // Create the /dev directory
    mkdir("/dev");

    // Create the /etc directory
    mkdir("/etc");

    // Create the /home directory
    mkdir("/home");

    // Create the /lib directory
    mkdir("/lib");

    // Create the /proc directory
    mkdir("/proc");

    // Create the /sbin directory
    mkdir("/sbin");

    // Create the /sys directory
    mkdir("/sys");

    // Create the /tmp directory
    mkdir("/tmp");

    // Create the /usr directory
    mkdir("/usr");

    // Create the /var directory
    mkdir("/var");
}

void init_pm(void) {
    // Initialize the process manager
    // Create the process table
    uint32_t *process_table = (uint32_t *)0x10000;
    process_table[0] = 0x00000001; // process 1
    process_table[1] = 0x00000002; // process 2
    process_table[2] = 0x00000003; // process 3

    // Load the process table
    asm volatile("movl %0, %%eax" :: "r" (process_table));
    asm volatile("int $0x10");
}

void init_mm(void) {
    // Initialize the memory manager
    // Create the memory map
    uint32_t *memory_map = (uint32_t *)0x10000;
    memory_map[0] = 0x00000001; // memory block 1
    memory_map[1] = 0x00000002; // memory block 2
    memory_map[2] = 0x00000003; // memory block 3

    // Load the memory map
    asm volatile("movl %0, %%eax" :: "r" (memory_map));
    asm volatile("int $0x10");
}

void execute_command(char *command) {
    // Execute the command
    // Parse the command
    char *argv[256];
    int argc = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }

    // Execute the command
    if (strcmp(argv[0], "ls") == 0) {
        // List the files in the current directory
        list_files();
    } else if (strcmp(argv[0], "cd") == 0) {
        // Change the current directory
        change_directory(argv[1]);
    } else if (strcmp(argv[0], "mkdir") == 0) {
        // Create a new directory
        create_directory(argv[1]);
    } else if (strcmp(argv[0], "rm") == 0) {
        // Remove a file or directory
        remove_file(argv[1]);
    } else if (strcmp(argv[0], "cp") == 0) {
        // Copy a file
        copy_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "mv") == 0) {
        // Move a file
        move_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "cat") == 0) {
        // Display the contents of a file
        display_file(argv[1]);
    } else {
        // Unknown command
        printf("Unknown command\n");
    }
}

void list_files(void) {
    // List the files in the current directory
    // Get the current directory
    char *current_directory = get_current_directory();

    // List the files in the current directory
    DIR *dir = opendir(current_directory);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void change_directory(char *directory) {
    // Change the current directory
    // Get the current directory
    char *current_directory = get_current_directory();

    // Change the current directory
    chdir(directory);
}

void create_directory(char *directory) {
    // Create a new directory
    // Create the directory
    mkdir(directory);
}

void remove_file(char *file) {
    // Remove a file or directory
    // Remove the file or directory
    unlink(file);
}

void copy_file(char *source, char *destination) {
    // Copy a file
    // Open the source file
    FILE *source_file = fopen(source, "r");

    // Open the destination file
    FILE *destination_file = fopen(destination, "w");

    // Copy the file
    char buffer[1024];
    while (fread(buffer, 1024, 1, source_file) == 1) {
        fwrite(buffer, 1024, 1, destination_file);
    }

    // Close the files
    fclose(source_file);
    fclose(destination_file);
}

void move_file(char *source, char *destination) {
    // Move a file
    // Copy the file
    copy_file(source, destination);

    // Remove the source file
    remove_file(source);
}

void display_file(char *file) {
    // Display the contents of a file
    // Open the file
    FILE *file_pointer = fopen(file, "r");

    // Display the contents of the file
    char buffer[1024];
    while (fread(buffer, 1024, 1, file_pointer) == 1) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file_pointer);
}
