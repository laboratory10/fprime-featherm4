####
# F prime CMakeLists.txt:
#
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/FeatherM4Time.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/FeatherM4Time.cpp"
)
target_use_arduino_libraries("TimeLib")

register_fprime_module()

