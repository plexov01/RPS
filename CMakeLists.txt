cmake_minimum_required(VERSION 3.16)

project(RPS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Указываем, что это приложение с GUI, без консольного окна
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
# if(WIN32)
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
# endif()



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)


add_executable(RPS
    main.cpp

    client.h client.cpp

    server.h server.cpp

    game.h game.cpp

    applicationView.h applicationView.cpp applicationView.ui

    ipPortCoder.h ipPortCoder.cpp
    defaultnetworkconfiguration.h defaultnetworkconfiguration.cpp
    playermessage.h playermessage.cpp


    # gamewindow.h gamewindow.cpp gamewindow.ui

    # lobby.h lobby.cpp lobby.ui
)


# add_executable(RPS
#     main.cpp
#     game.cpp
#     game.h
#     client.cpp
#     client.h
#     server.cpp
#     server.h
# )


target_link_libraries(RPS Qt6::Core Qt6::Widgets Qt6::Network )

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

    add_custom_command(TARGET RPS POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Deploying Qt dependencies..."
        COMMAND ${WINDEPLOYQT_EXECUTABLE} --release $<TARGET_FILE:RPS>
        COMMENT "Running windeployqt to include dependencies"
        VERBATIM
    )
endif()
