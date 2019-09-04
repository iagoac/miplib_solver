#include "solver.hpp"

void Solver::initialize(void) {
  #ifdef DEBUG
    std::cout << "Reading the .mps file: ";
  #endif

  /* If debug is not defined
  then do not send the CPLEX
  output to the std::out  */
  #ifndef DEBUG // Please, be atent 'ifndef'
    this->_cplex.setOut(this->_env.getNullStream());
    this->_cplex.setWarning(this->_env.getNullStream());
  #endif

  /* Reads the .mps file */
  this->_obj = IloObjective(this->_env);
  this->_var = IloNumVarArray(this->_env);
  this->_rng = IloRangeArray(this->_env);

  /* Initialize the model with the read values */
  try {
    this->_cplex.importModel(_model, this->_args->get<std::string>("-input").c_str(), _obj, _var, _rng);
  } catch (...) {
    std::cout << "Instance does not exists!" << std::endl;
    exit(1);
  }

  /* Defines the vectors that store
  the lower and the upper coefficients */
  this->num_var = this->_var.getSize();
  this->num_constraints = this->_rng.getSize();

  this->set_cplex_params();

  #ifdef DEBUG
    std::cout << "Done!" << std::endl;
  #endif

  #ifdef DEBUG
    /* Then, export the CPLEX model into file mymodel.lp */
    this->_cplex.exportModel("model.lp");
  #endif
}

void Solver::set_cplex_params(void) {
  this->_cplex.setParam(IloCplex::TiLim, this->_args->get<int>("-time"));
  this->_cplex.setParam(IloCplex::MIPEmphasis, this->_args->get<int>("-switch"));
  this->_cplex.setParam(IloCplex::Threads, 1);
  // this->_cplex.setParam(IloCplex::Cliques, -1);
  // this->_cplex.setParam(IloCplex::Covers, -1);
  // this->_cplex.setParam(IloCplex::DisjCuts, -1);
  // this->_cplex.setParam(IloCplex::FlowCovers, -1);
  // this->_cplex.setParam(IloCplex::FlowPaths, -1);
  // this->_cplex.setParam(IloCplex::GUBCovers, -1);
  // this->_cplex.setParam(IloCplex::ImplBd, -1);
  // this->_cplex.setParam(IloCplex::MIRCuts, -1);
  // this->_cplex.setParam(IloCplex::FracCuts, -1);
  // this->_cplex.setParam(IloCplex::ZeroHalfCuts, -1);
  // this->_cplex.setParam(IloCplex::MIPSearch, CPX_MIPSEARCH_TRADITIONAL);
  // this->_cplex.setParam(IloCplex::MIPInterval, 100);
  // this->_cplex.setParam(IloCplex::PreInd, 0);
  // this->_cplex.setParam(IloCplex::AggInd, 0);
  // this->_cplex.setParam(IloCplex::HeurFreq, -1);
  // this->_cplex.setParam(IloCplex::EpAGap, 0);
}
