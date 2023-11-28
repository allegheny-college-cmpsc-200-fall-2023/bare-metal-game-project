cmake_minimum_required(VERSION 3.18)
include($ENV{PICO_SDK_PATH}\\external\\pico_sdk_import.cmake)

project(program C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}
    headers
    network
    data    
)

add_executable(${PROJECT_NAME}
  network/tls_common.c
  network/tls_verify.c
  data/cJSON.c
  main.c
)

set(PICO_BOARD pico_w)

pico_sdk_init()

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_mbedtls
    pico_lwip_mbedtls
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
)

pico_add_extra_outputs(${PROJECT_NAME})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

set_source_files_properties(
    ${PICO_LWIP_PATH}/src/apps/altcp_tls/altcp_tls_mbedtls.c
    PROPERTIES
    COMPILE_OPTIONS "-Wno-unused-result"
)

include(network\\network_credentials.cmake)