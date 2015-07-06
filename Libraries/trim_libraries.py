#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 29 09:57:39 2015

@author: Ben
"""
import os
import fnmatch

# Things to keep
file_endings = (".dat", ".xml", ".ini", ".md", ".cmake", ".py", ".mk")
library_endings = (".dll", ".a", ".lib", ".dylib", ".so")
code_endings = (".c", ".C", ".c++", ".cc", ".cxx", ".cpp")
header_endings = (".h", ".H", ".h++", ".hh", ".hxx", ".hpp")
file_names = ("CMakeLists.txt", "deleted_files.txt", "Makefile", "makefile", "GNUmakefile")
file_patterns = ("*license*", "*LICENSE*", "*License*", 
                 "*readme*", "*README*", "*Readme*", "*ReadMe*",
                 "*copying*", "*COPYING*", "*Copying*",
                 "*notice*", "*NOTICE*", "*Notice*",
                 "*authors*", "*AUTHORS*", "*Authors*")

def wanted_file(name):
    for pattern in file_patterns:
        if fnmatch.fnmatch(name, pattern):
            return True
    
    return (name.endswith(file_endings) or name.endswith(code_endings) or
                name.endswith(header_endings) or name.endswith(library_endings) 
                or name in file_names)

def print_files(root_dir):
    print("@"*15)
    for root, dirs, files in os.walk(root_dir):
        for name in files:
            if not wanted_file(name):
                # get name local to this file by deleting the root dir part
                name = os.path.join(root, name).replace(root_dir, '')[1:]
                #replace backslashes with forward slashes
                name = name.replace('\\', '/')
                print(name)
    print("@"*15)

def delete_files(root_dir):
    print("Deleting ... ")
    file = open("deleted_files.txt", 'a')
    for root, dirs, files in os.walk(root_dir):
        for name in files:
            if not wanted_file(name):
                print(os.path.join(root, name).replace(root_dir, '.'))
                file.write(os.path.join(root, name).replace(root_dir, '') + '\n')
                os.remove(os.path.join(root, name))
                #pass
    file.close()
	
def gitignore_files(root_dir):
    print("Deleting ... ")
    file = open(".gitignore", 'a')
    file.write("# The following files will be ignored:\n")
    for root, dirs, files in os.walk(root_dir):
        for name in files:
            if not wanted_file(name):
                # get name local to this file by deleting the full path
                name = os.path.join(root, name).replace(root_dir, '')[1:]
                #replace backslashes with forward slashes
                name = name.replace('\\', '/')
                print(name)
                file.write(name + '\n')
    file.close()
			
# Use location of script as root directory
root_dir = os.path.dirname(os.path.realpath(__file__))

def make_choice():
    text = """
    Root directory: {}
    About to add to .gitignore all files not ending in:
        {}
        {}
        {}
        {}
    or with on of the names in:
        {}
    or names matching the pattern of:
        {}
    Root directory: {}
    Type 'c' to see files that will be added.
    Continue [y/c/n]?
    """.strip().format(root_dir, file_endings, library_endings, code_endings, 
                        header_endings, file_names, file_patterns, root_dir)
    
    choice = input(text)
    return choice

def main():
    choice = make_choice()
    while choice == 'c':
        print_files(root_dir)
        choice = make_choice()
    if choice == 'y':
        gitignore_files(root_dir)
        
main()        