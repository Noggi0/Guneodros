set_project("Guneodros")
set_languages("cxx20")

add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

if is_mode("release") then
    set_optimize("fastest")
elseif is_mode("debug") then
    set_warnings("allextra")
    set_optimize("none")
    set_symbols("debug")
    add_defines("DEBUG")
end

add_requires("libsdl2")
add_requires("libsdl2_image")

target("guneodros")
    set_kind("binary")
    add_files("./main.cpp")
    add_packages("libsdl2")
    add_packages("libsdl2_image")

if os.isfile("Tests/WorldTests.cpp") then
    target("world_tests")
        set_kind("binary")
        set_default(false)
        add_files("./Tests/WorldTests.cpp")
end

if os.isfile("Tests/ApplicationTests.cpp") then
    target("application_tests")
        set_kind("binary")
        set_default(false)
        add_files("./Tests/ApplicationTests.cpp")
        add_packages("libsdl2")
        add_packages("libsdl2_image")
end
