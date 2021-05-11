#ifndef COMMON_ERROR_H_
#define COMMON_ERROR_H_

void error_exit_errno(const char * msg, int _errno);

void error_exit_msg(const char * msg);

#endif  // COMMON_ERROR_H_
