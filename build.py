import os
import sys
from subprocess import Popen

vst3 = True

workspace_dir = os.getcwd()

faust = True
if faust: 
    print("Compiling the faust dsp code")
    # command = "faust -a minimal-effect.cpp tablesaw.dsp -o tablesaw_faust.h -vec -nvi -i"
    command = "faust -a minimal-effect.cpp tablesaw.dsp -o tablesaw_faust.h -vec -nvi"
    print(command)

    result = os.system(command)
    if result:
        print("Error during compilation of faust code, exiting")
        exit(1)

# flags
flags = "/nologo /MD /EHsc /utf-8 /Zi /D _USE_MATH_DEFINES /MP1"
warning_flags = "/Wall /wd4820 /wd5220 /wd4100 /wd4201"
output_name = ""
output_extension = ""

if vst3:
    flags += " /LD"
    output_name += "tablesaw"
    output_extension += "vst3"
else:
    output_name += "tablesaw.exe"
    output_extension += "exe"

includes = " ".join([
    f"/ICPLUG/src",
    f"/Iimgui", 
    f"/Iimgui/backends",
    f"/FI{workspace_dir}/config.h",
    f"/I\"C:/Program Files/Faust/include\""
])

sources = [
    f"tablesaw.cpp", 
    
    f"imgui/imgui.cpp", 
    f"imgui/backends/imgui_impl_win32.cpp", 
    f"imgui/backends/imgui_impl_opengl3.cpp",
    
    f"imgui/imgui_draw.cpp",
    f"imgui/imgui_tables.cpp",
    f"imgui/imgui_widgets.cpp",
]

if vst3:
    sources.append("CPLUG/src/cplug_vst3.c")
else:
    sources.append("CPLUG/src/cplug_standalone_win.c")
    
libs = " ".join([
    "opengl32.lib",
    "kernel32.lib",
    "user32.lib",
    "gdi32.lib",
])

if not vst3 :
    libs += " Ole32.lib"

processes = []
files_to_clean = []

print("Compiling c code")
for index, file in enumerate(sources):
    # print(f"Compiling {file}")
    
    command = f"cl /c {flags} {file} /Fd:{file}.pdb /Fo:{file}.obj {includes}"
    
    if file == "tablesaw.cpp":
        command += f" {warning_flags}"
    
    # print(command, "\n")
    processes.append(Popen(command))
    files_to_clean.append(f"{file}.obj")
    files_to_clean.append(f"{file}.pdb")
return_code = 0
        
for index, process in enumerate(processes):
    process.wait()
    return_code += process.poll() 
    print(f"Compilation of {sources[index]} terminated with code {return_code}")

if return_code != 0: 
    print("Problems during compilation, exiting")
    exit(1)


print("Linking")
link_command = f"cl {flags} /Fe:{output_name}.{output_extension} /Fd:{output_name}.pdb"

for file in sources:
    link_command += f" {file}.obj"

link_command += f" /link {libs}"

# print(link_command)
result = os.system(link_command)

if result != 0:
    print("Problems during linking, exiting")
    exit(1)

print("Cleaning")
for file in files_to_clean:
    os.remove(file)

print("Done")
