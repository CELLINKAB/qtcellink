project(QtCellink.Plugins.GeometryLoaders.Amf)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core 3DCore 3DRender
)
find_package(assimp REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE H_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB QRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.qrc)

set(PROJECT_SOURCES
    ${SRC_FILES}
    ${H_FILES}
    ${QRC_FILES}
)

qt_add_resources(QtCellink.Plugins.GeometryLoaders.Amf amf.pro)

add_library(QtCellink.Plugins.GeometryLoaders.Amf SHARED ${PROJECT_SOURCES})

set_target_properties(QtCellink.Plugins.GeometryLoaders.Amf PROPERTIES
    OUTPUT_NAME "amfgeometryloader"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins/geometryloaders"
)

target_include_directories(QtCellink.Plugins.GeometryLoaders.Amf PRIVATE
    ${Qt${QT_VERSION_MAJOR}Core_PRIVATE_INCLUDE_DIRS}
    ${Qt${QT_VERSION_MAJOR}3DCore_PRIVATE_INCLUDE_DIRS}
    ${Qt${QT_VERSION_MAJOR}3DRender_PRIVATE_INCLUDE_DIRS}
)

target_link_libraries(QtCellink.Plugins.GeometryLoaders.Amf PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::3DCore
    Qt${QT_VERSION_MAJOR}::3DRender
    assimp::assimp
)

file(GLOB_RECURSE MISC_FILES LIST_DIRECTORIES OFF
    "${CMAKE_CURRENT_LIST_DIR}/*.md"
    "${CMAKE_CURRENT_LIST_DIR}/.*"
    "${CMAKE_CURRENT_LIST_DIR}/*.pro"
    "${CMAKE_CURRENT_LIST_DIR}/*.txt"
)

add_custom_target(QtCellink.Plugins.GeometryLoaders.Amf.misc SOURCES ${MISC_FILES})
