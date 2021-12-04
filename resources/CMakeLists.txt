set(INPUTS_DIR "${CMAKE_BINARY_DIR}/inputs")

# Default inputs
file(COPY "days" DESTINATION "${INPUTS_DIR}")
file(GLOB INPUT_DAYS_FILES
    "${INPUTS_DIR}/days/*"
)
list(SORT INPUT_DAYS_FILES COMPARE NATURAL)

foreach(INPUT_DAY_FILE ${INPUT_DAYS_FILES})
    get_filename_component(DEFAULT_INPUT_FILE "${INPUT_DAY_FILE}" NAME)
    set(DEFAULT_INPUT_FILE "inputs/days/${DEFAULT_INPUT_FILE}")
    get_filename_component(FUNCTION_NAME "${INPUT_DAY_FILE}" NAME_WE)
    string(TOLOWER "day_${FUNCTION_NAME}" FUNCTION_NAME)
    string(TOUPPER "${FUNCTION_NAME}" INPUT_VAR_NAME)

    # days inputs
    set(ENTRY "constexpr char const * ${INPUT_VAR_NAME} = \"${DEFAULT_INPUT_FILE}\";")
    if (DAYS_INPUTS)
        set(DAYS_INPUTS "${DAYS_INPUTS}\n    ${ENTRY}")
    else()
        set(DAYS_INPUTS "${ENTRY}")
    endif()

    # days functions
    set(ENTRY_A "std::string ${FUNCTION_NAME}_a(char const * input_file_path);")
    set(ENTRY_B "std::string ${FUNCTION_NAME}_b(char const * input_file_path);")
    if(DAYS_FUNCTIONS)
        set(DAYS_FUNCTIONS "${DAYS_FUNCTIONS}\n${ENTRY_A}\n${ENTRY_B}")
    else()
        set(DAYS_FUNCTIONS "${ENTRY_A}\n${ENTRY_B}")
    endif()

    # days array
    set(ENTRY_A "    Day{\n        \"${FUNCTION_NAME}_a\",\n        []{ return ${FUNCTION_NAME}_a(inputs::${INPUT_VAR_NAME}); }\n    }")
    set(ENTRY_B "    Day{\n        \"${FUNCTION_NAME}_b\",\n        []{ return ${FUNCTION_NAME}_b(inputs::${INPUT_VAR_NAME}); }\n    }")
    if (DAYS_DATA)
        set(DAYS_DATA "${DAYS_DATA},\n${ENTRY_A},\n${ENTRY_B}")
    else()
        list(LENGTH INPUT_DAYS_FILES DAYS_FUNCTION_COUNT)
        math(EXPR DAYS_FUNCTION_COUNT "${DAYS_FUNCTION_COUNT} * 2")
        set(DAYS_DATA "static std::array<Day, ${DAYS_FUNCTION_COUNT}> DAYS{\n${ENTRY_A},\n${ENTRY_B}")
    endif()
endforeach()
set(DAYS_DATA "${DAYS_DATA}\n};")

# Test inputs
file(COPY "tests" DESTINATION "${INPUTS_DIR}")
file(GLOB FILES "${INPUTS_DIR}/tests/*")
list(SORT FILES COMPARE NATURAL)
foreach(FILE ${FILES})
    get_filename_component(FILE_NAME "${FILE}" NAME)
    get_filename_component(FILE_NAME_WE "${FILE}" NAME_WE)

    # tests input files
    string(TOUPPER "${FILE_NAME_WE}" VAR_NAME)
    set(ENTRY "static constexpr char const * TEST_${VAR_NAME} = \"inputs/tests/${FILE_NAME}\";")
    if(TESTS_INPUTS)
        set(TESTS_INPUTS "${TESTS_INPUTS}\n    ${ENTRY}")
    else()
        set(TESTS_INPUTS "${ENTRY}")
    endif()
endforeach()

configure_file(resources.hpp.in resources.hpp @ONLY)