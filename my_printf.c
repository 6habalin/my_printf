#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "func.c"

int my_printf(char * restrict format, ...);
char* myItoa(long int num, char* str, int base);
char* myHex(int number, int counter);
char * myUtoa(unsigned int n, int size);
char* longHex(unsigned long *decimal, int size);
int numSize(long int num);
char* myNegativeHex(unsigned int number, int size);

int main() {
    
    int a;
    my_printf("Hello %c!\n", "?");

    return 0;
}

int my_printf(char * restrict format, ...) {

    char *ptr;

    va_list objectsList;
    int length = 0;

    va_start(objectsList, format);

    for (ptr = format; *ptr != '\0'; ptr++) {
        while(*ptr != '%'){         //go through format
            if(*ptr != '\0'){
                write(1, ptr, 1);
                ptr++;
                length++;
            }  else {
            break;
            }
        }

        if(*ptr == '\0'){               //break after format is printed
            break;
            free(ptr);
        }

        ptr++;
        char *tmp;
        if (*ptr == 's') {              //%s and NULL      
        
            char* string = va_arg(objectsList, char*);

            if(string == NULL){

                tmp = "(null)";
                length+=6;
            } else {
                
                tmp = string;
                length+=strlen(tmp);
            }

        } else if (*ptr == 'd') {       //%d

            int i = va_arg(objectsList, int);

            char* a = malloc(numSize(i) + 2);
            tmp = myItoa(i, a, 10);
        
            length+=strlen(tmp);
        
        } else if (*ptr == 'o') {       //%o        

            int i = va_arg(objectsList, int);
            tmp = malloc(numSize(i) * 2);
            myItoa(i, tmp, 8);

            length+=strlen(tmp);

        } else if (*ptr == 'u') {       //%u        

            int i = va_arg(objectsList, int);
            unsigned int b = i;
            int mem = numSize(b);
            
            tmp = myUtoa(b, numSize(b));

            length+=strlen(tmp);
            
        } else if (*ptr == 'x') {       //%x  
            
            int i = va_arg(objectsList, int);
            if (i > 0) {

                tmp = myHex(i, numSize(i));

            } else {
                unsigned int num = i;
                
                tmp = myNegativeHex(num, numSize(num));
            }

            length+=strlen(tmp);
            
        } else if (*ptr == 'c') {       //%c         

            char* i = va_arg(objectsList, char*);
    
            tmp = i;
            length++;

        } else if (*ptr == 'p') {       //%p     

            void* str;
            str = va_arg(objectsList, void*);

            unsigned long int address;
            address = (unsigned long int)&str;
            
            tmp = longHex(&address, numSize(address));

            length+=strlen(tmp) + 2;
        }

        if(*ptr == 'p'){

            write(1, "0x", 3);
            write(1, tmp, strlen(tmp) + 1);
        } else {

            write(1, tmp, strlen(tmp));
        }

    }

    //printf("%d", length);               //prints size of printf()
    va_end(objectsList);
    return length;
}