#include <anticarium_camera/ImageProcess.h>
#include <string.h>

void ImageProcess::writeRowId(PiImage& image) {
    if (image.data.expired()) {
        return;
    }

    const int height = image.size.height();

    constexpr int colorsInPixel = 3;
    const int width = image.size.width() * colorsInPixel;

    auto row = image.data.lock().get();

    // Image must be mirrored
    for (int i = 0, rowNumber = height - 1; i < height; i++, rowNumber--) {
        const auto position = width * i;

        // write row number in first elements of each row
        uint16_t rowNumberBuffer = static_cast<uint16_t>(rowNumber);
        unsigned char* arr = reinterpret_cast<unsigned char*>(&rowNumberBuffer);

        unsigned char result[3] = { 0, arr[0], arr[1] };

        memcpy(row + position, result, sizeof(result));
    }
}
