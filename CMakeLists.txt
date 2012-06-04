project(ExpressDeliveryApp)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Qt4 COMPONENTS QtCore QtGui QtSQL REQUIRED)
find_package(Qwt REQUIRED)

add_subdirectory(UserInfo)
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(ExpressDeliveryApp_SRCS ExpressDeliveryApp.cpp main.cpp)
qt4_wrap_cpp(
    ExpressDeliveryApp_MOC_SRCS
    ExpressDeliveryApp.h
    UserInfo/UserInfo.h
    DateDialog/DateDialog.h
    HistogramItem/HistogramItem.h
)
qt4_automoc(${ExpressDeliveryApp_SRCS})
qt4_wrap_ui(
    ExpressDeliveryApp_UI_SRCS
    main.ui
)
#link_directories(/usr/lib/qt/plugins/sqldrivers/)
add_executable(ExpressDeliveryApp ${ExpressDeliveryApp_SRCS} ${ExpressDeliveryApp_UI_SRCS} UserInfo/UserInfo.cpp md5/md5.cpp DateDialog/DateDialog.cpp HistogramItem/HistogramItem.cpp)
target_link_libraries(ExpressDeliveryApp ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSQL_LIBRARY} ${QWT_LIBRARIES} UserInfo md5 DateDialog HistogramItem)
add_subdirectory(md5)
add_subdirectory(DateDialog)
add_subdirectory(HistogramItem)