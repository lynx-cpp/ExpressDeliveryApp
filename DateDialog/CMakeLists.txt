set(
    DateDialog_MOC_HDR
    DateDialog.h
)
qt4_wrap_cpp(
    DateDialog_MOC_SRC
    ${DateDialog_MOC_HDR}
)

add_library(
    DateDialog
    STATIC
    DateDialog.cpp
    ${DateDialog_MOC_SRC}
)

target_link_libraries(
    DateDialog
    ${QT_QTCORE_LIBRARY}
)