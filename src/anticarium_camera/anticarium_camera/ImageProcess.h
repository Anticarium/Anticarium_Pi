#pragma once
#include <anticarium_camera/PiImage.hpp>

class ImageProcess {
  public:
    ImageProcess();
    void writeRowId(PiImage& image);
};
