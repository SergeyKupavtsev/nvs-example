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

wireless_parameters_s *test_wifi_params;

uint8_t test_value = 100;

esp_err_t read_test_wifi_params(wireless_parameters_s **test_wifi_params)
{
    esp_err_t ret = read_struct("test_wifi_params", test_wifi_params, sizeof(wireless_parameters_s));
    return ret;
}

esp_err_t write_test_wifi_params(wireless_parameters_s *test_wifi_params)
{
    esp_err_t ret = write_struct("test_wifi_params", test_wifi_params, sizeof(wireless_parameters_s));
    return ret;
}

esp_err_t write_value(uint8_t value)
{
    esp_err_t ret = nvs_write_u8("1_0_0", value);
    return ret;
}

esp_err_t read_value(uint8_t *value)
{
    esp_err_t ret = nvs_read_u8("1_0_0", value);
    return ret;
}

void print_wifi_struct()
{
    printf("wifi_sta.password = %s\n", test_wifi_params->wifi_sta.password);
    printf("wifi_sta.ssid =  %s\n", test_wifi_params->wifi_sta.ssid);
    printf("wifi_ap.password = %s\n", test_wifi_params->wifi_ap.password);
    printf("wifi_ap.ssid = %s\n", test_wifi_params->wifi_ap.ssid);
    printf("soft_ap_off_time = %i\n", test_wifi_params->soft_ap_off_time);
}
void app_main()
{
    // Initialization NVS storage
    // Always need
    esp_err_t ret = nvs_init();
    printf("NVS init ret = %i\n", ret);

    // ----------- Struct init --------------- //
    test_wifi_params = malloc(sizeof(wireless_parameters_s));
    test_wifi_params->soft_ap_off_time = 10;
    strcpy(test_wifi_params->wifi_sta.password, "sta password");
    strcpy(test_wifi_params->wifi_sta.ssid, "StaSsid");
    strcpy(test_wifi_params->wifi_ap.password, "ap_password");
    strcpy(test_wifi_params->wifi_ap.ssid, "ApSsid");

    // ----------- Write struct --------------- //
    printf("Write struct :\n");
    print_wifi_struct();
    write_test_wifi_params(test_wifi_params);
    // ----------- Read struct --------------- //
    printf("Read struct :\n");
    read_test_wifi_params(&test_wifi_params);
    print_wifi_struct();

    // ----------- Write uint8_t value --------------- //
    printf("Write uint8_t value = %i\n", test_value);
    write_value(test_value);

    // ----------- Read uint8_t value  --------------- //
    read_value(&test_value);
    printf("Read uint8_t value = %i\n", test_value);
    // -------------------------------------- //
}