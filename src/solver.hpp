#ifndef SOLVER_HH_
#define SOLVER_HH_

#include <random>    // mtrand
#include <limits>    // std::numeric_limits
#include <algorithm> // std::min
#include "cplex_includes.hpp"
#include "argparse.hpp"
#include "cxxtimer.hpp"

class Solver {
  void set_theta(void);
  /* Model building methods */
  void set_cplex_params(void);

public:
  /* Class variables declaration */
  Args *_args;      // The arguments class

  /* CPLEX common structures */
  IloEnv _env;
  IloModel _model;
  IloCplex _cplex;

  /* CPLEX variables that read the .mps file */
  IloObjective _obj;    // objective function
  IloNumVarArray _var;  // variables array
  IloRangeArray _rng;   // constraints array

  /* The number of variables and
  constraints in the .mps file*/
  int num_var;
  int num_constraints;

  /* Arrays that store the
  upper value and lower value
  of each variable coefficient */
  IloNumArray lValue, uValue;

  /* Execution timer */
  cxxtimer::Timer timer;

  /* Class constructor */
  Solver (Args* arg)
  :_args(arg), _model(this->_env), _cplex(this->_model) {
    this->initialize();
  }

  /* Method used by the constructor
  calls other methods to initialize
  the mathematical model         */
  void initialize(void);

  void solve(void) { this->_cplex.solve(); }
};

#endif // SOLVER_HH_
