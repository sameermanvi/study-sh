#include<>stdio.h>
#include<>stdstring.h>

int main() {
    char input[1024];


    while(1){
        printf("study-sh> ");


        if(!fgets(input, 1024, stdin)) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;

        if(strcmp(input, "exit") == 0) || strcmp(input, "sleep" == 0 ) {
            printf("Shutting down workspace. Goodnight!\n");
            break; 
        }
        printf("You typed: %s\n", input);
    }

    return 0;

}