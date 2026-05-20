cmake_minimum_required(VERSION 3.20)

project(TEMPLATE_C_SDL3 LANGUAGES C)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

#output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# set production flags
set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

# This assumes the SDL source is available in vendor/linux/SDL...
if(UNIX)
    add_subdirectory(vendor/linux/SDL EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/linux/SDL_image EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/linux/SDL_mixer EXCLUDE_FROM_ALL)
    add_subdirectory(vendor/linux/SDL_ttf EXCLUDE_FROM_ALL)
endif()

include_directories(
    src/core
    src/ecs
    src/state
    src/factories
    src/widgets
    src/systems
    src/world
    src/serialization
    vendor/microui
    vendor/nuklear
)

add_executable(TEMPLATE_C_SDL3
    src/main.c
    src/pch.h
    src/core/process_input.h src/core/process_input.c
    src/core/engine_state.h
    src/core/update.h src/core/update.c
    src/core/render.h src/core/render.c
    src/core/engine_state.c
    src/core/window_events.h src/core/window_events.c
    src/core/texture_helpers.h src/core/texture_helpers.c
    src/core/camera.h src/core/camera.c
    src/ecs/ecs.h src/ecs/ecs.c
    src/ecs/components.h
    src/ecs/components.c
    src/ecs/entity_manager.h src/ecs/entity_manager.c
    src/ecs/entity.h
    src/ecs/entity.c
    src/core/asset_manager.h src/core/asset_manager.c
    src/states/game_state.h
    src/states/game_state.c
    src/states/game_play_state.h
    src/states/game_play_state.c
    src/factories/add_player.h src/factories/add_player.c
    src/core/input_state.h
    src/factories/add_tile.h src/factories/add_tile.c

    # microui
    # vendor/microui/microui.h
    # vendor/microui/microui.c
    # src/core/microui_helpers.h src/core/microui_helpers.c
    # src/widgets/microui_widgets.h src/widgets/microui_widgets.c
    # src/widgets/microui_definitions.h
    src/core/editor.h src/core/editor.c
    src/world/map.h src/world/map.c
    src/systems/system_render_entities.h src/systems/system_render_entities.c
    src/core/core_helpers.h src/core/core_helpers.c
    src/serialization/serialization_map.h src/serialization/serialization_map.c
    src/systems/system_queue_free.h src/systems/system_queue_free.c
    src/gui_nuklear/nuklear_helpers.h src/gui_nuklear/nuklear_helpers.c

)

if(PRODUCTION_BUILD)
        # setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)

else()
        # This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
    SDL3_image::SDL3_image
    SDL3::SDL3
)
