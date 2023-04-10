//
// Created by juandiego on 4/6/23.
//

#ifndef FILE_SYSTEM_GLOBAL_HPP
#define FILE_SYSTEM_GLOBAL_HPP

/// Types
using text = char *;

/// Constants
inline constexpr int int_sz = sizeof(int);
inline constexpr int float_sz = sizeof(float);

/// Menus
inline std::string menu_1 = "+===========================================+\n"
                            "║                                           ║\n"
                            "║            __  __                         ║\n"
                            "║           |  \\/  |___ _ _ _  _            ║\n"
                            "║           | |\\/| / -_) ' \\ || |           ║\n"
                            "║           |_|  |_\\___|_||_\\_,_|           ║\n"
                            "║                                           ║\n"
                            "║                                           ║\n"
                            "║     Options:                              ║\n"
                            "║                                           ║\n"
                            "║     [0]: Add a new record                 ║\n"
                            "║     [1]: Read all records                 ║\n"
                            "║     [2]: Read the ith record              ║\n"
                            "║     [3]: Exit                             ║\n"
                            "║                                           ║\n"
                            "+===========================================+";

inline std::string menu_2 = "+===========================================+\n"
                            "║                                           ║\n"
                            "║            __  __                         ║\n"
                            "║           |  \\/  |___ _ _ _  _            ║\n"
                            "║           | |\\/| / -_) ' \\ || |           ║\n"
                            "║           |_|  |_\\___|_||_\\_,_|           ║\n"
                            "║                                           ║\n"
                            "║                                           ║\n"
                            "║     Options:                              ║\n"
                            "║                                           ║\n"
                            "║     [0]: Add a new record                 ║\n"
                            "║     [1]: Read all records                 ║\n"
                            "║     [2]: Read the ith record              ║\n"
                            "║     [3]: Delete the ith record            ║\n"
                            "║     [4]: Initialize empty 'free list'     ║\n"
                            "║     [5]: Exit                             ║\n"
                            "║                                           ║\n"
                            "+===========================================+";

/// Error throw messages
inline std::string file_not_open = "Cannot open the file";
inline std::string not_valid_position = "Invalid position";
inline std::string reading_deleted_record = "Cannot read a deleted record";
inline std::string record_already_deleted = "A deleted record is at this position";

/// Error catch statement
#define CATCH \
    catch (std::runtime_error& error) { \
        std::cerr << error.what() << std::endl; \
    } \
    catch (std::invalid_argument& error) { \
        std::cerr << error.what() << std::endl; \
    }

/// Console clear command
#if defined(_WIN32) || defined(_WIN64)
inline const char * clear_console = "cls";
#else
inline const char *clear_console = "clear";
#endif

#endif //FILE_SYSTEM_GLOBAL_HPP
