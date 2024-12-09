cmake_minimum_required(VERSION 3.0.0)
project("tianmouc_af_project")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_EXE_LINKER_FLAGS "-L./tmp_lib")
set(LDLIBS -fPIC -pthread -lslabhidtosmbus -lslabhiddevice -lusb-1.0 -ludev)

set(inc1 ${SDK_PATH}/usb/inc)
set(inc2 ${SDK_PATH}/usb/cyusb/lib)
set(inc3 ${SDK_PATH}/usb/api)
set(inc4 ${SDK_PATH}/inc)
set(linkpath ${SDK_PATH}/usb/api)

message(${inc1})
message(${inc2})
message(${inc3})

link_directories(${linkpath})
    
include_directories(${inc1})
include_directories(${inc2})
include_directories(${inc3})
include_directories(${inc4})
add_compile_definitions(USB_SDK)
set(file1 tianmoucv.cpp)
set(file2 ${SDK_PATH}/src/tmc_proc.cpp)
set(file3 ${SDK_PATH}/usb/src/new_dataRecevier.cpp)
set(file4 ${SDK_PATH}/usb/src/camera.cpp)
set(file5 ${SDK_PATH}/usb/src/lyn_cam.cpp)
set(file6 ${SDK_PATH}/usb/src/tools.cpp)
set(file7 ${SDK_PATH}/src/isp.cpp)

include_directories(./inc)
include_directories(./lens_sdk/include)
set(SRC_PATH ./src)
set(file8 ${SRC_PATH}/UsbCtrl.c)
set(file9 ${SRC_PATH}/LensAccess.c)
set(file10 ${SRC_PATH}/LensSetup.c)
set(file11 ${SRC_PATH}/LensInfo.c)
set(file12 ${SRC_PATH}/LensConnect.c)
set(file13 ${SRC_PATH}/LensCtrl.c)
    

include_directories("/usr/local/include/opencv4")
find_package(OpenCV 4 REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "Found OpenCV version: ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV version 4.5.0 or higher is required.")
endif()

add_executable(tianmoucv_app ${file1} ${file2} ${file3} ${file4} ${file5} ${file6} ${file7} ${file8} ${file9} ${file10} ${file11} ${file12} ${file13})
target_compile_options(tianmoucv_app PRIVATE ${CMAKE_CXX_FLAGS})
target_link_libraries(tianmoucv_app PRIVATE ${OpenCV_LIBS} ${LDLIBS} cyusb)

