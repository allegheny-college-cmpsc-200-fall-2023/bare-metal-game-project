char *map_to_string(int width, int height, int** features) {
    cJSON *map = cJSON_CreateArray();
    for(int rows = 0; rows < height; rows++){
        cJSON *row = cJSON_CreateArray();
        for(int column = 0; column < width; column++) {
            cJSON *number = cJSON_CreateNumber(features[rows][column]);
            cJSON_AddItemToArray(row, number);
        }
        cJSON_AddItemToArray(map, row);
    }
    return cJSON_Print(map);
}
