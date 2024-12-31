SET(MAIN_NAME Main)

# Set directory paths.
set(CORE_PATH ${PROJECT_ROOT}/Core)
set(FRAMEWORK_PATH ${PROJECT_ROOT}/Framework)
set(STB_IMAGE_INCLUDE ${PROJECT_ROOT}/stb_image)

set(CORE_LIB_NAME android/${CMAKE_ANDROID_ARCH_ABI}/libLive2DCubismCore.a)

# Specify version of compiler.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---Configure Framework---
# Specify Cubism Framework rendering.
set(FRAMEWORK_SOURCE OpenGL)
# Add Cubism Native Framework.
add_subdirectory(${FRAMEWORK_PATH} ${CMAKE_BINARY_DIR}/Framework)
target_include_directories(Framework PRIVATE src)
# Add rendering definition to framework.
target_compile_definitions(Framework PUBLIC CSM_TARGET_ANDROID_ES2)
# Link libraries to framework.
add_library(Live2DCubismCore STATIC IMPORTED)

# ---CubismCoreLib---
# Import CubismCoreLib
set_target_properties(Live2DCubismCore
  PROPERTIES
    IMPORTED_LOCATION
      ${CORE_PATH}/lib/${CORE_LIB_NAME}
    INTERFACE_INCLUDE_DIRECTORIES
      ${CORE_PATH}/include
)
target_compile_definitions(Live2DCubismCore
  INTERFACE
  ${CSM_TARGET}
)

target_link_libraries(Framework Live2DCubismCore GLESv2)

# Add source files.
add_subdirectory(src)

# Link libraries to app.
target_link_libraries(${MAIN_NAME}
  Framework
)

# Specify include directories.
target_include_directories(${MAIN_NAME} PUBLIC 
  ${STB_IMAGE_INCLUDE}
        src
)

# 设置要插入的代码
set(INSERT_INCLUDE "#include <HackProperties.h>\n")
set(INSERT_ADDITIONAL_PROPERTIES "    __ADDITIONAL_PROPERTIES__\n")

# 源文件路径
set(SOURCE_HPP ${CMAKE_CURRENT_SOURCE_DIR}/../Framework/src/Motion/ACubismMotion.hpp)
# 备份文件路径
set(BACKUP_HPP ${SOURCE_HPP}.bak)

# 在配置阶段立即执行文件修改脚本
if(NOT EXISTS "${BACKUP_HPP}")
    include(${CMAKE_CURRENT_SOURCE_DIR}/insert_code.cmake)
endif()

# 在配置阶段立即执行文件修改脚本
include(${CMAKE_CURRENT_SOURCE_DIR}/insert_code.cmake)

