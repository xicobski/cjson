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
