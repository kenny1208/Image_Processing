# include <iostream>
# include <vector>
using namespace std;

#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))

void rgb2yuv(const unsigned char& src_r, const unsigned char& src_g, const unsigned char& src_b, unsigned char& dst_y, unsigned char& dst_u, unsigned char& dst_v)
{
    float r = static_cast<float>(src_r);
    float g = static_cast<float>(src_g);
    float b = static_cast<float>(src_b);

    float y = 0.299f * r + 0.587f * g + 0.114f * b;
    float u = -0.169f * r + -0.331f * g + 0.5f * b + 128.0f;
    float v = 0.5f * r + -0.419f * g + -0.081f * b + 128.0f;

    dst_y = y >= 255 ? 255 : (unsigned char)(y + 0.5);
    dst_u = u >= 255 ? 255 : (unsigned char)(u + 0.5);
    dst_v = v >= 255 ? 255 : (unsigned char)(v + 0.5);
}

void yuv2rgb(const unsigned char& src_y, const unsigned char& src_u, const unsigned char& src_v, unsigned char& dst_r, unsigned char& dst_g, unsigned char& dst_b)
{
    float y = static_cast<float>(src_y);
    float u = static_cast<float>(src_u);
    float v = static_cast<float>(src_v);

    float r = 1.0f * y + -0.00093f * u + 1.401687f * v;
    float g = 1.0f * y + -0.3437f * u + -0.71417f * v - 128.0f;
    float b = 1.0f * y + 1.77216f * u + 0.00099f * v - 128.0f;
}

void rgb2hsv(const unsigned char& src_r, const unsigned char& src_g, const unsigned char& src_b, unsigned char& dst_h, unsigned char& dst_s, unsigned char& dst_v)
{
    float r = src_r / 255.0f;
    float g = src_g / 255.0f;
    float b = src_b / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = max_f(r, g, b);
    float min = min_f(r, g, b);

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    dst_h = (unsigned char)(h / 2);   // dst_h : 0-180
    dst_s = (unsigned char)(s * 255); // dst_s : 0-255
    dst_v = (unsigned char)(v * 255); // dst_v : 0-255
}   

int main() {
    FILE* fp;
    int x = 345, y = 174;
    bool err = fopen_s(&fp, "AiPicG.bmp", "rb");
    unsigned char c;
    if (err != 0)
        return 0;
    for (int i = 0; i < 1078; i++) {
        c = getc(fp);
    }
    int W = 1024;
    int H = 1024;

    for (int i = 0; i < W * (H - y - 1); i++) {
        c = getc(fp);
    }
    for (int j = 0; j < x; j++) {
        c = getc(fp);
    }
    
	unsigned char r = 255;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char h, s, v;
	rgb2hsv(r, g, b, h, s, v);
	printf("r=%d, g=%d, b=%d, h=%d, s=%d, v=%d\n", r, g, b, h, s, v);

    unsigned char y_val, u, v1;
    rgb2yuv(r, g, b, y_val, u, v1);
    printf("r=%d, g=%d, b=%d, y=%d, u=%d, v=%d\n", r, g, b, y_val, u, v1);

	unsigned char r1, g1, b1;
	yuv2rgb(y_val, u, v1, r1, g1, b1);
	printf("y=%d, u=%d, v=%d, r=%d, g=%d, b=%d\n", y_val, u, v1, r1, g1, b1);



    fclose(fp);
}
