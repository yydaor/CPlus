#ifndef FunctionPlus_h
#define FunctionPlus_h

#include "Prelude+.h"
#include "Type+.h"

/** Call - can be called like a function */

class {
  var (*call_with)(var,var);
} Call;

#define call(x, ...) call_with_ptr(x, (var[]){ __VA_ARGS__, (var)-1 })
var call_with_ptr(var self, var* args);
var call_with(var self, var args);

/*
** == Function ==
**
**  Simple Higher Level Functions
**  Must by of type (var(*)(var,var))
**  Can be constructed using "lambda"
**
**    lambda(hello_person, args) {
**      var name = cast(pop(args), String);
**      printf("Hello %s!", as_str(name) );
**      return None;
**    };
**
**    call(hello_person, $(String, "Dan"));
**
**
**	See 'Lambda+.h' for more functional tools.
**
*/

global var Function;

data {
  var type;
  var (*func)(var);
} FunctionData;

#define lambda(name, args) \
  auto var __LambdaPlus_##name(var); \
  var name = $(Function, __LambdaPlus_##name); \
  var __LambdaPlus_##name(var args)

/** Function_New(var self, var(*func)(var) ); */
var Function_New(var self, va_list* args);
var Function_Delete(var self);

var Function_Copy(var self);
void Function_Assign(var self, var obj);

var Function_Call(var self, var args);

instance(Function, New) = { sizeof(FunctionData), Function_New, Function_Delete };
instance(Function, Copy) = { Function_Copy };
instance(Function, Assign) = { Function_Assign };
instance(Function, Call) = { Function_Call };

#endif
