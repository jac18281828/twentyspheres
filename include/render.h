#pragma once

#include "bitmap.h"
#include "color.h"
#include "twmath.h"

namespace twenty {

void shade_sphere(bitmap<>& buffer, const double kd, const double ks, const int spec_index, pixel<int> const& center,
                  const int radius, color3 const& light_source) {
  constexpr auto Ilight = 140;
  constexpr auto K = 70.0;
  constexpr auto IaKa = 0.15;
  constexpr auto Hx = vector3(0.325058, 0.325058, 0.888074);
  constexpr auto dx = point3(110.0, 110.0, 110.0);
  constexpr auto Lx = vector3(0.57735, 0.57735, 0.57735);
  constexpr auto epsilon = 1e-8;

  const auto rsquare = sqr(radius);
  for (auto y = -radius; y < radius; ++y) {
    const auto ysquare = sqr(y);
    for (auto x = -radius; x < radius; ++x) {
      const auto xsquare = sqr(x);
      if ((xsquare + ysquare) <= rsquare) {
        const auto z = std::round(std::sqrt(rsquare - xsquare - ysquare));
        const auto zsquare = sqr(z);
        const auto denom = std::sqrt(xsquare + ysquare + zsquare);
        point3 xn(x / denom, y / denom, z / denom);

        // calculate LN and NnH
        auto dist = 0.0, nh = 0.0, nnh = 0.0;
        auto ldotn = dot(Lx, xn);
        if (ldotn <= epsilon) {
          ldotn = 0.0;
        } else {
          auto delta = dx - point3(x, y, z);
          dist = length(delta);
          nh = dot(Hx, xn);
          nnh = std::exp(spec_index * std::log(nh));
        }
        // end calculate LN and NnH
        const auto ambientterm = IaKa;
        color_t ig, ir, ib;
        if (ldotn <= epsilon) {
          ir = std::round(light_source[0] * ambientterm);
          ig = std::round(light_source[1] * ambientterm);
          ib = std::round(light_source[2] * ambientterm);
        } else {
          const auto distfactor = Ilight / (dist + K);
          const auto diffuseterm = distfactor * kd * ldotn;
          const auto specularterm = distfactor * ks * nnh;
          ir = std::round(light_source[0] * (ambientterm + diffuseterm + specularterm));
          ig = std::round(light_source[1] * (ambientterm + diffuseterm + specularterm));
          ib = std::round(light_source[2] * (ambientterm + diffuseterm + specularterm));
        }

        pixel<int> p{center.x + x, center.y + y};
        color3 rgb{ir, ig, ib};

        buffer.set_pixel(p, rgb);
      }
    }
  }
}
} // namespace twenty
