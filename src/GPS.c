#include "defines.h"

//Convert a string representation of a number to a float
 
float toFloat(char *c, int size) {
    float result = 0;
    float decimal;
    float multiplier;
    int i, dot_index = -1;

    // Find decimal point position
    for (i = 0; i < size && c[i]; i++) {
        if (c[i] == '.') {
            dot_index = i;
            break;
        }
    }

    // If no decimal point, use standard conversion
    if (dot_index == -1) return atof(c);

    // Process digits before decimal point
    for (i = 0; i < dot_index; i++) {
        result = result * 10 + (c[i] - '0');
    }

    // Process digits after decimal point
    decimal = 0.0;
    multiplier = 0.1;

    for (i = dot_index + 1; i < size && c[i]; i++) {
        decimal += (c[i] - '0') * multiplier;
        multiplier *= 0.1;
    }

    return result + decimal;
}

/*
 convert NMEA latitude format (ddmm.mmmm) to decimal degrees
 lat_ddmm Latitude in NMEA format
 return double Latitude in decimal degrees
 */
double to_decimal_lat(double lat_ddmm) {
    int degrees = (int)(lat_ddmm) / 100;
    double minutes = lat_ddmm - (degrees * 100);
    return degrees + (minutes / 60.0);
}

/*
 Convert NMEA longitude format (dddmm.mmmm) to decimal degrees 
 lon_ddmm Longitude in NMEA format
 return double Longitude in decimal degrees
 */
double to_decimal_lon(double lon_ddmm) {
    int degrees = (int)(lon_ddmm) / 100;
    double minutes = lon_ddmm - (degrees * 100);
    return degrees + (minutes / 60.0);
}

//Calculate the distance between two coordinates using the Haversine formula

double haversine(double lat1, double lon1, double lat2, double lon2) {
    // Convert degrees to radians
    double phi1 = lat1 * PI / 180.0;
    double phi2 = lat2 * PI / 180.0;
    double delta_phi = (lat2 - lat1) * PI / 180.0;
    double delta_lambda = (lon2 - lon1) * PI / 180.0;

    // Calculate haversine formula
    double a = sin(delta_phi / 2) * sin(delta_phi / 2) +
               cos(phi1) * cos(phi2) *
               sin(delta_lambda / 2) * sin(delta_lambda / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    // Return distance
    return EARTH_RADIUS * c;
}

// @brief Convert a float to a string representation

void float_to_str(float num, char* buffer, int precision) {
    int integer = (int)num;
    float fraction = num - integer;
    int p;
    int k;
    int digit;
    int i = 0;

    // Convert integer part
    if (integer == 0) {
        buffer[i++] = '0';
    } else {
        char temp[10];
        int j = 0;
        while (integer > 0) {
            temp[j++] = (integer % 10) + '0';
            integer /= 10;
        }
        for (k = j - 1; k >= 0; k--) {
            buffer[i++] = temp[k];
        }
    }

    // Add decimal point
    buffer[i++] = '.';

    // Convert fractional part to specified precision
    for (p = 0; p < precision; p++) {
        fraction *= 10;
        digit = (int)fraction;
        buffer[i++] = digit + '0';
        fraction -= digit;
    }

    buffer[i] = '\0';
}

//Get the current GPS coordinates
 
void Location_Getter(char *longitude, char *latitude) {
    char buffer[100];
    int i = 0;

    // Read from UART until a valid GPRMC sentence is found
    while (1) {
        char c = UART5_Read();
        if (c == '$') {
            buffer[0] = c;
            i = 1;
            // Read the entire sentence
            while (i < 99) {
                c = UART5_Read();
                buffer[i++] = c;
                if (c == '\n') break;
            }
            buffer[i] = '\0';

            // Check if this is a GPRMC sentence
            if (strncmp(buffer + 1, "GPRMC", 5) == 0) {
                char *token;
                int field = 0;
                token = strtok(buffer, ",");

                // Parse the comma-separated fields
                while (token != NULL) {
                    field++;
                    if (field == 4)          // Field 4 contains latitude
                        strcpy(latitude, token);
                    else if (field == 6)     // Field 6 contains longitude
                        strcpy(longitude, token);
                    token = strtok(NULL, ",");
                }
                break;
            }
        }
    }
}
