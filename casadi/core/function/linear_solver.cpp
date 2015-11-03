/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "linear_solver_internal.hpp"

using namespace std;
namespace casadi {

  LinearSolver::LinearSolver() {
  }

  LinearSolverInternal* LinearSolver::operator->() {
    return static_cast<LinearSolverInternal*>(Function::operator->());
  }

  const LinearSolverInternal* LinearSolver::operator->() const {
    return static_cast<const LinearSolverInternal*>(Function::operator->());
  }

  void LinearSolver::prepare() {
    (*this)->prepare();
  }

  void LinearSolver::solve(double* x, int nrhs, bool transpose) {
    (*this)->solve(x, nrhs, transpose);
  }

  void LinearSolver::solve(bool transpose) {
    (*this)->solve(transpose);
  }

  MX LinearSolver::solve(const MX& A, const MX& B, bool transpose) {
    return (*this)->solve(A, B, transpose);
  }

  bool LinearSolver::test_cast(const SharedObjectNode* ptr) {
    return dynamic_cast<const LinearSolverInternal*>(ptr)!=0;
  }

  void LinearSolver::spSolve(bvec_t* X, const bvec_t* B, bool transpose) const {
    (*this)->spSolve(X, B, transpose);
  }

  void LinearSolver::spSolve(DMatrix& X, const DMatrix& B, bool transpose) const {
    (*this)->spSolve(X, B, transpose);
  }

  LinearSolver::LinearSolver(const std::string& name, const std::string& solver,
                             const Sparsity& sp, int nrhs, const Dict& opts) {
    if (solver=="none") {
      assignNode(new LinearSolverInternal(name, sp, nrhs));
    } else {
      assignNode(LinearSolverInternal::getPlugin(solver).creator(name, sp, nrhs));
    }
    setOption(opts);
    init();
  }

  LinearSolver::LinearSolver(const std::string& name, const std::string& solver,
                             const Sparsity& sp, const Dict& opts) {
    if (solver=="none") {
      assignNode(new LinearSolverInternal(name, sp, 1));
    } else {
      assignNode(LinearSolverInternal::getPlugin(solver).creator(name, sp, 1));
    }
    setOption(opts);
    init();
  }

  bool LinearSolver::hasPlugin(const std::string& name) {
    return LinearSolverInternal::hasPlugin(name);
  }

  void LinearSolver::loadPlugin(const std::string& name) {
    LinearSolverInternal::loadPlugin(name);
  }

  std::string LinearSolver::doc(const std::string& name) {
    return LinearSolverInternal::getPlugin(name).doc;
  }

  Sparsity LinearSolver::getFactorizationSparsity(bool transpose) const {
    return (*this)->getFactorizationSparsity(transpose);
  }

  DMatrix LinearSolver::getFactorization(bool transpose) const {
    return (*this)->getFactorization(transpose);
  }

  void LinearSolver::solveL(double* x, int nrhs, bool transpose) {
    return (*this)->solveL(x, nrhs, transpose);
  }

} // namespace casadi
