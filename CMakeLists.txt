project(ExpressDeviveryApp)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Qt4 COMPONENTS QtCore QtGui QtSQL REQUIRED)

add_subdirectory(RegisterApp)
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ExpressDeviveryApp_SRCS ExpressDeviveryApp.cpp main.cpp)
qt4_automoc(${ExpressDeviveryApp_SRCS})
qt4_wrap_ui(
    ExpressDeviveryApp_UI_SRCS
    main.ui
)
#link_directories(/usr/lib/qt/plugins/sqldrivers/)
add_executable(ExpressDeviveryApp ${ExpressDeviveryApp_SRCS} ${ExpressDeviveryApp_UI_SRCS} ${RegisterApp_MOC_SRCS} RegisterApp/RegisterApp.cpp)
#target_link_libraries(ExpressDeviveryApp ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} libqsqlmysql.so /usr/lib/libQtSql.so.4)
#target_link_libraries(ExpressDeviveryApp ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} /usr/lib/libQtSql.so.4)
target_link_libraries(ExpressDeviveryApp ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSQL_LIBRARY})