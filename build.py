import os
import sys
from subprocess import Popen

vst3 = True

workspace_dir = os.getcwd()
source_dir = workspace_dir + "/Source"
lib_dir = workspace_dir + "/libs"

# flags
flags = "/nologo /MD /utf-8 /Zi"
warning_flags = "/Wall /wo4820 /wo5220"
output_name = ""

if vst3:
    flags += " /LD"
    output_name += "plugin.vst3"
else:
    output_name += "plugin.exe"

includes = " ".join([
    f"/I{lib_dir}/CPLUG/src",
    f"/I{lib_dir}/imgui", 
    f"/I{lib_dir}/imgui/backends",
    f"/FI{source_dir}/config.h"
])

sources = [
    f"{source_dir}/tablesaw.cpp", 
    
    f"{lib_dir}imgui/imgui.cpp", 
    f"{lib_dir}imgui/backends/imgui_impl_win32.cpp", 
    f"{lib_dir}imgui/backends/imgui_impl_opengl3.cpp",
    
    f"{lib_dir}imgui/imgui_draw.cpp",
    f"{lib_dir}imgui/imgui_tables.cpp",
    f"{lib_dir}imgui/imgui_widgets.cpp",
]

if vst3:
    sources.append("{lib_dir}CPLUG/src/cplug_vst3.c")
else:
    sources.append("{lib_dir}/CPLUG/src/cplug_standalone_win.c")
    
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
    print("Problems during compilation exiting")
    exit(1)


print("Linking")
link_command = f"cl {flags} /Fe:{output_name} /Fd:plugin.pdb"

for file in sources:
    link_command += f" {file}.obj"

link_command += f" /link {libs}"

# print(link_command)
result = os.system(link_command)

print("Cleaning")
for file in files_to_clean:
    os.remove(file)
    