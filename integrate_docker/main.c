#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    printf("Hello World\n");
    printf("Number of arguments: %d\n", argc);
    for(uint8_t i=0; i < argc; i++){
        printf("argv[%d]= %s\n", i, argv[i]);
    }
    return 0;
}