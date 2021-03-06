/* Copyright 2015-2017 Philippe Tillet
* 
* Permission is hereby granted, free of charge, to any person obtaining 
* a copy of this software and associated documentation files 
* (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, 
* publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be 
* included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef ISAAC_DRIVER_KERNEL_H
#define ISAAC_DRIVER_KERNEL_H

#include "isaac/defines.h"
#include "isaac/driver/common.h"
#include "isaac/driver/program.h"
#include "isaac/driver/handle.h"
#include "isaac/value_scalar.h"

#include <memory>

namespace isaac
{

namespace driver
{

class Buffer;

// Kernel
class ISAACAPI Kernel: public has_handle_comparators<Kernel>
{
  friend class CommandQueue;
public:
  typedef Handle<cl_kernel, CUfunction> handle_type;

public:
  //Constructors
  Kernel(Program const & program, const char * name);
  //Accessors
  handle_type const & handle() const;
  //Arguments setters
  void setArg(unsigned int index, value_scalar const & scal);
  void setArg(unsigned int index, std::size_t size, void* ptr);
  void setArg(unsigned int index, Buffer const &);
  void setSizeArg(unsigned int index, std::size_t N);
  template<class T> void setArg(unsigned int index, T value) { setArg(index, sizeof(T), (void*)&value); }

private:
  backend_type backend_;
  unsigned int address_bits_;
  std::vector<std::shared_ptr<void> >  cu_params_store_;
  std::vector<void*>  cu_params_;
  handle_type h_;
};

}

}

#endif

