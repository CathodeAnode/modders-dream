module;
#include <Eigen/Dense>
export module md.math;

namespace md::math {

template <typename Type, int Size>
using Vector = Eigen::Vector<Type, Size>;

template <typename Type>
using Vector2 = Eigen::Vector2<Type>;
template <typename Type>
using Vector3 = Eigen::Vector3<Type>;
template <typename Type>
using Vector4 = Eigen::Vector4<Type>;

using Vector2f = Eigen::Vector2f;
using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;

using Vector2d = Eigen::Vector2d;
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;

using Vector2i = Eigen::Vector2i;
using Vector3i = Eigen::Vector3i;
using Vector4i = Eigen::Vector4i;

template <typename Scalar, int Rows, int Cols>
using Matrix = Eigen::Matrix<Scalar, Rows, Cols>;

template <typename Type>
using Matrix2 = Eigen::Matrix2<Type>;
template <typename Type>
using Matrix3 = Eigen::Matrix3<Type>;
template <typename Type>
using Matrix4 = Eigen::Matrix4<Type>;

using Matrix2f = Eigen::Matrix2f;
using Matrix3f = Eigen::Matrix3f;
using Matrix4f = Eigen::Matrix4f;

using Matrix2d = Eigen::Matrix2d;
using Matrix3d = Eigen::Matrix3d;
using Matrix4d = Eigen::Matrix4d;

using Quaternionf = Eigen::Quaternionf;
using Quaterniond = Eigen::Quaterniond;

} // namespace md::math
