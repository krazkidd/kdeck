set(OATPP_VERSION "1.3.0")

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

# get the source
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO oatpp/oatpp-openssl
    REF 1.3.0-latest
    SHA512 f6b33fae3e3ad922ca13b5169173874eb49f77dc1288199b05d2bb0c034a0979ce893c37948cb42029d55fdb3df739da18e6deaebc4d43d54c3a0d9aca876a55
    HEAD_REF master
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        "-DOATPP_BUILD_TESTS:BOOL=OFF"
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME oatpp-openssl CONFIG_PATH "lib/cmake/oatpp-openssl-${OATPP_VERSION}")
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL "${SOURCE_PATH}/LICENSE" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}" RENAME copyright)
