cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "-std=c++11")

project(
    locata
)

add_library(wifi-scan SHARED wifi_scan.c)
target_link_libraries(wifi-scan mnl)
set_target_properties (wifi-scan  PROPERTIES VERSION 1.0 SOVERSION 1)

install(TARGETS wifi-scan DESTINATION lib)
install(FILES wifi_scan.h DESTINATION include)

add_executable(locata log.cpp  main.cpp  mqtt_driver.cpp  publisher.cpp  wlan_provider.cpp location.cpp utils.cpp config.cpp data_logger.cpp)
target_link_libraries(locata wifi-scan pthread paho-mqtt3c mnl)

install(TARGETS locata DESTINATION bin)
install(FILES locata.conf DESTINATION etc)
