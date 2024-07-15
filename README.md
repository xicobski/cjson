# cjson - A JSON parser made in C

A simple parser to `.json` files built in C.

This library has only **5** functions to interact with JSON files:

```c
// Reads the content of a json file.
char* jsonfread(const char* filename);

// Extracts a json object from the main json content.
char* getjson(const char* json, const char* key);

// Extacts a string value from a json object.
char* strjson(const char* json, const char* key);

// Extracts an integer value from a json object.
int intjson(const char* json, const char* key);

// Extacts a float value from a json object.
float floatjson(const char* json, const char* key);
```

The function `static char* strspc(const char* src)` only use is to remove the spaces, `\n`, and `\r` from the content read by `jsonfread`. 

## Example on how to use

```c
#include <stdio.h>
#include <stdlib.h>
#include "jsonify.h"

int main() {
    printf("\n\n");

    char* fcontent = jsonfread("sample"); // get the full json file
    printf("JSON Content: %s\n", fcontent);
    
    char* filter = getjson(fcontent, "uid1"); // filter the user with id equal to "uid1"
    printf("Filtered to \"uid1\": %s\n", filter);

    char* name = strjson(filter, "name");
    printf("Extracted the name: %s\n", name);

    int age = intjson(filter, "age");
    printf("Extracted the age as integer value: %d\n", age);

    float agef = floatjson(filter, "age");
    printf("Extracted the age as float value: %.2f\n", agef);

    char* country = strjson(filter, "country");
    printf("Extracted the country code: %s\n", country);
    
    printf("\n");
    return 0;
}
```
