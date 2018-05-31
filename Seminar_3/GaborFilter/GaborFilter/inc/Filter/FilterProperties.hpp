#ifndef FILTER_FILTERPROPERTIES_HPP
#define FILTER_FILTERPROPERTIES_HPP

struct FilterProperties {
    double deviation;
    double orientation;
    double wavelength;
    double ratio;
    double offset;

    FilterProperties() noexcept;
};

#endif  // !FILTER_FILTERPROPERTIES_HPP
