# Project Overview

This project contains the implementation of various functionalities for handling buttons and rotary encoders. The code is organized into multiple files, each responsible for specific tasks.

## File Descriptions

### button.c
This file contains the implementation of button handling functions, including initialization, state change handling, and debouncing.

### button.h
This header file declares the functions and data structures used for button handling.

### button_if.c
This file provides the interface functions for interacting with the buttons, including getting the current state of a button.

### debug-out.h
This header file defines the `DEBUG_OUT` macro for outputting debug messages. The macro can be enabled or disabled using the `DEBUG_OUT_ENABLED` preprocessor directive.

### rotary-encoder-if.c
This file contains the implementation of functions for interacting with rotary encoders, including getting the state of a specified encoder pin.

### stm32h7xx_it.c
This file contains the interrupt service routines (ISRs) for handling various interrupts, including the ADC3 interrupt handler.

## Usage

To use the button and rotary encoder functionalities, include the appropriate header files in your source code and call the provided functions as needed. Ensure that the `DEBUG_OUT` macro is enabled or disabled based on your debugging requirements.

## Compilation

To compile the project, use the provided `CMakeLists.txt` file. Ensure that all necessary source files are included and that the correct include directories are specified.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact

For any questions or issues, please contact the project maintainer at [email@example.com].