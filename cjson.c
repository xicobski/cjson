#include "jsonify.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define err(_e) ({ printf("[error] %s\n", _e); })

/// @brief Formats a json file to a one line string.
/// @param src Content of the json file.
/// @return New json string.
static char* strspc(const char* src) {
    bool quotes = false;
    size_t length = 0;
    for (uint16_t it = 0; it < strlen(src); it++) {
        if (*(src + it) == '\"')
            quotes = !quotes;

        if ((*(src + it) != ' ' && *(src + it) != '\n' && *(src + it) != '\r') || quotes)
            length++;
    }

    quotes = false;
    char* nospc = (char*)malloc(length + 1);
    memset(nospc, 0, length+1);
    for (uint16_t it = 0, indx = 0; it < strlen(src); it++) {
        if (*(src + it) == '\"') 
            quotes = !quotes;

        if (*(src + it) != ' ' && *(src + it) != '\n' && *(src + it) != '\r' || quotes) {
            *(nospc + indx) = *(src + it);
            indx++;
        }
    }

    return nospc;
}

/// @brief Read the content of a json file.
/// @param filename Name of the file.
/// @return String with the content of the file.
char* jsonfread(const char* filename) {
    char* extension = strstr(filename, ".");
    char* filepath;

    if (extension == NULL) {
        filepath = (char*)malloc(strlen(filename) + strlen(".json") + 1);
        strcpy(filepath, filename);
        strcat(filepath, ".json");
    }else if (!strcmp(extension, ".json")) {
        filepath = (char*)malloc(strlen(filename) + 1);
        strcpy(filepath, filename);
    } else {
        err("Invalid file!");
        free(extension);
        return "\0";
    }
    free(extension);

    FILE* file = fopen(filepath, "r+");
    if (!file) {
        printf("[error] No file [%s] available!\n", filepath);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* rxbuff = (char*)malloc(fsize + 1);
    memset(rxbuff, 0, fsize+1);
    if (!rxbuff) {
        err("Segmentation fault!\n");
        fclose(file);
        return "\0";
    }

    fread(rxbuff, 1, fsize, file);
    fclose(file);
    char* trimrx = strspc(rxbuff);
    return trimrx;
}

/// @brief Extracts a json object from the main json content.
/// @param json Main content where the sub json object is located.
/// @param key Json key to filter the object to extract.
/// @return String with the extracted json object.
char* getjson(const char* json, const char* key) {
    char* keyptr = strstr(json, key);

    if (keyptr == NULL) {
        err("Invalid key!");
        return "\0";
    }
    
    uint8_t brackets = 0;
    char* value_sptr = (char*)NULL;
    char* value_eptr = (char*)NULL;
    for (uint8_t it = 0; it < strlen(keyptr); it++) {
        if (*(keyptr + it) == '{') {
            brackets++;
        }

        if (*(keyptr + it) == '}') {
            brackets--;
        }

        if (brackets == 1 && value_sptr == NULL) {
            value_sptr = (keyptr + it);
        }

        if (brackets == 0 && value_sptr != NULL) {
            value_eptr = (keyptr + it + 1);

            char hold = *value_eptr;
            *value_eptr = '\0';
            char* value = (char*)malloc(strlen(value_sptr) + 1);
            strcpy(value, value_sptr);
            *value_eptr = hold;

            return value;
        }
    }
    return "\0";
}

/// @brief Extracts a string value from a json object.
/// @param json Json object where the value is stored.
/// @param key Json Key to filter the string to extract.
/// @return Extracted value as a string.
char* strjson(const char* json, const char* key) {
    char* keyptr = strstr(json, key);

    if (keyptr == NULL) {
        err("Invalid key!");
        return "\0";
    }

    while (*keyptr != ':')
        keyptr++;
    
    keyptr++;
    if (*keyptr == '\"')
        keyptr++;

    char* value_eptr = NULL;
    for (uint8_t it = 0; it < strlen(keyptr); it++) {
        if (*(keyptr + it) == '\"') {
            value_eptr = (keyptr + it);
            break;
        }
    }

    char hold = *value_eptr;
    *value_eptr = '\0';
    char* value = (char*)malloc(strlen(keyptr));
    strcpy(value, keyptr);
    *value_eptr = hold;

    
    return value;
}

/// @brief Extracts a integer value from a json object.
/// @param json Json object where the value is stored.
/// @param key Json key to filter the integet to extract.
/// @return Extracted value as a int.
int intjson(const char* json, const char* key) {
    char* keyptr = strstr(json, key);

    if (keyptr == NULL) {
        err("Invalid key!");
        return 0;
    }

    while (*keyptr != ':')
        keyptr++;
    
    keyptr++;
    if (*keyptr == '\"')
        keyptr++;

    char* value_eptr = NULL;
    for (uint8_t it = 0; it < strlen(keyptr); it++) {
        if (*(keyptr + it) == '\"' || *(keyptr + it) == ',') {
            value_eptr = (keyptr + it);
            break;
        }
    }

    char hold = *value_eptr;
    *value_eptr = '\0';
    char* svalue = (char*)malloc(strlen(keyptr));
    strcpy(svalue, keyptr);
    *value_eptr = hold;

    int value = atoi(svalue);
    
    return value;
}

/// @brief Extracts a float value from a json object.
/// @param json Json object where the value is stored.
/// @param key Json key to filter the float value to extract.
/// @return Extracted value as float.
float floatjson(const char* json, const char* key) {
    char* keyptr = strstr(json, key);

    if (keyptr == NULL) {
        err("Invalid key!");
        return 0;
    }

    while (*keyptr != ':')
        keyptr++;
    
    keyptr++;
    if (*keyptr == '\"')
        keyptr++;

    char* value_eptr = NULL;
    for (uint8_t it = 0; it < strlen(keyptr); it++) {
        if (*(keyptr + it) == '\"' || *(keyptr + it) == ',') {
            value_eptr = (keyptr + it);
            break;
        }
    }

    char hold = *value_eptr;
    *value_eptr = '\0';
    char* svalue = (char*)malloc(strlen(keyptr));
    strcpy(svalue, keyptr);
    *value_eptr = hold;

    float value = atof(svalue);
    
    return value;
}
