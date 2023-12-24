#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include "TreeNode.h"
#include "AVLTree.h"
#include "HashNode.h"
#include "HashTable.h"

// File paths for result and output handling
// Note: These paths are set relative to the source file location.

// The path of the current file
const std::string _THIS_PATH_ = __FILE__;

// Function to obtain the parent path of a given path
std::string parent_path(const std::string& path = _THIS_PATH_) {
    size_t pos = path.find_last_of("\\");

    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(0, pos);
}

// The source path (parent path of the current file)
const std::string _SOURCE_PATH_ = parent_path(_THIS_PATH_);

// The path for storing result files
const std::string _RESULT_PATH_ = parent_path(_SOURCE_PATH_) + "\\results";

// The default output file path
const std::string _DEFAULT_OUTPUT_PATH_ = _RESULT_PATH_ + "\\result.txt";

// The path for displaying output
const std::string _DISPLAY_PATH_ = _RESULT_PATH_ + "\\display.txt";

// Function to get the full path of a file based on its filename
std::string get_path_file(const std::string& filename) {
    size_t pos = filename.find("\\");
    if (pos == std::string::npos) {
        return _RESULT_PATH_ + "\\" + filename;
    }
    return filename;
}

#endif // !HEADER_H