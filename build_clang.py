import os
import sys

argc = len(sys.argv)

build_cpp = False
build_faust = False
release_mode = False

if argc == 1 or sys.argv[1] == "all": 
    build_cpp = True
    build_faust = True
    release_mode = False

elif sys.argv[1] == "faust":
    build_cpp = False
    build_faust = True
    release_mode = False

elif sys.argv[1] == "cpp":
    build_cpp = True
    build_faust = False
    release_mode = False
    
elif sys.argv[1] == "release":
    build_cpp = True
    build_faust = True
    release_mode = True

workspace_dir = os.getcwd()

def println(message : str):
    os.system(f"echo {message}\n")

if build_faust:
    # println("Compiling the faust dsp code")
    println("Compiling the faust dsp code")
    
    command = "faust -a minimal-effect.cpp tablesaw.dsp -o tablesaw_faust.h -nvi"
    println(command)

    result = os.system(command)
    if result:
        println("Error during compilation of faust code, exiting")
        exit(1)


if build_cpp:

    output_name = "Tablesaw_release" if release_mode else "Tablesaw_debug"
    output_extension = "vst3"
    
    # c flags
    flags = f" -pipe -shared -D_USE_MATH_DEFINES -D\"CPLUG_PLUGIN_NAME=\\\"{output_name}\\\"\""
    
    if release_mode:
        flags += " -O3"
    else:
        flags += " -gcodeview"
        
    warning_flags = "-Wall"
    
    includes = " ".join([
        "-ICPLUG/src",
        "-Iimgui", 
        "-Iimgui/backends",
        f"-include {workspace_dir}/config.h",
        "-I\"C:/Program Files/Faust/include\""
    ])
    
    sources = " ".join([
        "tablesaw.cpp",
    
        "imgui/imgui.cpp", 
        "imgui/backends/imgui_impl_win32.cpp", 
        "imgui/backends/imgui_impl_opengl3.cpp",
        
        "imgui/imgui_draw.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
    
        "CPLUG/src/cplug_vst3.c" 
    ])
        
    libs = " ".join([
        "-lopengl32",
        "-lkernel32",
        "-luser32",
        "-lgdi32",
        "-ldwmapi",
    ])
    
    println("Compiling c code")
    
    command = f"clang++ {flags} {warning_flags} {sources} -o {output_name}.vst3  {includes} {libs}"
    println(command)
    
    return_code = os.system(command)
    
    if return_code != 0: 
        println("Problems during compilation, exiting")
        exit(1)

    println("Cleaning")
    for file in filter(lambda string : ".obj" in string, os.listdir()):
        os.remove(file)

println("Done")