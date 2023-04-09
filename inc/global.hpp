//
// Created by juandiego on 4/6/23.
//

#ifndef FILE_SYSTEM_GLOBAL_HPP
#define FILE_SYSTEM_GLOBAL_HPP

using text = char*;

inline int int_sz = sizeof(int);
inline int float_sz = sizeof(float);

inline std::string file_not_open = "Cannot open the file";
inline std::string not_valid_position = "Invalid position";
inline std::string  reading_deleted_record = "Cannot read a deleted record";
inline std::string  record_already_deleted = "A deleted record is at this position";

#define CATCH \
    catch (std::runtime_error& error) { \
        std::cerr << error.what() << std::endl; \
    } \
    catch (std::invalid_argument& error) { \
        std::cerr << error.what() << std::endl; \
    }

#if defined(_WIN32) || defined(_WIN64)
inline const char * clear_console = "cls";
#else
inline const char * clear_console = "clear";
#endif

#endif //FILE_SYSTEM_GLOBAL_HPP
