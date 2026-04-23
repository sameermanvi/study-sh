#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char input[1024];
    
    //  a variable to track my current subject state
    char current_mode[50] = ""; 

    // my semester subjects
    char *subjects[] = {"Chemistry", "Mechanics", "Electronics", "C_Programming"};
    int num_subjects = 4;

    while(1) {
        // The Context-Aware Prompt
        // If current_mode has text in it, show the subject in brackets
        if (strlen(current_mode) > 0) {
            printf("[%s] study-sh> ", current_mode);
        } else {
            printf("study-sh> ");
        }
        
        if (!fgets(input, 1024, stdin)) break; 
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0 || strcmp(input, "sleep") == 0) {
            printf("Shutting down workspace. See ya!\n");
            break; 
        }
        
        // 2. UPGRADED: The Build Command
        else if (strcmp(input, "build") == 0) {
            printf("Initializing study workspace...\n");
            mkdir("Notes", 0777); // Ensure the main folder exists
            
            // Loop through your subjects array and create a subfolder for each
            for (int i = 0; i < num_subjects; i++) {
                char path[100];
                sprintf(path, "Notes/%s", subjects[i]); // Combines strings like "Notes/Mechanics"
                
                if (mkdir(path, 0777) == 0) {
                    printf("Created %s\n", path);
                } else {
                    printf(" %s already exists.\n", path);
                }
            }
        }
        
        // 5. NEW: The Quick Capture 'add' Command
        else if (strncmp(input, "add ", 4) == 0) {
            // First, make sure we are actually in a subject mode
            if (strlen(current_mode) == 0) {
                printf("⚠️ You need to enter a subject mode first (e.g., type 'mechanics').\n");
            } else {
                // Extract everything after "add " (which is the note itself)
                char *note_text = input + 4; 
                
                // Build the file path: Notes/Mechanics/notes.txt
                char filepath[200];
                sprintf(filepath, "Notes/%s/notes.txt", current_mode);

                // 1. OPEN the file in "a" (append) mode. 
                FILE *file = fopen(filepath, "a");
                
                if (file == NULL) {
                    printf("Error: Could not open %s. Did you run 'build' first?\n", filepath);
                } else {
                    // 2. WRITE the note to the file with a bullet point and a newline
                    fprintf(file, "- %s\n", note_text);
                    
                    // 3. CLOSE the file to save it to the hard drive
                    fclose(file);
                    printf(" Note added to %s\n", current_mode);
                }
            }
        }




        else if (strcmp(input, "help") == 0) {
            printf("\n--- study-sh Commands ---\n");
            printf("  help        : Show this list\n");
            printf("  build       : Initialize workspace folders\n");
            printf("  [subject]   : Type a subject name (e.g., mechanics) to enter its mode\n");
            printf("  leave       : Exit the current subject mode\n");
            printf("  exit/sleep  : Shut down the workspace\n");
            printf("-------------------------\n\n");
        }
        
        // 3. NEW: Mode Exiting
        else if (strcmp(input, "leave") == 0) {
            strcpy(current_mode, ""); // Clear the string to return to base mode
        }

        // 4. NEW: Subject Switching Logic
        else if (strcmp(input, "chemistry") == 0) strcpy(current_mode, "Chemistry");
        else if (strcmp(input, "mechanics") == 0) strcpy(current_mode, "Mechanics");
        else if (strcmp(input, "electronics") == 0) strcpy(current_mode, "Electronics");
        else if (strcmp(input, "c_programming") == 0) strcpy(current_mode, "C_Programming");
        
        else {
            printf("Command not recognized: %s\n", input);
        }
    }

    return 0;
}