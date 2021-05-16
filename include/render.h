#pragma once

namespace twenty {

void shade_sphere(screenbuffer_t& buffer, rect<int> const& screen,
                  const double kd, const double ks, const int spec_index,
                  pixel<int> const& center, const int radius,
                  point<color_t> const& light_source) {
  constexpr auto Ilight = 140;
  constexpr auto K = 70.0;
  constexpr auto IaKa = 0.15;
  constexpr auto Hx = 0.325058, Hy = 0.325058, Hz = 0.888074;
  constexpr auto dx = 110.0, dy = 110.0, dz = 110.0;
  constexpr auto Lx = 0.57735, Ly = 0.57735, Lz = 0.57735;
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
        point<double> xn;
        xn.x = x / denom;
        xn.y = y / denom;
        xn.z = z / denom;
        // calculate LN and NnH
        auto dist = 0.0, nh = 0.0, nnh = 0.0;
        auto ldotn = xn.x * Lx + xn.y * Ly + xn.z * Lz;
        if (ldotn <= epsilon) {
          ldotn = 0.0;
        } else {
          dist = std::sqrt(sqr(dx - x) + sqr(dy - y) + sqr(dz - z));
          nh = Hx * xn.x + Hy * xn.y + Hz * xn.z;
          nnh = std::exp(spec_index * std::log(nh));
        }
        // end calculate LN and NnH
        const auto ambientterm = IaKa;
        color_t ig, ir, ib;
        if (ldotn <= epsilon) {
          ir = std::round(light_source.x * ambientterm);
          ig = std::round(light_source.y * ambientterm);
          ib = std::round(light_source.z * ambientterm);
        } else {
          const auto distfactor = Ilight / (dist + K);
          const auto diffuseterm = distfactor * kd * ldotn;
          const auto specularterm = distfactor * ks * nnh;
          ir = std::round(light_source.x *
                          (ambientterm + diffuseterm + specularterm));
          ig = std::round(light_source.y *
                          (ambientterm + diffuseterm + specularterm));
          ib = std::round(light_source.z *
                          (ambientterm + diffuseterm + specularterm));
        }

        pixel<int> p{center.i + x, center.j + y};
        point<color_t> rgb{ir, ig, ib};

        write_pixel(buffer, p, screen.width, rgb);
      }
    }
  }
}
} // namespace twenty
