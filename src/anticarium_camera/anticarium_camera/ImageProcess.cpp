#include <anticarium_camera/ImageProcess.h>
#include <string.h>

ImageProcess::ImageProcess() {
}

void ImageProcess::writeRowId(PiImage& image) {
    if (image.data.expired()) {
        return;
    }

    // write row number in first elements of each row
    auto height = image.size.height();

    // Multiplying by 3, because there are colors in pixel
    auto width = image.size.width() * 3;

    auto row = image.data.lock().get();
    for (int i = 0; i < height; i++) {
        const auto position = width * i;

        uint16_t rowNumber = static_cast<uint16_t>(i);
        unsigned char* arr = reinterpret_cast<unsigned char*>(&rowNumber);

        unsigned char result[3] = { 0, arr[1], arr[0] };

        // write row number in 1 and 2 indexes of row array
        memcpy(row + position, result, sizeof(result));
    }
}
