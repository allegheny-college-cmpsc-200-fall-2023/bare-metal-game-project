/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "headers/cJSON.h"

// Using this url as we know the root cert won't change for a long time
#define TLS_CLIENT_SERVER "metal.cmpsc200.chompe.rs"
#define TLS_CLIENT_HTTP_REQUEST  "GET / HTTP/1.1\r\n" \
                                 "Host: " TLS_CLIENT_SERVER "\r\n" \
                                 "Connection: close\r\n" \
                                 "\r\n"
#define TLS_CLIENT_TIMEOUT_SECS  15

// This is the PUBLIC root certificate exported from a browser
// Note that the newlines are needed
#define TLS_ROOT_CERT_OK "-----BEGIN CERTIFICATE-----\n\
MIIC+jCCAn+gAwIBAgICEAAwCgYIKoZIzj0EAwIwgbcxCzAJBgNVBAYTAkdCMRAw\n\
DgYDVQQIDAdFbmdsYW5kMRIwEAYDVQQHDAlDYW1icmlkZ2UxHTAbBgNVBAoMFFJh\n\
c3BiZXJyeSBQSSBMaW1pdGVkMRwwGgYDVQQLDBNSYXNwYmVycnkgUEkgRUNDIENB\n\
MR0wGwYDVQQDDBRSYXNwYmVycnkgUEkgUm9vdCBDQTEmMCQGCSqGSIb3DQEJARYX\n\
c3VwcG9ydEByYXNwYmVycnlwaS5jb20wIBcNMjExMjA5MTEzMjU1WhgPMjA3MTEx\n\
MjcxMTMyNTVaMIGrMQswCQYDVQQGEwJHQjEQMA4GA1UECAwHRW5nbGFuZDEdMBsG\n\
A1UECgwUUmFzcGJlcnJ5IFBJIExpbWl0ZWQxHDAaBgNVBAsME1Jhc3BiZXJyeSBQ\n\
SSBFQ0MgQ0ExJTAjBgNVBAMMHFJhc3BiZXJyeSBQSSBJbnRlcm1lZGlhdGUgQ0Ex\n\
JjAkBgkqhkiG9w0BCQEWF3N1cHBvcnRAcmFzcGJlcnJ5cGkuY29tMHYwEAYHKoZI\n\
zj0CAQYFK4EEACIDYgAEcN9K6Cpv+od3w6yKOnec4EbyHCBzF+X2ldjorc0b2Pq0\n\
N+ZvyFHkhFZSgk2qvemsVEWIoPz+K4JSCpgPstz1fEV6WzgjYKfYI71ghELl5TeC\n\
byoPY+ee3VZwF1PTy0cco2YwZDAdBgNVHQ4EFgQUJ6YzIqFh4rhQEbmCnEbWmHEo\n\
XAUwHwYDVR0jBBgwFoAUIIAVCSiDPXut23NK39LGIyAA7NAwEgYDVR0TAQH/BAgw\n\
BgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwCgYIKoZIzj0EAwIDaQAwZgIxAJYM+wIM\n\
PC3wSPqJ1byJKA6D+ZyjKR1aORbiDQVEpDNWRKiQ5QapLg8wbcED0MrRKQIxAKUT\n\
v8TJkb/8jC/oBVTmczKlPMkciN+uiaZSXahgYKyYhvKTatCTZb+geSIhc0w/2w==\n\
-----END CERTIFICATE-----\n"

extern char *client_connect(const char *cert, size_t cert_len, const char *server, const char *request, int timeout);

char *https_request() {

    const char cert_ok[] = TLS_ROOT_CERT_OK;
    char *response = client_connect(
        cert_ok, 
        sizeof(cert_ok), 
        TLS_CLIENT_SERVER, 
        TLS_CLIENT_HTTP_REQUEST, 
        TLS_CLIENT_TIMEOUT_SECS
    );

    /* sleep a bit to let usb stdio write out any buffer to host */
    sleep_ms(100);
    return response;
    
}

char *upload_map(char *user, char *test, int pct) {
    cJSON *post_data = cJSON_CreateObject();

    cJSON_AddItemToObject(post_data, "user", cJSON_CreateString(user));
    cJSON_AddItemToObject(post_data, "map", cJSON_CreateString(test));
    cJSON_AddItemToObject(post_data, "pct", cJSON_CreateNumber((double)pct));

    char *post_data_string = cJSON_Print(post_data);
    int size_of_data = strlen(post_data_string);
    char size_of_data_string[100];
    sprintf(
        size_of_data_string,
        "%d",
        size_of_data
    );
    char upload_request[150 + size_of_data];
    strcpy(upload_request, "POST / HTTP/1.1\r\n");
    strcat(upload_request, "Host: " TLS_CLIENT_SERVER "\r\n");
    strcat(upload_request, "Connection: close\r\n");
    strcat(upload_request, "Content-Type: application/json\r\n");
    strcat(upload_request, "Content-Length: ");
    strcat(upload_request, size_of_data_string);
    strcat(upload_request, "\r\n\r\n");
    strcat(upload_request, post_data_string);

    const char cert_ok[] = TLS_ROOT_CERT_OK;

    char *response = client_connect(
        cert_ok, 
        sizeof(cert_ok), 
        TLS_CLIENT_SERVER, 
        upload_request, 
        TLS_CLIENT_TIMEOUT_SECS
    );

    sleep_ms(100);
    return response;
}
