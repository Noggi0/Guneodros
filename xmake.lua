add_requires("libsdl")

set_project("Guneodros")
set_languages("cxx17")

if is_mode("release") then
    set_optimize("fastest")
elseif is_mode("debug") then
    set_warnings("allextra")
    set_optimize("none")
    set_symbols("debug")
end

add_requires("libsdl")

target("guneodros")
    set_kind("binary")
    add_files("./main.cpp")
    add_packages("libsdl")