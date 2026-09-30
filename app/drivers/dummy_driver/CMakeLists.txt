if (CONFIG_DUMMY_DRIVER)
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
    target_sources(app PRIVATE dummy_driver.c)
endif()