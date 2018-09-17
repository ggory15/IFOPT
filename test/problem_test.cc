#define BOOST_TEST_MODULE IFOPT
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

#include <ifopt_core/problem.h>
#include "ifopt/test_vars_constr_cost.h"
#include "iostream"

using namespace ifopt;
using namespace std;

BOOST_AUTO_TEST_CASE(variable)
{
  Problem nlp;
  nlp.AddVariableSet(std::make_shared<ExVariables>("var_set0"));
  nlp.AddVariableSet(std::make_shared<ExVariables>("var_set1"));

  cout << "check varialbe number" << endl;
  BOOST_CHECK_EQUAL(nlp.GetNumberOfOptimizationVariables(), 4);
}

BOOST_AUTO_TEST_CASE(GetBoundsOnOptimizationVariables)
{
  Problem nlp;
  nlp.AddVariableSet(std::make_shared<ExVariables>("var_set0"));
  nlp.AddVariableSet(std::make_shared<ExVariables>("var_set1"));

  auto bounds = nlp.GetBoundsOnOptimizationVariables();

  cout << "check bound size" << endl;

  BOOST_CHECK_EQUAL(2+2, bounds.size());
 
  // var_set0
  BOOST_CHECK_EQUAL(-1.0, bounds.at(0).lower_);
  BOOST_CHECK_EQUAL(+1.0, bounds.at(0).upper_);
  BOOST_CHECK_EQUAL(-inf, bounds.at(1).lower_);
  BOOST_CHECK_EQUAL(+inf, bounds.at(1).upper_);

  // var_set1
  BOOST_CHECK_EQUAL(-1.0, bounds.at(2).lower_);
  BOOST_CHECK_EQUAL(+1.0, bounds.at(2).upper_);
  BOOST_CHECK_EQUAL(-inf, bounds.at(3).lower_);
  BOOST_CHECK_EQUAL(+inf, bounds.at(3).upper_);
}

BOOST_AUTO_TEST_CASE(GetVariableValues)
{

  cout << "check GetVariableValues" << endl;
 auto var_set0 = std::make_shared<ExVariables>("var_set0");
  var_set0->SetVariables(Eigen::Vector2d(0.1, 0.2));

  auto var_set1 = std::make_shared<ExVariables>("var_set1");
  var_set1->SetVariables(Eigen::Vector2d(0.3, 0.4));

  Problem nlp;
  nlp.AddVariableSet(var_set0);
  nlp.AddVariableSet(var_set1);

  Eigen::VectorXd x = nlp.GetVariableValues();
  BOOST_CHECK_EQUAL(0.1, x(0));
  BOOST_CHECK_EQUAL(0.2, x(1));
  BOOST_CHECK_EQUAL(0.3, x(2));
  BOOST_CHECK_EQUAL(0.4, x(3));
}
BOOST_AUTO_TEST_CASE(GetNumberOfConstraints)
{

  cout << "check GetNumberOfConstraints" << endl;
  Problem nlp;
  nlp.AddConstraintSet(std::make_shared<ExConstraint>("constraint1"));

  // add same constraints again for testing.
  // notice how the Jacobian calculation inside ExConstraint-class remains the
  //same - the full Jacobian is stitched together accordingly.
  nlp.AddConstraintSet(std::make_shared<ExConstraint>("constraint2"));

  BOOST_CHECK_EQUAL(1+1, nlp.GetNumberOfConstraints());
}

