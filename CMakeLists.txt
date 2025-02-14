cmake_minimum_required(VERSION 3.16)

project(RPS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)

# Источники для сервера
set(SERVER_SOURCES
    server.cpp
    server.h
    main_server.cpp
)

# Источники для клиента
set(CLIENT_SOURCES
    client.cpp
    client.h
    main_client.cpp
)

# Создание исполняемого файла для сервера
add_executable(ServerApp ${SERVER_SOURCES})
target_link_libraries(ServerApp PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

# Создание исполняемого файла для клиента
add_executable(ClientApp ${CLIENT_SOURCES})
target_link_libraries(ClientApp PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

# Установка исполняемых файлов (если нужно)
install(TARGETS ServerApp ClientApp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
