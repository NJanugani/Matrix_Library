#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T12:29:32
#
#-------------------------------------------------

QT          += opengl

# DO NOT CHANGE THIS !!
CONFIG      += c++14

TARGET      = glcomputes2
TEMPLATE    = lib

DEFINES     += GLCOMPUTES2_LIBRARY

SOURCES     += \
    GLComputes.cpp \
    Exemplar.cpp \
    Shader.cpp \
    externs/glm/detail/dummy.cpp \
    externs/glm/detail/glm.cpp

HEADERS     += \
    exports.hpp \
    GLComputes.hpp \
    Exemplar.hpp \
    Shader.hpp \
    Defines.hpp \
    externs/glm/detail/_features.hpp \
    externs/glm/detail/_fixes.hpp \
    externs/glm/detail/_noise.hpp \
    externs/glm/detail/_swizzle.hpp \
    externs/glm/detail/_swizzle_func.hpp \
    externs/glm/detail/_vectorize.hpp \
    externs/glm/detail/func_common.hpp \
    externs/glm/detail/func_exponential.hpp \
    externs/glm/detail/func_geometric.hpp \
    externs/glm/detail/func_integer.hpp \
    externs/glm/detail/func_matrix.hpp \
    externs/glm/detail/func_packing.hpp \
    externs/glm/detail/func_trigonometric.hpp \
    externs/glm/detail/func_vector_relational.hpp \
    externs/glm/detail/precision.hpp \
    externs/glm/detail/setup.hpp \
    externs/glm/detail/type_float.hpp \
    externs/glm/detail/type_gentype.hpp \
    externs/glm/detail/type_half.hpp \
    externs/glm/detail/type_int.hpp \
    externs/glm/detail/type_mat.hpp \
    externs/glm/detail/type_mat2x2.hpp \
    externs/glm/detail/type_mat2x3.hpp \
    externs/glm/detail/type_mat2x4.hpp \
    externs/glm/detail/type_mat3x2.hpp \
    externs/glm/detail/type_mat3x3.hpp \
    externs/glm/detail/type_mat3x4.hpp \
    externs/glm/detail/type_mat4x2.hpp \
    externs/glm/detail/type_mat4x3.hpp \
    externs/glm/detail/type_mat4x4.hpp \
    externs/glm/detail/type_vec.hpp \
    externs/glm/detail/type_vec1.hpp \
    externs/glm/detail/type_vec2.hpp \
    externs/glm/detail/type_vec3.hpp \
    externs/glm/detail/type_vec4.hpp \
    externs/glm/gtc/bitfield.hpp \
    externs/glm/gtc/color_space.hpp \
    externs/glm/gtc/constants.hpp \
    externs/glm/gtc/epsilon.hpp \
    externs/glm/gtc/integer.hpp \
    externs/glm/gtc/matrix_access.hpp \
    externs/glm/gtc/matrix_integer.hpp \
    externs/glm/gtc/matrix_inverse.hpp \
    externs/glm/gtc/matrix_transform.hpp \
    externs/glm/gtc/noise.hpp \
    externs/glm/gtc/packing.hpp \
    externs/glm/gtc/quaternion.hpp \
    externs/glm/gtc/random.hpp \
    externs/glm/gtc/reciprocal.hpp \
    externs/glm/gtc/round.hpp \
    externs/glm/gtc/type_aligned.hpp \
    externs/glm/gtc/type_precision.hpp \
    externs/glm/gtc/type_ptr.hpp \
    externs/glm/gtc/ulp.hpp \
    externs/glm/gtc/vec1.hpp \
    externs/glm/gtx/associated_min_max.hpp \
    externs/glm/gtx/bit.hpp \
    externs/glm/gtx/closest_point.hpp \
    externs/glm/gtx/color_space.hpp \
    externs/glm/gtx/color_space_YCoCg.hpp \
    externs/glm/gtx/common.hpp \
    externs/glm/gtx/compatibility.hpp \
    externs/glm/gtx/component_wise.hpp \
    externs/glm/gtx/dual_quaternion.hpp \
    externs/glm/gtx/euler_angles.hpp \
    externs/glm/gtx/extend.hpp \
    externs/glm/gtx/extended_min_max.hpp \
    externs/glm/gtx/fast_exponential.hpp \
    externs/glm/gtx/fast_square_root.hpp \
    externs/glm/gtx/fast_trigonometry.hpp \
    externs/glm/gtx/gradient_paint.hpp \
    externs/glm/gtx/handed_coordinate_space.hpp \
    externs/glm/gtx/hash.hpp \
    externs/glm/gtx/integer.hpp \
    externs/glm/gtx/intersect.hpp \
    externs/glm/gtx/io.hpp \
    externs/glm/gtx/log_base.hpp \
    externs/glm/gtx/matrix_cross_product.hpp \
    externs/glm/gtx/matrix_decompose.hpp \
    externs/glm/gtx/matrix_interpolation.hpp \
    externs/glm/gtx/matrix_major_storage.hpp \
    externs/glm/gtx/matrix_operation.hpp \
    externs/glm/gtx/matrix_query.hpp \
    externs/glm/gtx/matrix_transform_2d.hpp \
    externs/glm/gtx/mixed_product.hpp \
    externs/glm/gtx/norm.hpp \
    externs/glm/gtx/normal.hpp \
    externs/glm/gtx/normalize_dot.hpp \
    externs/glm/gtx/number_precision.hpp \
    externs/glm/gtx/optimum_pow.hpp \
    externs/glm/gtx/orthonormalize.hpp \
    externs/glm/gtx/perpendicular.hpp \
    externs/glm/gtx/polar_coordinates.hpp \
    externs/glm/gtx/projection.hpp \
    externs/glm/gtx/quaternion.hpp \
    externs/glm/gtx/range.hpp \
    externs/glm/gtx/raw_data.hpp \
    externs/glm/gtx/rotate_normalized_axis.hpp \
    externs/glm/gtx/rotate_vector.hpp \
    externs/glm/gtx/scalar_multiplication.hpp \
    externs/glm/gtx/scalar_relational.hpp \
    externs/glm/gtx/simd_mat4.hpp \
    externs/glm/gtx/simd_quat.hpp \
    externs/glm/gtx/simd_vec4.hpp \
    externs/glm/gtx/spline.hpp \
    externs/glm/gtx/std_based_type.hpp \
    externs/glm/gtx/string_cast.hpp \
    externs/glm/gtx/transform.hpp \
    externs/glm/gtx/transform2.hpp \
    externs/glm/gtx/type_aligned.hpp \
    externs/glm/gtx/type_trait.hpp \
    externs/glm/gtx/vector_angle.hpp \
    externs/glm/gtx/vector_query.hpp \
    externs/glm/gtx/wrap.hpp \
    externs/glm/simd/common.h \
    externs/glm/simd/exponential.h \
    externs/glm/simd/geometric.h \
    externs/glm/simd/integer.h \
    externs/glm/simd/matrix.h \
    externs/glm/simd/packing.h \
    externs/glm/simd/platform.h \
    externs/glm/simd/trigonometric.h \
    externs/glm/simd/vector_relational.h \
    externs/glm/common.hpp \
    externs/glm/exponential.hpp \
    externs/glm/ext.hpp \
    externs/glm/fwd.hpp \
    externs/glm/geometric.hpp \
    externs/glm/glm.hpp \
    externs/glm/integer.hpp \
    externs/glm/mat2x2.hpp \
    externs/glm/mat2x3.hpp \
    externs/glm/mat2x4.hpp \
    externs/glm/mat3x2.hpp \
    externs/glm/mat3x3.hpp \
    externs/glm/mat3x4.hpp \
    externs/glm/mat4x2.hpp \
    externs/glm/mat4x3.hpp \
    externs/glm/mat4x4.hpp \
    externs/glm/matrix.hpp \
    externs/glm/packing.hpp \
    externs/glm/trigonometric.hpp \
    externs/glm/vec2.hpp \
    externs/glm/vec3.hpp \
    externs/glm/vec4.hpp \
    externs/glm/vector_relational.hpp

DEFINES     *= QT_USE_QSTRINGBUILDER
INCLUDEPATH += $$(GL_INCLUDES)
INCLUDEPATH += $$PWD/externs
LIBS += -L$$(GL_LIBS)/Lib -lEGL -lGLESv2

QMAKE_CXXFLAGS  += -isystem $$PWD/externs

INCLUDEPATH     += $$(GL_INCLUDES)/ $$(GLM)/
LIBS            += -L$$(GL_LIBS)/Lib -lEGL -lGLESv2


unix {
    target.path = /usr/lib
    INSTALLS += target
    QMAKE_CXXFLAGS += -std=c++14
}

mac {
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS  += -std=c++14
    QMAKE_MACOSX_DEPLOYMENT_TARGET=10.9
}

DISTFILES += \
    shaders/exemplars/vertex.glsl \
    shaders/exemplars/fragment.glsl

RESOURCES += \
    assets.qrc
