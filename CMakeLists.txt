message("sgx_urts_rust")

set(SGX_URTS_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/sgx_urts/target/release/libsgx_urts.a)
add_custom_command(
  OUTPUT ${SGX_URTS_OUTPUT}
  COMMAND cargo build --release
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sgx_urts
)

add_custom_target(sgx_urts_target
  DEPENDS ${SGX_URTS_OUTPUT}
)

add_library(sgx_urts_rust STATIC IMPORTED GLOBAL)
add_dependencies(sgx_urts_rust sgx_urts_target)

set_target_properties(sgx_urts_rust
    PROPERTIES
    IMPORTED_LOCATION "${SGX_URTS_OUTPUT}"
)

# IMPORTED libraries cannot be installed, so we just copy the files,
# and define (in Secretarium.cmake) sgx_urts_rust as an IMPORTED library pointing to the installed file
install(FILES ${SGX_URTS_OUTPUT} DESTINATION ${CMAKE_INSTALL_LIBDIR})
