#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include "bitmap.h"
#include "color.h"
#include "image.h"
#include "render.h"
#include "tripple.h"

using namespace twenty;
using namespace std::literals::chrono_literals;

namespace {

constexpr auto height = 400;
constexpr auto width = 400;

void render_image(std::string const& filename) {

  const auto light_source = color3{238, 238, 245};

  bitmap bmap(width, height);

  bmap.fill(light_source);

  constexpr auto kd = 0.2;
  constexpr auto ks = 0.6;
  constexpr auto spec_idx = 1.0;

  constexpr auto N = 16;
  constexpr double spec_step = (ks - kd) / N;

  double kz = 0.0;

  constexpr auto Nx = 5;
  for (int i = 0; i < Nx; ++i) {
    const auto xstep = width / Nx;
    const auto Ny = N / Nx;
    for (int j = 0; j < Ny; ++j) {
      const auto ystep = height / Ny;
      constexpr auto radius = std::min(width, height) / (std::max(Nx, Ny) + 2) / 2;
      pixel<int> center{i * xstep + xstep / 2, j * ystep + ystep / 2};
      shade_sphere(bmap, kd + kz, ks - kz, spec_idx, center, radius, light_source);
      kz += spec_step;
    }
  }

  auto jpeg = jpegfile(filename);
  jpeg.write(bmap.buffer(), width, height);
  std::cout << filename << std::endl;
}

} // namespace

int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr << "filename expected." << std::endl;
    return 1;
  } else {
    render_image(argv[1]);
  }

  std::this_thread::sleep_for(60s);

  return 0;
}
