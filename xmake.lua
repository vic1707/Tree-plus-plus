-- add release and debug modes
add_rules("mode.release", "mode.debug")

-- add requires libs
add_requires("fmt 9.X")

-- not necesssary on macosx
if is_plat("linux") and not is_arch(os.arch()) then
    -- cross architecture compilation requirements
    add_requires("muslcc")
    set_toolchains("@muslcc")
end

target("treepp")
    set_kind("binary")
    set_languages("cxx20")
    add_files("src/**.cpp")
    add_includedirs("inc")
    add_packages("fmt")
    set_rundir("$(projectdir)")
    -- naming and flags which are OS specific
    if is_plat("windows") then
        set_filename("treepp_$(plat)_$(arch).exe")
    else
        set_filename("treepp_$(plat)_$(arch)")
        add_cxxflags("-Wall -Wextra -pedantic")
    end
