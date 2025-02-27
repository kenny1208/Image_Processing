# include <iostream>
# include <vector>
using namespace std;


int getRGB(int x, int y, FILE* fp)
{
	unsigned char c;
	for (int i = 0;i < 54;i++)
	{
		c = getc(fp);
	}

	for (int i = 0;i < (50 - y - 1) * 1024;i++)
	{
		c = getc(fp);
	}
	for (int i = 0;i < x;i++)
	{
		c = getc(fp);
	}


	unsigned char b = getc(fp);
	unsigned char g = getc(fp);
	unsigned char r = getc(fp);
	printf("R: %d, G: %d, B: %d\n", r, g, b);
	return 0;
}

int main()
{
	FILE* fp;
	bool err = fopen_s(&fp, "AiPicG.bmp", "rb");
	unsigned char c;
	if (!err)
	{
		unsigned char c;
		for (int i = 0;i < 1024 + 54;i++)
		{
			c = getc(fp);
		}

		int histogram[256] = { 0 };

		for (int y = 0; y <1024; y++)
		{
			for (int x = 0; x < 1024; x++)
			{
				c = getc(fp);
				histogram[(int)c]++;
			}
		}

		for (int i = 0; i < 256; i++)
		{
			printf("Gray%d: %d\n", i, histogram[i]);
		}
		fclose(fp);
	}
}
