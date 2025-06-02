####
# F prime CMakeLists.txt:
#
#
####
include(utilities)
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.cpp"
)

register_fprime_module()

