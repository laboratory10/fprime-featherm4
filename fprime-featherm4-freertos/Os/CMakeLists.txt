restrict_platforms(ArduinoFw)
add_custom_target("${FPRIME_CURRENT_MODULE}")

# Set up Arduino implementations
add_fprime_supplied_os_module(Console Arduino)
add_fprime_supplied_os_module(RawTime Arduino)