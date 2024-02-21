
file(GLOB_RECURSE src_f CONFIGURE_DEPENDS
     "*.hpp"
     "*.cpp"
     "*.h"
)

target_sources(test PRIVATE
    ${src_f}
)
