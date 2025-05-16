#ifndef GPS_H_
#define GPS_H_
#include <stdint.h>

// Function prototypes
void GPS_Init(void);
double to_decimal_lon(double lon_ddmm);
double to_decimal_lat(double lat_ddmm);
void float_to_str(float num, char* buffer, int precision);
float toFloat(char *c, int size);
void GPS_ParseSentence(const char *sentence);
void Location_Getter(char longitiude[], char latitiude[]);
void double_to_string(double value, char *str, int precision);
void double_to_string(double value, char *str, int precision);
//void lat_log(double *lat,double *log);
void convertToDMS(char *decimalStr, char *degStr, char *minStr, char *secStr);
double haversine(double lat1, double lon1, double lat2, double lon2) ;

// GPS Data Structure
typedef struct {
    double latitude;       // Latitude in decimal degrees
    double longitude;      // Longitude in decimal degrees
    double speed_knots;    // Speed in knots
    double course;         // Course over ground in degrees
    int fix_status;        // Fix status ('A' = Active, 'V' = Void)
} GPS_Data_t;

extern GPS_Data_t gps_data;

#endif /* GPS_H_ */
