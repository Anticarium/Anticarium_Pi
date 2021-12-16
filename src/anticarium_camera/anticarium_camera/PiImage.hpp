#pragma once

#include <QSize>
#include <memory>

// Each row starts with row number for PiImage
// Row number is stored as uint16_t as 1 and 2 element in row
// Note that element 0 is empty
struct PiImage {
    QSize size;
    std::weak_ptr<unsigned char[]> data;
};
