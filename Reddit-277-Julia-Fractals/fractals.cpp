#include <algorithm>
#include <chrono>
#include <complex>
#include <iostream>

typedef std::complex<double> comp;

constexpr comp parameter(-0.221, -0.713);
constexpr double threshold = 2.0;

// based on https://en.wikipedia.org/wiki/User:Evercat/Buddhabrot.c
void drawbmp(char *filename, uint_fast64_t width, uint_fast64_t height, std::vector<std::vector<uint_fast8_t>> data) {

  unsigned int headers[13];
  FILE *outfile;

  int extrabytes = 4 - ((width * 3) % 4);                 // How many bytes of padding to add to each
  // horizontal line - the size of which must
  // be a multiple of 4 bytes.
  if (extrabytes == 4)
    extrabytes = 0;

  int paddedsize = ((width * 3) + extrabytes) * height;

// Headers...
// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

  headers[0] = paddedsize + 54;      // bfSize (whole file size)
  headers[1] = 0;                    // bfReserved (both)
  headers[2] = 54;                   // bfOffbits
  headers[3] = 40;                   // biSize
  headers[4] = width;  // biwidth
  headers[5] = height; // biheight

// Would have biPlanes and biBitCount in position 6, but they're shorts.
// It's easier to write them out separately (see below) than pretend
// they're a single int, especially with endian issues...

  headers[7] = 0;                    // biCompression
  headers[8] = paddedsize;           // biSizeImage
  headers[9] = 0;                    // biXPelsPerMeter
  headers[10] = 0;                    // biYPelsPerMeter
  headers[11] = 0;                    // biClrUsed
  headers[12] = 0;                    // biClrImportant

  outfile = fopen(filename, "wb");

//
// Headers begin...
// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
//

  fprintf(outfile, "BM");

  for (int n = 0; n <= 5; n++) {
    fprintf(outfile, "%c", headers[n] & 0x000000FF);
    fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
    fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
    fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
  }

// These next 4 characters are for the biPlanes and biBitCount fields.

  fprintf(outfile, "%c", 1);
  fprintf(outfile, "%c", 0);
  fprintf(outfile, "%c", 24);
  fprintf(outfile, "%c", 0);

  for (int n = 7; n <= 12; n++) {
    fprintf(outfile, "%c", headers[n] & 0x000000FF);
    fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
    fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
    fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
  }

//
// Headers done, now write the data...
//

  for (int y = height - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
  {
    for (int x = 0; x <= width - 1; x++) {
      fprintf(outfile, "%c", data[y][x]);
      fprintf(outfile, "%c", data[y][x]);
      fprintf(outfile, "%c", data[y][x]);
    }
    if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
    {
      for (int n = 1; n <= extrabytes; n++) {
        fprintf(outfile, "%c", 0);
      }
    }
  }

  fclose(outfile);
  return;
}

comp func(const comp z, const comp par) {
  return z * z + par;
}

uint_fast64_t iter(comp z, const comp par, double thres) {
  uint_fast64_t count = 0;
  while (std::abs(z) < thres) {
    z = func(z, par);
    ++count;
  }
  return count;
}

std::vector<std::vector<uint_fast8_t>> julia_set(uint_fast64_t width,
                                                 uint_fast64_t height,
                                                 const comp par = parameter,
                                                 double thres = threshold,
                                                 uint_fast64_t aa_samples = 4) {
  std::vector<uint_fast64_t> tmp1(width);
  std::vector<std::vector<uint_fast64_t>> tmp_julia_set(height, tmp1);

  tmp_julia_set.reserve(height);

  double h_step = 2.0 / height, w_step = 2.0 / width;

  for (uint_fast64_t i = 0; i < height; ++i)
#pragma omp parallel for simd
      for (uint_fast64_t j = 0; j < width; ++j)
        tmp_julia_set[i][j] = iter(comp(-1 + w_step * j, -1 + h_step * i), par, thres);

  uint_fast64_t mx = 1;
  for (uint_fast64_t i = 0; i < height; ++i)
    mx = std::max(mx, *std::max_element(tmp_julia_set[i].begin(), tmp_julia_set[i].end()));


  std::vector<uint_fast8_t> tmp(tmp_julia_set[0].size());
  std::vector<std::vector<uint_fast8_t>> julia_set(tmp_julia_set.size(), tmp);
  for (uint_fast64_t i = 0; i < tmp_julia_set.size(); ++i)
    for (uint_fast64_t j = 0; j < tmp_julia_set[i].size(); ++j)
      julia_set[i][j] = std::round(255.0 * static_cast<double>(tmp_julia_set[i][j]) / mx);

  return julia_set;
}

int main() {
  auto begin = std::chrono::high_resolution_clock::now();
  drawbmp("result1.bmp", 1920, 1080, julia_set(1920, 1080));
  auto end1 = std::chrono::high_resolution_clock::now();
  drawbmp("result2.bmp", 1920, 1080, julia_set(1920, 1080, comp(0.285, 0.01)));
  auto end2 = std::chrono::high_resolution_clock::now();
  drawbmp("result3.bmp", 3840, 2160, julia_set(3840, 2160, comp(0, 0.8)));
  auto end3 = std::chrono::high_resolution_clock::now();
  std::cout << "Time1 " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin).count() << " ms."
      << std::endl;
  std::cout << "Time2 " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end1).count() << " ms."
      << std::endl;
  std::cout << "Time3 " << std::chrono::duration_cast<std::chrono::milliseconds>(end3 - end2).count() << " ms."
      << std::endl;
  return 0;
}
