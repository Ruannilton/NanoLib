#ifndef _STL_CORE_H
#define _STL_CORE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define __prefix stl_
#define __base_name core

#define _____concat2(A, B) A##B
#define _____concat(A, B) _____concat2(A, B)

#define __stl_fn(type, name, fn) _____concat(_____concat(_____concat(__prefix, _____concat(_____concat(name, _), type)), _), fn)
#define __stl_t(type, name) _____concat(_____concat(_____concat(name, _), type), _t)

#define __unique(name) _____concat(name, _____concat(_____concat(_____concat(_, _____concat(__prefix, __base_name)), __LINE__), __COUNTER__))

#endif