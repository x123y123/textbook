/* Implement a function to read in characters from standard input and assign them to a buffer. The buffer will contain all of the characters read except for a terminating return character. Since we don't know how many characters the user will input, we don't know how long the buffer should be.*/

// We use the realloc function to allocate additional space by fixed increment amount

#include <stdio.h>
#include <stdlib.h>

void _safe_free(void **pp)
{
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

#define safe_free(p) _safe_free((void**)&p)
           

char *get_line(void)
{
    const size_t size_increment = 10;
    char *buffer = (char*)malloc(size_increment);
    char *current_position = buffer;     // *current_position = *buff
    size_t max_len = size_increment;
    size_t len = 0;
    int character;

    // error handling, check whether malloc is unable to allocate memory or not
    if (current_position == NULL) 
        return NULL;
    
    while(1) {
        // get char
        character = fgetc(stdin);
        //printf("%c\n", character);
        
        if(character == '\n')
            break;

        if (++len >= max_len) {
            // resize 
            char *new_buffer = realloc(buffer, max_len += size_increment);
            printf("realloc ACT!\n");

            // error handling, if realloc failed then free up the existing allocated memory and force the function to return NULL
            if (new_buffer == NULL) {
               /* free(buffer);
                  buffer = NULL; */
                safe_free(buffer);
                return NULL;
            }

            // get the new current position
            current_position = new_buffer + (current_position - buffer);
            buffer = new_buffer;
        }
        *current_position++ = character;
    }
    *current_position = '\0';
    return buffer;
}

int main()
{
    char *input_line = get_line();
    printf("input_line: %s\n", input_line);

    return 0;
}
