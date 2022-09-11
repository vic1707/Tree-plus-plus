-- add release and debug modes
add_rules("mode.release", "mode.debug")

-- add requires libs
add_requires("fmt")


target("treepp")
    set_kind("binary")
    set_languages("c++20")
    add_files("src/**.cpp")
    add_includedirs("inc")
    add_packages("fmt")
