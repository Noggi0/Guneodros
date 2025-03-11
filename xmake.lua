set_project("Guneodros")
set_languages("cxx17")

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