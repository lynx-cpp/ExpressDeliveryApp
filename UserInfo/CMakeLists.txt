include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
set(
    UserInfo_MOC_HDRS
    UserInfo.h
)
qt4_wrap_cpp(
    UserInfo_MOC_SRCS
    ${UserInfo_MOC_HDRS}
)

add_library(
    UserInfo
    STATIC
    UserInfo.cpp
    ${UserInfo_MOC_SRCS}
)

target_link_libraries(
    UserInfo
    ${QT_QTCORE_LIBRARY}
)