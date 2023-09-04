win32|macx {  #win32, macx
    QT       += core gui  widgets printsupport openglwidgets
    #LIBS     += -framework GLUT -framework OpenGL -framework Cocoa
    #LIBS     += -lopengl32
} else {
    QT       += core gui openglwidgets 
    #LIBS     += -lOpenGL -lGLU -lglut
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(gif/QtGifImage/src/gifimage/qtgifimage.pri)

SOURCES += \
    ../parser.c \
    ../s21_affine.c \
    ../s21_matrix/s21_matrix_functions/s21_calc_complements.c \
    ../s21_matrix/s21_matrix_functions/s21_check_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_create_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_del_row_and_column.c \
    ../s21_matrix/s21_matrix_functions/s21_determinant.c \
    ../s21_matrix/s21_matrix_functions/s21_eq_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_inverse_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_mult_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_mult_number.c \
    ../s21_matrix/s21_matrix_functions/s21_remove_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_sum_sub_matrix.c \
    ../s21_matrix/s21_matrix_functions/s21_transpose.c \
    main.cpp \
    mainwindow.cpp \
    qlwidget.cpp

HEADERS += \
    ../s21_matrix/s21_matrix.h \
    ../s21_viewer.h \
    mainwindow.h \
    qlwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
