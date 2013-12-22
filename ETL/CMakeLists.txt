cmake_minimum_required (VERSION 2.8.9)
project(SynfigETL)

set(ETL_MAJOR "0")
set(ETL_MINOR "04")
set(ETL_PATCH "18")
set(ETL_VER "${ETL_MAJOR}.${ETL_MINOR}.${ETL_PATCH}")

set(ETL_PREFIX   ${CMAKE_INSTALL_PREFIX})
set(ETL_BIN_PATH ${ETL_PREFIX}/bin)
set(ETL_LIB_PATH ${ETL_PREFIX}/lib)
set(ETL_INCLUDE_PATH ${ETL_PREFIX}/include)

configure_file(ETL.pc.in ETL.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ETL.pc DESTINATION ${ETL_PREFIX}/lib/pkgconfig)

add_subdirectory(ETL)
