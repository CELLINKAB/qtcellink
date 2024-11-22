project(QtCellink.Plugins.GeometryLoaders.Amf)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core 3DCore 3DRender
)
find_package(assimp REQUIRED)

add_library(QtCellink.Plugins.GeometryLoaders.Amf SHARED ${PROJECT_SOURCES})

set_target_properties(QtCellink.Plugins.GeometryLoaders.Amf PROPERTIES
    OUTPUT_NAME "amfgeometryloader"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins/geometryloaders"
)

target_link_libraries(QtCellink.Plugins.GeometryLoaders.Amf PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::3DCore
    Qt${QT_VERSION_MAJOR}::3DRender
    Qt${QT_VERSION_MAJOR}::CorePrivate
    Qt${QT_VERSION_MAJOR}::3DCorePrivate
    Qt${QT_VERSION_MAJOR}::3DRenderPrivate
    assimp::assimp
)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB H_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB MISC_FILES LIST_DIRECTORIES OFF
    ${CMAKE_CURRENT_LIST_DIR}/*.md
    ${CMAKE_CURRENT_LIST_DIR}/.*
    ${CMAKE_CURRENT_LIST_DIR}/*.pro
    ${CMAKE_CURRENT_LIST_DIR}/*.txt
)

target_sources(QtCellink.Plugins.GeometryLoaders.Amf PRIVATE
    ${SRC_FILES}
    ${H_FILES}
    amf.json
    ${MISC_FILES}
)
