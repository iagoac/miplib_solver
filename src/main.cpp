#include <stdio.h>
#include <stdlib.h>
#include "solver.hpp"

int main(int argc, char* const* argv) {
  /* Declare the arguments parser */
  ArgParse argparser;

  /* Get the arguments */
  argparser.add("-input", ArgParse::Opt::req);
  argparser.add("-time", ArgParse::Opt::req);
  argparser.add("-switch", ArgParse::Opt::req);

  Args args = argparser.parse(argc, argv);

  if (args.get<int>("-switch") < 0 || args.get<int>("-switch") > 4) {
    std::cout << "terminate called after throwing an instance of 'wrongParameterValue'" << std::endl;
    std::cout << "  what():  Param '-switch' need to be between 0 and 4." << std::endl;
    exit(1);
  }

  /* Debug initial message */
  #ifdef DEBUG
    std::cout << "Debug is activated!" << std::endl;
    std::cout << "Solving instance " << args.get<std::string>("-input") << std::endl;
  #endif

  /* Solver constructor
  it reads the .mps file */
  Solver solver(&args);

  #ifdef DEBUG
    std::cout << "Done!" << std::endl;
  #endif

  /* Initializing the time counter */
  solver.timer.start();

  solver.solve();

  solver.timer.stop();

  std::cout << args.get<std::string>("-input") << ",";
  std::cout << args.get<int>("-time") << ",";
  std::cout << args.get<int>("-switch") << ",";
  std::cout << solver.num_var << ",";
  std::cout << solver.num_constraints << ",";
  if (solver._cplex.getStatus() != IloAlgorithm::Infeasible) {
    std::cout << solver._cplex.getBestObjValue() << ",";
    std::cout << solver._cplex.getObjValue() << ",";
    std::cout << solver._cplex.getMIPRelativeGap()*100 << ",";
  } else {
    std::cout << "0,0,0,";
  }
  std::cout << solver._cplex.getTime() << ",";
  std::cout << solver._cplex.getStatus() << std::endl;

  return (0);
}
