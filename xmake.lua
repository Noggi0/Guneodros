set_project("Guneodros")
set_languages("cxx20")

if is_mode("release") then
    set_optimize("fastest")
elseif is_mode("debug") then
    set_warnings("allextra")
    set_optimize("none")
    set_symbols("debug")
    add_defines("DEBUG")
end

add_requires("libsdl")
add_requires("libsdl_image")

target("guneodros")
    set_kind("binary")
    add_files("./main.cpp")
    add_packages("libsdl")
    add_packages("libsdl_image")

target("world_tests")
    set_kind("binary")
    set_default(false)
    add_files("./Tests/WorldTests.cpp")

target("application_tests")
    set_kind("binary")
    set_default(false)
    add_files("./Tests/ApplicationTests.cpp")
    add_packages("libsdl")
    add_packages("libsdl_image")
