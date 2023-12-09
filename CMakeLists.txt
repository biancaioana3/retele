cmake_minimum_required(VERSION 3.23)
project(myftp_bi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )

add_executable(client
        client/main.cpp
        client/LoginWidget.cpp
        client/LoginWidget.h
        client/MainWindow.cpp client/MainWindow.h client/TreeWidget.cpp client/TreeWidget.h
        common/functions.h)

add_executable(server
        server/main.cpp
        server/util.h server/server.h server/Thread.cpp server/Thread.h)

target_link_libraries(server pthread)

target_link_libraries(client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

