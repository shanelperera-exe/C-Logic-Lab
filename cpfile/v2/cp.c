#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./cpfile source destination\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (src == NULL) {
        printf("ERROR: Couldn't open source file %s\n", argv[1]);
        return 1;
    }

    FILE *dest = fopen(argv[2], "wb");
    if (dest == NULL) {
        printf("ERROR: Couldn't open destination file %s\n", argv[2]);
        fclose(src);
        return 1;
    }

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0) {
       fwrite(&b, sizeof(b), 1, dest); 
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
    return 0;
}