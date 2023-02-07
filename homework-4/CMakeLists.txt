cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "4" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.1.${PATCH_VERSION})

project(printip VERSION ${PROJECT_VESRION})

message("Start making targets")

# targets
add_executable(printip_cli printip.cpp)

set_target_properties(printip_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(printip_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(printip_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS printip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ipush@ya.ru)

include(CPack)

