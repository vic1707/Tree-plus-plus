-- add release and debug modes
add_rules("mode.release", "mode.debug")

-- add requires libs
add_requires("fmt")

-- set c++ standard
set_languages("c++20")

target("treepp")
    set_kind("binary")
    add_files("src/**.cpp")
    add_includedirs("inc")
    add_packages("fmt")
