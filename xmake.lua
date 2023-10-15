set_project("noteblade")
set_allowedarchs("windows|x86", "macosx|arm64", "macosx|x64")
add_rules("mode.debug", "mode.release")

package("tinyxml2")
    add_urls("https://github.com/leethomason/tinyxml2/archive/$(version).tar.gz")
    add_versions("8.0.0", "6ce574fbb46751842d23089485ae73d3db12c1b6639cda7721bf3a7ee862012c")
    add_versions("9.0.0", "cc2f1417c308b1f6acc54f88eb70771a0bf65f76282ce5c40e54cfe52952702c")
    
    on_install("windows", "macosx", function (package)
        os.cp("tinyxml2.h", package:installdir("include"))
        os.cp("tinyxml2.cpp", package:installdir("src"))
        if is_plat("windows") then
            import("package.tools.xmake").install(package, {"--toolchain=msvc", "--arch=x86"})
        end
        if is_plat("macosx") then
            import("package.tools.xmake").install(package, {"--toolchain=clang"})
        end
    end)
package_end()
add_requires("tinyxml2 9.0.0")

target("noteblade")
    set_kind("binary")
    add_packages("tinyxml2")
    add_files("src/*.cpp")
    if is_plat("macosx", "linux") then
        set_toolchains("clang")
        set_languages("c++17")
        add_cxxflags("-std=c++17")
        add_cxxflags("-DBUILD_PLATFORM=\"$(os)\"")
        add_cxxflags("-DBUILD_TIME=\"$(shell date '+%Y-%m-%dT%H:%M:%S%z')\"")
        add_cxxflags("-DBUILD_HOSTNAME=\"$(shell hostname)\"")
    end
    if is_plat("windows") then
        set_toolchains("msvc")
        set_languages("c++20")
        add_cxxflags("/std:c++20 /utf-8")
        add_cxxflags("/DBUILD_TIME=\"$(shell powershell Get-Date -Format o)\"")
        add_cxxflags("/DBUILD_HOSTNAME=\"$(env computername)\"")
    end
