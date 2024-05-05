cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(Computational_Mathematics LANGUAGES CXX)

include(GNUInstallDirs)
set(PACKAGE_NAME matplotlib_cpp)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/${PACKAGE_NAME}/cmake)


# Library target
add_library(matplotlib_cpp INTERFACE
        lab4/Realisation.cpp
        lab4/LinearApproximation.h
        lab4/ChooseApproximationFunction.h
        lab4/QuadraticApproximation.h
)
target_include_directories(matplotlib_cpp
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/examples>
        $<INSTALL_INTERFACE:include>
)
target_compile_features(matplotlib_cpp INTERFACE
        cxx_std_11
)
# TODO: Use `Development.Embed` component when requiring cmake >= 3.18
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(matplotlib_cpp INTERFACE
        Python3::Python
        Python3::Module
)
find_package(Python3 COMPONENTS NumPy)
if (Python3_NumPy_FOUND)
    target_link_libraries(matplotlib_cpp INTERFACE
            Python3::NumPy
    )
else ()
    target_compile_definitions(matplotlib_cpp INTERFACE WITHOUT_NUMPY)
endif ()
install(
        TARGETS matplotlib_cpp
        EXPORT install_targets
)


# Examples
add_executable(Computational_Mathematics
        lab4/Realisation.cpp
        lab4/LinearApproximation.h
        lab4/ChooseApproximationFunction.h
        lab4/QuadraticApproximation.h
)
target_link_libraries(Computational_Mathematics PRIVATE matplotlib_cpp)
set_target_properties(Computational_Mathematics PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


if (Python3_NumPy_FOUND)
    add_executable(Computational_Mathematic
            lab4/Realisation.cpp
            lab4/LinearApproximation.h
            lab4/ChooseApproximationFunction.h
            lab4/QuadraticApproximation.h
    )
    target_link_libraries(Computational_Mathematic PRIVATE matplotlib_cpp)
    set_target_properties(Computational_Mathematic PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif ()


# Install headers
install(FILES
        "lab5/matplotlibcpp.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# Install targets file
install(EXPORT install_targets
        FILE
        ${PACKAGE_NAME}Targets.cmake
        NAMESPACE
        ${PACKAGE_NAME}::
        DESTINATION
        ${INSTALL_CONFIGDIR}
)


# Install matplotlib_cppConfig.cmake
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PACKAGE_NAME}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)