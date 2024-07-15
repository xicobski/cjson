#ifndef __JSONIFY_H__
#define __JSONIFY_H__

char* jsonfread(const char* filename);
char* getjson(const char* json, const char* key);
char* strjson(const char* json, const char* key);
int   intjson(const char* json, const char* key);
float floatjson(const char* json, const char* key);

#endif