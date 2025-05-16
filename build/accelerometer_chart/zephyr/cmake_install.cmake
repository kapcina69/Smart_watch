# Install script for directory: /home/luka/ncs/v2.9.1/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "MinSizeRel")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/luka/ncs/toolchains/b77d8c1312/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/suit-processor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/luka/ncs/v2.9.1/zephyr/samples/modules/lvgl/accelerometer_chart/build/accelerometer_chart/zephyr/cmake/reports/cmake_install.cmake")
endif()

