//
// Created by juandiego on 4/6/23.
//

#ifndef FILE_SYSTEM_GLOBAL_HPP
#define FILE_SYSTEM_GLOBAL_HPP

using text = char*;

inline int int_sz = sizeof(int);
inline int float_sz = sizeof(float);

inline const char * file_not_open = "Cannot open the file\n";
inline const char * not_valid_position = "Invalid position\n";
inline const char * reading_deleted_record = "Cannot read a deleted record";
inline const char * record_already_deleted = "A deleted record is at this position";

#if defined(_WIN32) || defined(_WIN64)
const char * clear_console = "cls";
#else
const char * clear_console = "clear";
#endif

#endif //FILE_SYSTEM_GLOBAL_HPP
