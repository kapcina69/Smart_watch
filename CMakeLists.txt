# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(accelerometer_chart)

include_directories(
    include
)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE
    src/bluetooth/ble_hrs.c
    src/bluetooth/ble_nus.c
    src/bluetooth/ble_service.c
)
target_sources(app PRIVATE
    src/sensors/bmi160.c
    src/sensors/max30101.c
)
target_sources(app PRIVATE
    # src/images/background.c
    src/images/heart.c
    src/images/background1.c
    src/images/steps_img.c
    src/images/bluetooth.c
    src/images/watchface1bg.c
    src/images/shoesw1.c
    src/images/cardiogram.c
    src/images/bluetooth1.c
    src/battery_monitor.c
)
target_sources(app PRIVATE
    src/watchdog.c
)