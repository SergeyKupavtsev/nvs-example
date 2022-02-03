#include "nvs_component.h"

#include "string.h"
typedef struct
{
    char ssid[50];
    char password[20];
} wifi_parameters_s;

// Struct for example, can be any
typedef struct
{
    wifi_parameters_s wifi_sta;
    wifi_parameters_s wifi_ap;
    uint8_t soft_ap_off_time;
} wireless_parameters_s;

esp_err_t read_wifi_params(wireless_parameters_s **wireless_params)
{
    esp_err_t ret = read_struct("wifi_params", wireless_params, sizeof(wireless_parameters_s));
    return ret;
}

esp_err_t write_wifi_params(wireless_parameters_s *wireless_params)
{
    esp_err_t ret = write_struct("wifi_params", wireless_params, sizeof(wireless_parameters_s));
    return ret;
}
wireless_parameters_s *wifi_params;
void print_wifi_struct()
{
    printf("wifi_sta.password = %s\n", wifi_params->wifi_sta.password);
    printf("wifi_sta.ssid =  %s\n", wifi_params->wifi_sta.ssid);
    printf("wifi_ap.password = %s\n", wifi_params->wifi_ap.password);
    printf("wifi_ap.ssid = %s\n", wifi_params->wifi_ap.ssid);
    printf("soft_ap_off_time = %i\n", wifi_params->soft_ap_off_time);
}
void app_main()
{
    // Initialization NVS storage
    // Always need
    esp_err_t ret = nvs_init();
    printf("NVS init ret = %i\n", ret);

    wifi_params = malloc(sizeof(wireless_parameters_s));

    wifi_params->soft_ap_off_time = 10,
    strcpy(wifi_params->wifi_sta.password, "sta password");
    strcpy(wifi_params->wifi_sta.ssid, "StaSsid");
    strcpy(wifi_params->wifi_ap.password, "ap_password");
    strcpy(wifi_params->wifi_ap.ssid, "ApSsid");

    printf("Write struct :\n");

    print_wifi_struct();

    write_wifi_params(&wifi_params);

    printf("Read struct :\n");
    read_wifi_params((&wifi_params));
    print_wifi_struct();
}