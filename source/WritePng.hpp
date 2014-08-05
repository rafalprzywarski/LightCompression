#pragma once
#include "Image.hpp"
#include <boost/gil/extension/io/png_dynamic_io.hpp>

namespace lc
{

inline void writePng(const Image& img, const std::string& filename)
{
    boost::gil::png_write_view(filename, const_view(img));
}

}
