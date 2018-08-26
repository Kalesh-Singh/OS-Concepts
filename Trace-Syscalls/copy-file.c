// Run the command
// strace ./copy_file
// to see the system calls that this program makes.

#include <stdio.h>
int main() {
    char in_file[80];
    char out_file[80];

    printf("Enter the name of the input file: ");
    scanf("%s", in_file);

    printf("Enter the name of the output file: ");
    scanf("%s", out_file);

    printf("Input file = %s\n", in_file);
    printf("Output file = %s\n", out_file);

    FILE* in = fopen(in_file, "r");
    if (in ==  NULL) {
        perror("Failed to open input file.");
    }
    FILE* out = fopen(out_file, "w");
    if (out == NULL) {
        perror("Failed to open output file.");
    }

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
    }   

    fclose(in);
    fclose(out); 

    
    
    return 0;
}
