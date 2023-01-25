#include "life_file_base.h"

FileOpeningError::FileOpeningError()
    : std::runtime_error("File opening error\n") {}
