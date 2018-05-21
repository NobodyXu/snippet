#!/usr/bin/python3
from subprocess import run

output_stream = open("output_file", "w", encoding = "utf-8")
versions_stream = open("version_output", encoding = "utf-8")

def _Run(command):
    output_stream.write("\n" + str(command) + ":\n")
    returncode = run(command, stdout = output_stream, stderr = output_stream).returncode
    output_stream.write("\nReturn code: " + str(returncode) + "\n\n")

def Run(command, tf_version = ""):
    _Run(["sudo", "pip3"] +  command + ["tensorflow" + tf_version])

while versions_stream.readable():
    version_str = versions_stream.readline()
    assert len(version_str) > 0

    #Uninstall tensorflow
    Run(["uninstall", "-y"])

    #Install the specific-version tensorflow
    Run(["install"], "==" + version_str)

    #Run the py script to verify the install of tensorFlow
    _Run("./verify_install.py")
