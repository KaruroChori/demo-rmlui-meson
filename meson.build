project(
  'test-rmlui',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=c++23'],
)

cmake = import('cmake')

rmlui_opts =cmake.subproject_options()
rmlui_opts.add_cmake_defines(
    {
        'RMLUI_SDL_VERSION_MAJOR':3,
        'RMLUI_SHELL': 'ON',
        'RMLUI_BACKEND': 'SDL_SDLrenderer', #'X11_GL2'
        'CMAKE_POSITION_INDEPENDENT_CODE': true,
        'CMAKE_INSTALL_LIBDIR': get_option('libdir'),
    },
)
rmlui_subproj = cmake.subproject('rmlui',  options: rmlui_opts)

message('CMake targets:\n - ' + '\n - '.join(rmlui_subproj.target_list()))

sdl3_dep = dependency('sdl3')

executable(
    'demo',
    ['src/main.cpp'],
    install: true,
    dependencies: [
        sdl3_dep,
        rmlui_subproj.dependency('rmlui'),
        rmlui_subproj.dependency('rmlui_shell'),
        rmlui_subproj.dependency('rmlui_core'),
        rmlui_subproj.dependency('rmlui_debugger'),
    ],
)
