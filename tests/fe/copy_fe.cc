//----------------------------  copy_fe.cc  ---------------------------
//    q_1.cc,v 1.1 2003/05/05 13:49:41 wolf Exp
//    Version:
//
//    Copyright (C) 2012 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    fuqher information on this license.
//
//----------------------------  copy_fe.cc  ---------------------------


// Fix a bug whereby calling a copy constructor of FESystem
// later resulted in a deallocation fault because the copy
// constructor copied pointers that were later freed twice.
//
// bug: default copy constructor can not copy a FESystem.
/*
#11 0x00007ffff5b5ba73 in dealii::deal_II_exceptions::internals::issue_error_assert_1<dealii::Subscriptor::ExcNoSubscriber> (
    file=0x7ffff6c658b0 "/scratch/branch_feqdg0/deal.II/source/base/subscriptor.cc", line=180,
    function=0x7ffff6c65b40 <dealii::Subscriptor::do_unsubscribe(char const*) const::__PRETTY_FUNCTI---Type <return> to continue, or q <return> to quit---
ON__> "void dealii::Subscriptor::do_unsubscribe(const char*) const",
    cond=0x7ffff6c65a8d "it->second > 0",
    exc_name=0x7ffff6c65a40 "ExcNoSubscriber(object_info->name(), name)", e=...)
    at /scratch/branch_feqdg0/deal.II/include/deal.II/base/exceptions.h:269
#12 0x00007ffff5b5b331 in dealii::Subscriptor::do_unsubscribe (this=0x657330,
    id=0x431b60 <typeinfo name for dealii::FESystem<2, 2>> "N6dealii8FESystemILi2ELi2EEE")
    at /scratch/branch_feqdg0/deal.II/source/base/subscriptor.cc:180
#13 0x00007ffff2995d23 in dealii::Subscriptor::unsubscribe (this=0x657330,
    id=0x431b60 <typeinfo name for dealii::FESystem<2, 2>> "N6dealii8FESystemILi2ELi2EEE")
    at /scratch/branch_feqdg0/deal.II/include/deal.II/base/subscriptor.h:286
#14 0x00007ffff40a8276 in dealii::FESystem<2, 2>::~FESystem (this=0x7fffffffd330,
    __in_chrg=<optimized out>) at /scratch/branch_feqdg0/deal.II/source/fe/fe_system.cc:332
#15 0x0000000000422463 in main () at copy_fe.cc:28
*/


#include "../tests.h"
#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_system.h>

int main ()
{
  initlog(__FILE__);
  {
    FE_Q<2> fe(1);
    {
      FE_Q<2> fe2(fe);
    }
    deallog << fe.base_element(0).dofs_per_cell << std::endl;
  }

  {
    FESystem<2> fe(FE_Q<2>(1),2);
    {
      FESystem<2> fe2(fe);
    }
    deallog << fe.base_element(0).dofs_per_cell << std::endl;
  }

  deallog << "OK" << std::endl;
}