#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers/cache.h"
#include "headers/timing.h"
#include "headers/cJSON.h"
#include "headers/heap.h"
#include "pico/stdlib.h"

// MIGHTDO: Create a struct per the README to store map data

// DO NOT DELETE: Create call to external function to make HTTPS request
extern char* https_request();

// TODO: Parse JSON values using a function

void print_map(/* TODO: Pass map structure */) {
    // HINT: Set up symbols array to construct map
    char *symbols[] = {".", "#"};
    // Iterate in row-major order to construct map grid
    for (int row = 0; row < /* TODO: Structure rows */; row++){
        // Iterate over column to complete row
        for(int column = 0; column < /* TODO: Structure columns */; column++){
            printf("%s", /* TODO: Relevant map feature tile */);
        }
        // Print new line
        printf("\n");
    }
}

int dist_topology(int topology_pct) {
    // Determine if toplogy should be placed in base map
    if(topology_pct >= rand() % 100) {
        return 1;
    }
    // Default: natural ground
    return 0;
}

// TODO: Calculate adjacency for toplogical map creation

// TODO: Test base map for toplogical rules

// MIGHTDO: Write a function governing toplogical map creation

// TODO: Write function to create base map

int main(void) {
    stdio_init_all();

    while(true) {

        // TODO: Make HTTPS request to game server

        /*
            TODO: Parse response as a cJSON object. For more information,
                  see: https://github.com/DaveGamble/cJSON
        */

        // TODO: Parse cJSON object to obtain individual values

        // TODO: Create base map to generate topography

        // TODO: Generate rule-based topography from base map

        // TODO: Print map for debug

        /* 
            TODO: Sleep between generations for debug?
        */

        sleep_ms(1000);
        
    }
    return 0;
}
