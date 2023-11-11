#pragma once

#ifdef __cplusplus
extern "C" {
  int yyparse();
}
#else
int yyparse();
#endif

