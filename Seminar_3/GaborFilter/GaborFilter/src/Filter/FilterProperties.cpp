#include "Filter/FilterProperties.hpp"

#define DEFAULT_WAVELENGTH              1.0     // λ - lambda
#define DEFAULT_NORMAL_ORIENTATION      0.0     // θ - theta
#define DEFAULT_PHASE_OFFSET            0.0     // ψ - psi
#define DEFAULT_STANDARD_DEVIATION      1.0     // σ - sigma
#define DEFAULT_SPATIAL_ASPECT_RATIO    0.02    // γ - gamma

FilterProperties::FilterProperties() noexcept {
    deviation = DEFAULT_STANDARD_DEVIATION;
    orientation = DEFAULT_NORMAL_ORIENTATION;
    wavelength = DEFAULT_WAVELENGTH;
    ratio = DEFAULT_SPATIAL_ASPECT_RATIO;
    offset = DEFAULT_PHASE_OFFSET;
}
