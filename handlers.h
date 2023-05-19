#ifndef HANDLERS_H
#define HANDLERS_H

#define UNUSED __attribute__((unused))
#define PROMPT_MSG "dali<3 " 
#define BUFFER_SIZE 1024

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\

#endif
