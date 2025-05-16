#include "defines.h"
// Location structure
typedef struct {
    char *name;
    double lat;
    double lon;
} Location;

// Find the nearest location and return its index
int find_nearest_location(double my_lat, double my_lon, const Location *locations, int num_locations) {
    double min_distance = 1e9;
    int nearest_index = -1;
		int i;
    for (i = 0; i < num_locations; i++) {
        double distance = haversine(my_lat, my_lon, locations[i].lat, locations[i].lon);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_index = i;
        }
    }

    return nearest_index;
}

// Predefined locations
Location locations[] = {
    {"Hall A",        30.064176, 31.280445},
    {"Hall C",        30.063880, 31.280430},
    {"Library",       30.065141, 31.279957},
    {"Credit Building", 30.063669, 31.278422},
    {"Luban",         30.063354, 31.279386}
};


int main(void) {
    

    
	float lat_ddmm, lon_ddmm;
    double lat, lon;
    char latStr[15], lonStr[15];
    int nearest_idx, prev_nearest_idx = -1;
    int num_locations = sizeof(locations) / sizeof(locations[0]);
				
		UART5_Init();
    LCD_Init();
    PortF_Init();
    PortD_Buzzer_Init();
	while(1){
	Location_Getter(lonStr, latStr);  // Get raw GPS values

        lat_ddmm = toFloat(latStr, 12);
        lon_ddmm = toFloat(lonStr, 12);

        lat = to_decimal_lat(lat_ddmm);
        lon = to_decimal_lon(lon_ddmm);
	
        float_to_str(lat, latStr, 6);
        float_to_str(lon, lonStr, 6);

        LCD_Clear();
        LCD_GotoLine(0);
        LCD_String("Lat:");
        LCD_String(latStr);
        LCD_GotoLine(1);
        LCD_String("Lon:");
        LCD_String(lonStr);
				Sys_Tick(10);

        nearest_idx = find_nearest_location(lat, lon, locations, num_locations);

        if (nearest_idx != prev_nearest_idx) {
            Buzzer_Ring();
            prev_nearest_idx = nearest_idx;
        }

        LCD_Clear();
        LCD_GotoLine(0);
        LCD_String("Nearest:");
        LCD_GotoLine(1);
        LCD_String(locations[nearest_idx].name);
        Sys_Tick(10);
		
			}
 
}
