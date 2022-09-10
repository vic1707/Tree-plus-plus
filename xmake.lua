-- add release and debug modes
add_rules("mode.release", "mode.debug")

-- add requires libs
add_requires("fmt")

-- set arch
set_allowedarchs("armv7-a", "arm64-v8a", "armv5te", "mips", "mips64", "i386", "x86_64")

archs = { "armv7-a", "arm64-v8a", "armv5te", "mips", "mips64", "i386", "x86_64" }
-- add targets
for _, arch in ipairs(archs) do
    target("treepp_" .. os.host() .. "_" .. arch)
        set_kind("binary")
        set_arch(arch)
        add_files("src/**.cpp")
        add_includedirs("inc")
        set_languages("c++20")
        add_packages("fmt")
end
