// ---------------------------------------------------------------------
//
// Copyright (C) 1999 - 2015 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

#ifndef dealii__tensor_function_templates_h
#define dealii__tensor_function_templates_h

#include <deal.II/base/tensor_function.h>
#include <deal.II/base/tensor.h>
#include <deal.II/lac/vector.h>

#include <vector>
#include <cmath>

DEAL_II_NAMESPACE_OPEN


template <int rank, int dim, typename Number>
TensorFunction<rank, dim, Number>::TensorFunction (const Number initial_time)
  :
  FunctionTime<Number> (initial_time)
{}


template <int rank, int dim, typename Number>
TensorFunction<rank, dim, Number>::~TensorFunction ()
{}


template <int rank, int dim, typename Number>
typename TensorFunction<rank, dim, Number>::value_type
TensorFunction<rank, dim, Number>::value (const Point<dim> &) const
{
  Assert (false, ExcPureFunctionCalled());
  return Tensor<rank,dim, Number>();
}


template <int rank, int dim, typename Number>
void
TensorFunction<rank, dim, Number>::value_list (
  const std::vector<Point<dim> > &points,
  std::vector<value_type>        &values) const
{
  Assert (values.size() == points.size(),
          ExcDimensionMismatch(values.size(), points.size()));

  for (unsigned int i=0; i<points.size(); ++i)
    values[i]  = this->value (points[i]);
}


template <int rank, int dim, typename Number>
typename TensorFunction<rank, dim, Number>::gradient_type
TensorFunction<rank, dim, Number>::gradient (const Point<dim> &) const
{
  Assert (false, ExcPureFunctionCalled());
  return Tensor<rank+1,dim, Number>();
}


template <int rank, int dim, typename Number>
void
TensorFunction<rank, dim, Number>::gradient_list (
  const std::vector<Point<dim> >   &points,
  std::vector<gradient_type> &gradients) const
{
  Assert (gradients.size() == points.size(),
          ExcDimensionMismatch(gradients.size(), points.size()));

  for (unsigned int i=0; i<points.size(); ++i)
    gradients[i] = gradient(points[i]);
}



template <int rank, int dim, typename Number>
ConstantTensorFunction<rank, dim, Number>::ConstantTensorFunction (
  const Tensor<rank, dim, Number> &value,
  const Number initial_time)
  :
  TensorFunction<rank, dim, Number> (initial_time),
  _value(value)
{}


template <int rank, int dim, typename Number>
ConstantTensorFunction<rank, dim, Number>::~ConstantTensorFunction ()
{}


template <int rank, int dim, typename Number>
typename TensorFunction<rank, dim, Number>::value_type
ConstantTensorFunction<rank, dim, Number>::value (
  const Point<dim> &/*point*/) const
{
  return _value;
}


template <int rank, int dim, typename Number>
void
ConstantTensorFunction<rank, dim, Number>::value_list (
  const std::vector<Point<dim> > &points,
  std::vector<typename TensorFunction<rank, dim, Number>::value_type> &values) const
{
  (void)points;
  Assert (values.size() == points.size(),
          ExcDimensionMismatch(values.size(), points.size()));

  for (unsigned int i=0; i<values.size(); ++i)
    values[i]  = _value;
}


template <int rank, int dim, typename Number>
typename TensorFunction<rank, dim, Number>::gradient_type
ConstantTensorFunction<rank, dim, Number>::gradient (const Point<dim> &) const
{
  static const Tensor<rank+1, dim, Number> zero;

  return zero;
}


template <int rank, int dim, typename Number>
void
ConstantTensorFunction<rank, dim, Number>::gradient_list (
  const std::vector<Point<dim> >   &points,
  std::vector<typename TensorFunction<rank, dim, Number>::gradient_type> &gradients) const
{
  (void)points;
  Assert (gradients.size() == points.size(),
          ExcDimensionMismatch(gradients.size(), points.size()));

  static const Tensor<rank+1, dim, Number> zero;

  for (unsigned int i=0; i<gradients.size(); ++i)
    gradients[i] = zero;
}



template <int rank, int dim, typename Number>
ZeroTensorFunction<rank, dim, Number>::ZeroTensorFunction (const Number initial_time)
  :
  ConstantTensorFunction<rank, dim, Number> (dealii::Tensor<rank, dim, Number>(), initial_time)
{}


DEAL_II_NAMESPACE_CLOSE

#endif /* dealii__tensor_function_templates_h */