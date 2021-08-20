#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#include "bitmap.h"
#include "color.h"
#include "environment.h"
#include "image.h"
#include "render.h"
#include "tripple.h"
#include "twmath.h"

using namespace twenty;
using namespace std::literals::chrono_literals;

namespace {

constexpr auto height = 400;
constexpr auto width = 400;

static environment make_environment() {
  environment env;

  auto xform = transform(vector3{width, height, 1}, vector3{0, 0, 0});

  auto green = spectra{0, 1, 0};
  auto cptr = std::make_shared<cube>(1, 1, 1, green);

  env.add(element_instance(cptr, xform));

  return env;
}

static bool is_inside(pixel<int> const& pix, patch4 const& p) {
  auto start = p.begin();
  auto v1 = *start;
  ++start;
  auto theta = 0.0;
  while (start != p.end()) {
    auto next = *start;
    auto norm = normalize(cross(next, v1));
  }
}

static void render(bitmap& bm, patch4 const& p) {
  // scan p
  for (int i = 0; i < bm.width(); ++i) {
    for (int j = 0; j < bm.height(); ++j) {
      pixel<int> screen{i, j};
      if (is_inside(screen, p)) {
        bm.set_pixel(screen, color3{255, 0, 0});
      }
    }
  }
}

static void render_environment(environment const& env, std::string const& filename) {

  const auto light_source = color3{238, 238, 245};

  bitmap bmap(width, height);

  bmap.fill(light_source);

  for (auto enviter = std::begin(env); enviter != std::end(env); ++enviter) {
    auto patch_list = enviter->get_patch_list();
    for (auto patchiter = std::begin(patch_list); patchiter != std::end(patch_list); ++patchiter) {
      render(bmap, *patch);
    }
  }

  auto jpeg = jpegfile(filename);
  jpeg.write(bmap.buffer(), width, height);
  std::cout << filename << std::endl;
}

static void render_image(std::string const& filename) {

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
    const auto filename = argv[1];
    auto env = make_environment();
    render_environment(env, filename);
  }

  std::this_thread::sleep_for(60s);

  return 0;
}
