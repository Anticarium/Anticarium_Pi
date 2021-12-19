#include <anticarium_camera/ImageProcess.h>
#include <gtest/gtest.h>

TEST(TestImageProcess, TestBuild) {
    auto pixels = std::make_shared<unsigned char[]>(12);

    pixels[0]  = 1;
    pixels[1]  = 2;
    pixels[2]  = 3;
    pixels[3]  = 4;
    pixels[4]  = 5;
    pixels[5]  = 6;
    pixels[6]  = 7;
    pixels[7]  = 8;
    pixels[8]  = 9;
    pixels[9]  = 10;
    pixels[10] = 11;
    pixels[11] = 12;

    PiImage piImage;
    piImage.data = pixels;
    piImage.size.setWidth(2);
    piImage.size.setHeight(2);

    ImageProcess::writeRowId(piImage);

    EXPECT_EQ(piImage.data.lock()[0], 0);
    EXPECT_EQ(piImage.data.lock()[1], 0);
    EXPECT_EQ(piImage.data.lock()[2], 0);
    EXPECT_EQ(piImage.data.lock()[3], 4);
    EXPECT_EQ(piImage.data.lock()[4], 5);
    EXPECT_EQ(piImage.data.lock()[5], 6);
    EXPECT_EQ(piImage.data.lock()[6], 0);
    EXPECT_EQ(piImage.data.lock()[7], 1);
    EXPECT_EQ(piImage.data.lock()[8], 0);
    EXPECT_EQ(piImage.data.lock()[9], 10);
    EXPECT_EQ(piImage.data.lock()[10], 11);
    EXPECT_EQ(piImage.data.lock()[11], 12);
}
