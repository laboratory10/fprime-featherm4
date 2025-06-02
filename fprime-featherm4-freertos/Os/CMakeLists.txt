####
# F prime CMakeLists.txt:
#
#
####
add_custom_target("${FPRIME_CURRENT_MODULE}")

# Set up Arduino implementations
add_fprime_supplied_os_module(Console FeatherM4)
add_fprime_supplied_os_module(RawTime FeatherM4)