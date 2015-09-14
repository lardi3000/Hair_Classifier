TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    db_utils.hpp \
    functions.hpp \
    main.hpp \
    myFeatures.h

SOURCES += \
    db_utils.cpp \
    functions.cpp \
    main.cpp \
    myFeatures.cpp

#INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann

#INCLUDEPATH+=/usr/include/mysql
#LIBS += -L/usr/include/
LIBS += -lmysqlclient
