#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CONFIG_FILE "/etc/pjson.json"

// pjson version 1.0.0 - devel
// wtitten by AntiSecTech <contact.antisec@pm.me>

void print_usage() {
    printf("Usage: pjson <file.json> [<key>]\n");
}

void print_help() {
    printf("pjson - a simple JSON Parser\n\n");
    printf("Usage:\n");
    printf("  pjson <file.json> [<key>]\n");
    printf("  pjson -v | --version\n");
    printf("  pjson -h | --help\n\n");
    printf("Options:\n");
    printf("  -h, --help       Show this help message\n");
    printf("  -v               Show version number\n");
    printf("  --version        Show detailed version information\n");
}

void print_value(json_t *root, const char *key) {
    json_t *value = root;
    char *token = strtok(strdup(key), ".");

    while (token && json_is_object(value)) {
        value = json_object_get(value, token);
        token = strtok(NULL, ".");
    }

    if (json_is_string(value)) {
        printf("%s\n", json_string_value(value));
    } else {
        printf("Key not found or not a string.\n");
    }
}

void print_file_contents(const char *filename, const char *scheme) {
    char command[256];
    snprintf(command, sizeof(command), "pygmentize -l json -f terminal256 -O style=%s %s | less -R", scheme, filename);
    system(command);
}

void print_version() {
    json_error_t error;
    json_t *root = json_load_file(CONFIG_FILE, 0, &error);
    if (!root) {
        fprintf(stderr, "Error parsing JSON file: %s\n", error.text);
        return;
    }

    json_t *release = json_object_get(root, "Release");
    if (json_is_object(release)) {
        json_t *version = json_object_get(release, "Version");
        if (json_is_string(version)) {
            printf("%s\n", json_string_value(version));
        }
    }

    json_decref(root);
}

void print_detailed_version() {
    json_error_t error;
    json_t *root = json_load_file(CONFIG_FILE, 0, &error);
    if (!root) {
        fprintf(stderr, "Error parsing JSON file: %s\n", error.text);
        return;
    }

    json_t *program = json_object_get(root, "Program");
    if (json_is_object(program)) {
    	json_t *name = json_object_get(program, "name");

    	if (json_is_string(name)) {
    		printf("%s ", json_string_value(name));
    	}
    }
    
    json_t *release = json_object_get(root, "Release");
    if (json_is_object(release)) {

        json_t *version = json_object_get(release, "Version");
        json_t *release_type = json_object_get(release, "Release");
        
        if (json_is_string(version)) {
            printf("version %s", json_string_value(version));
        }
        if (json_is_string(release_type)) {
            printf(" - %s\n", json_string_value(release_type));
        }
    }

    json_decref(root);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    if (strcmp(argv[1], "-v") == 0) {
        print_version();
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        print_detailed_version();
        return 0;
    }

    const char *filename = argv[1];
    const char *key = argc > 2 ? argv[2] : NULL;

    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        fprintf(stderr, "Error: File %s not found.\n", filename);
        return 1;
    }

    json_error_t error;
    json_t *root = json_load_file(CONFIG_FILE, 0, &error);
    if (!root) {
        fprintf(stderr, "Error parsing config JSON file: %s\n", error.text);
        return 1;
    }

    json_t *config = json_object_get(root, "Config");
    const char *scheme = "monokai";
    if (json_is_object(config)) {
        json_t *scheme_json = json_object_get(config, "scheme");
        if (json_is_string(scheme_json)) {
            scheme = json_string_value(scheme_json);
        }
    }

    if (key) {
        json_t *json_root = json_load_file(filename, 0, &error);
        if (!json_root) {
            fprintf(stderr, "Error parsing JSON file: %s\n", error.text);
            json_decref(root);
            return 1;
        }

        print_value(json_root, key);
        json_decref(json_root);
    } else {
        print_file_contents(filename, scheme);
    }

    json_decref(root);
    return 0;
}
