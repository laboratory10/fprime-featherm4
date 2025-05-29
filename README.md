# fprime-featherm4

## Overview

Welcome to fprime-featherm4, a repository that contains board-specifc platform/toolchain/driver files for use in building a system that uses the <a href="https://fprime.jpl.nasa.gov/">F' Flight Software Framework</a> with the <a href="https://www.freertos.org/">FreeRTOS</a> open-source RTOS for microcontrollers and small microprocessors. This repository is designed to be paired with platform and OS specific repositories to run F' systems. If the OS you are trying to use already has a reference repository, I recommend starting there. For more detail, see the relevant repositories for the featherm4-freertos platform:

- <a href=https://github.com/laboratory10/fprime-featherm4-freertos-reference>fprime-featherm4-freertos-reference</a> - an example of a basic build using a specific platform
    - <a href=https://github.com/laboratory10/fprime-featherm4-freertos>fprime-featherm4-freertos</a> - a platform repository which is defined by a combination of board and OS
        - fprime-featherm4 (this repository) - board-specific platform/toolchain/driver files
        - <a href=https://github.com/laboratory10/fprime-freertos>fprime-freertos</a> - a port connecting the F' OSAL to FreeRTOS
 


