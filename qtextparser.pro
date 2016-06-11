lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

CONFIG += c++11 debug_and_release
QT      = core xml

TEMPLATE=lib
DESTDIR = $$_PRO_FILE_PWD_/bin

CONFIG(release, debug|release) {
    TARGET = Qt5TextParser
} else {
    TARGET = Qt5TextParserd
}

VERSION = 0.5.0

include(src/qtextparser.pri)
