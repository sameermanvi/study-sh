#include <stdio.h>
#include <string.h>
#include <sys/stat.h> // New: For the mkdir function

int main() {
    char input[1024];

    while(1) {
        printf("study-sh> ");
        
        if (!fgets(input, 1024, stdin)) {
            break; 
        }

        input[strcspn(input, "\n")] = 0;

        
        if (strcmp(input, "exit") == 0 || strcmp(input, "sleep") == 0) {
            printf("Shutting down workspace. Goodnight!\n");
            break; 
        }
        
        // build command to set up the study workspace
        else if (strcmp(input, "build") == 0) {
            printf("Initializing study workspace...\n");
            
            // Create the main Notes directory
            // 0777 gives read/write/execute permissions
            if (mkdir("Notes", 0777) == 0) {
                printf(" Created 'Notes' directory.\n");
            } else {
                printf("'Notes' directory might already exist or an error occurred.\n");
            }
        }
        
        // 3. NEW: Check for the help command
        else if (strcmp(input, "help") == 0) {
            printf("\n--- study-sh Commands ---\n");
            printf("  help  : Show this list of commands\n");
            printf("  build : Initialize study workspace (Creates Notes folder)\n");
            printf("  exit  : Shut down the workspace (also 'sleep')\n");
            printf("-------------------------\n\n");
        }
        
        else {
            printf("Command not recognized: %s\n", input);
        }
    }

    return 0;
}