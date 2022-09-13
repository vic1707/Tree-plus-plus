-- add release and debug modes
add_rules("mode.release", "mode.debug")

-- add requires libs
add_requires("fmt 9.X")

-- not necesssary on macosx
if not is_plat("macosx") and not is_arch(os.arch()) then
    -- cross architecture compilation requirements
    add_requires("muslcc")
    set_toolchains("@muslcc")
end

target("treepp")
    set_kind("binary")
    set_filename("treepp_$(plat)_$(arch)")
    set_languages("cxx20")
    add_files("src/**.cpp")
    add_includedirs("inc")
    add_packages("fmt")
    if is_plat("windows") then
        -- add_cxxflags("/Wall /WX")
    else
        add_cxxflags("-Wall -Wextra -pedantic")
    end
