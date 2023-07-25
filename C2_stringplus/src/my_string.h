#ifndef SRC_MY_STRING_H
#define SRC_MY_STRING_H
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#define LINUX                                                                  \
  {                                                                            \
    "Success", "Operation not permitted", "No such file or directory",         \
        "No such process", "Interrupted system call", "Input/output error",    \
        "No such device or address", "Argument list too long",                 \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource temporarily unavailable", "Cannot allocate memory",          \
        "Permission denied", "Bad address", "Block device required",           \
        "Device or resource busy", "File exists", "Invalid cross-device link", \
        "No such device", "Not a directory", "Is a directory",                 \
        "Invalid argument", "Too many open files in system",                   \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain",                     \
        "Numerical result out of range", "Resource deadlock avoided",          \
        "File name too long", "No locks available",                            \
        "Function not implemented", "Directory not empty",                     \
        "Too many levels of symbolic links", "Unknown error 41",               \
        "No message of desired type", "Identifier removed",                    \
        "Channel number out of range", "Level 2 not synchronized",             \
        "Level 3 halted", "Level 3 reset", "Link number out of range",         \
        "Protocol driver not attached", "No CSI structure available",          \
        "Level 2 halted", "Invalid exchange", "Invalid request descriptor",    \
        "Exchange full", "No anode", "Invalid request code", "Invalid slot",   \
        "Unknown error 58", "Bad font file format", "Device not a stream",     \
        "No data available", "Timer expired", "Out of streams resources",      \
        "Machine is not on the network", "Package not installed",              \
        "Object is remote", "Link has been severed", "Advertise error",        \
        "Srmount error", "Communication error on send", "Protocol error",      \
        "Multihop attempted", "RFS specific error", "Bad message",             \
        "Value too large for defined data type", "Name not unique on network", \
        "File descriptor in bad state", "Remote address changed",              \
        "Can not access a needed shared library",                              \
        "Accessing a corrupted shared library",                                \
        ".lib section in a.out corrupted",                                     \
        "Attempting to link in too many shared libraries",                     \
        "Cannot exec a shared library directly",                               \
        "Invalid or incomplete multibyte or wide character",                   \
        "Interrupted system call should be restarted", "Streams pipe error",   \
        "Too many users", "Socket operation on non-socket",                    \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol", "Address already in use",  \
        "Cannot assign requested address", "Network is down",                  \
        "Network is unreachable", "Network dropped connection on reset",       \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available",                                           \
        "Transport endpoint is already connected",                             \
        "Transport endpoint is not connected",                                 \
        "Cannot send after transport endpoint shutdown",                       \
        "Too many references: cannot splice", "Connection timed out",          \
        "Connection refused", "Host is down", "No route to host",              \
        "Operation already in progress", "Operation now in progress",          \
        "Stale file handle", "Structure needs cleaning",                       \
        "Not a XENIX named type file", "No XENIX semaphores available",        \
        "Is a named type file", "Remote I/O error", "Disk quota exceeded",     \
        "No medium found", "Wrong medium type", "Operation canceled",          \
        "Required key not available", "Key has expired",                       \
        "Key has been revoked", "Key was rejected by service", "Owner died",   \
        "State not recoverable", "Operation not possible due to RF-kill",      \
        "Memory page has hardware error"                                       \
  }

#define APPLE                                                                  \
  {                                                                            \
    "Undefined error: 0", "Operation not permitted",                           \
        "No such file or directory", "No such process",                        \
        "Interrupted system call", "Input/output error",                       \
        "Device not configured", "Argument list too long",                     \
        "Exec format error", "Bad file descriptor", "No child processes",      \
        "Resource deadlock avoided", "Cannot allocate memory",                 \
        "Permission denied", "Bad address", "Block device required",           \
        "Resource busy", "File exists", "Cross-device link",                   \
        "Operation not supported by device", "Not a directory",                \
        "Is a directory", "Invalid argument", "Too many open files in system", \
        "Too many open files", "Inappropriate ioctl for device",               \
        "Text file busy", "File too large", "No space left on device",         \
        "Illegal seek", "Read-only file system", "Too many links",             \
        "Broken pipe", "Numerical argument out of domain", "Result too large", \
        "Resource temporarily unavailable", "Operation now in progress",       \
        "Operation already in progress", "Socket operation on non-socket",     \
        "Destination address required", "Message too long",                    \
        "Protocol wrong type for socket", "Protocol not available",            \
        "Protocol not supported", "Socket type not supported",                 \
        "Operation not supported", "Protocol family not supported",            \
        "Address family not supported by protocol family",                     \
        "Address already in use", "Can't assign requested address",            \
        "Network is down", "Network is unreachable",                           \
        "Network dropped connection on reset",                                 \
        "Software caused connection abort", "Connection reset by peer",        \
        "No buffer space available", "Socket is already connected",            \
        "Socket is not connected", "Can't send after socket shutdown",         \
        "Too many references: can't splice", "Operation timed out",            \
        "Connection refused", "Too many levels of symbolic links",             \
        "File name too long", "Host is down", "No route to host",              \
        "Directory not empty", "Too many processes", "Too many users",         \
        "Disc quota exceeded", "Stale NFS file handle",                        \
        "Too many levels of remote in path", "RPC struct is bad",              \
        "RPC version wrong", "RPC prog. not avail", "Program version wrong",   \
        "Bad procedure for program", "No locks available",                     \
        "Function not implemented", "Inappropriate file type or format",       \
        "Authentication error", "Need authenticator", "Device power is off",   \
        "Device error", "Value too large to be stored in data type",           \
        "Bad executable (or shared library)", "Bad CPU type in executable",    \
        "Shared library version mismatch", "Malformed Mach-o file",            \
        "Operation canceled", "Identifier removed",                            \
        "No message of desired type", "Illegal byte sequence",                 \
        "Attribute not found", "Bad message", "EMULTIHOP (Reserved)",          \
        "No message available on STREAM", "ENOLINK (Reserved)",                \
        "No STREAM resources", "Not a STREAM", "Protocol error",               \
        "STREAM ioctl timeout", "Operation not supported on socket",           \
        "Policy not found", "State not recoverable", "Previous owner died",    \
        "Interface output queue is full"                                       \
  }
#define my_NULL ((void *)0)
typedef long unsigned my_size_t;
typedef struct flags {
  int min;
  int plus;
  int space;
  int hash;
  int zero;
  int width;
  int aster;
  int dot;
  int accur;
  int h;
  int l;
  int L;
  int f_counter;
} my_flags;
// -------------standart part string-------
void *my_memchr(const void *str, int c, my_size_t n);
int my_memcmp(const void *str1, const void *str2, my_size_t n);
void *my_memcpy(void *dest, const void *src, my_size_t n);
void *my_memmove(void *dest, const void *src, my_size_t n);
void *my_memset(void *str, int c, my_size_t n);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, my_size_t n);
char *my_strchr(const char *str, int c);
int my_strcmp(const char *str1, const char *str2);
int my_strncmp(const char *str1, const char *str2, my_size_t n);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, my_size_t n);
my_size_t my_strcspn(const char *str1, const char *str2);
char *my_strerror(int errnum);
my_size_t my_strlen(const char *str);
char *my_strpbrk(const char *str1, const char *str2);
char *my_strrchr(const char *str, int c);
my_size_t my_strspn(const char *str1, const char *str2);
char *my_strstr(const char *haystack, const char *needle);
char *my_strtok(char *str, const char *delim);

//------------------SPRINTF-------------------
int my_sprintf(char *str, const char *format, ...);
int my_parse_flags(my_flags *flags, va_list args, char **c);
void my_choice_spec(my_flags *flags, va_list *args, char *temp_str, char *c,
                    int *res);
void my_flags_rebut(my_flags *flags);

//---help with my_parse_flags---
int my_isdig(char c);
int my_toint(char *temp);
void my_get_str(char *temp, char **c);
int my_str_dig(char **c);

//---help with my_choice_spec
void my_efg_default_val(my_flags *flags);
void my_pspec_c(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res);
void my_pspec_s(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res);
void my_pspec_d_i(my_flags *flags, va_list *args, char *c, char *temp_str,
                  int *res);
void my_pspec_u_x_X_o(my_flags *flags, va_list *args, char *c, char *temp_str,
                      int *res);
void my_pspec_p(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res);
void my_spec_n(my_flags *flags, va_list *args, int *res);
void my_pspec_f(my_flags *flags, long double temp_dou, char *c, char *temp_str,
                int *res);
int my_pspec_e(my_flags *flags, long double temp_dou, char *c, char *temp_str,
               int *res);
void my_pspec_g_G(my_flags *flags, long double temp_dou, char *c,
                  char *temp_str, int *res);
void my_add_to_str(char *temp_str, my_flags *flags, char *source, char *c,
                   int *res);

//---help with my_pspec_s---
void my_accur_s(my_flags *flags, char *long_chr);

//---help with my_pspec_d_i---
void my_llint_to_char(long long int n, char *res, int accur, int plus);

//---help with my_pspec_u_x_X_o and my_pspec_p---
void my_ullint_to_format_str(unsigned long long int n, char *c, char *res,
                             my_flags *flags);
void my_add_ulldig_to_str(unsigned long long int n, char *c, char *str, int *i);
char my_hex_to_chr(int hex, char *c);
void my_add_zero_to_str(char *res, int accur, int *j, int f_counter);

void check_spec_add_0xX(my_flags *flags, unsigned long long int temp_n, char *c,
                        char *str, int *i);
void my_reverse_str(char *res, char *str, int *i, int *j);

//---help with my_pspec_f, my_pspec_e, my_pspec_g---
long double my_getld_efg(my_flags *flags, va_list *args);
int check_nan_inf(char *temp_str, long double temp_dou);
void my_check_minus_ld(my_flags *flags, long double *temp_dou, char *all);
void my_f_right_ld(my_flags *flags, char *second_part, char *c,
                   long double *right, long double *left);
void my_pspec_fe_to_char(unsigned long long int n, char *c, char *res,
                         my_flags *flags, int cou_zero);
void my_f_left_ld(char *first_part, long double *left);
char my_esign_count_pow(long double *left, long double *right,
                        long double *temp_dou, int *cou_pow);
void my_del_zero(char *second_part);
void my_wrt_e_end(char *all, int j, char sign, char exp);

//-----Special string processing functions-----
void *my_to_upper(const char *str);
void *my_to_lower(const char *str);
void *my_insert(const char *src, const char *str, my_size_t start_index);
void *my_trim(const char *src, const char *trim_chars);
char *my_reverse(char *str);

//------------------SSCANF-------------------
int my_sscanf(const char *str, const char *format, ...);
int my_sparse_flags(my_flags *flags, char **c);
void my_scan_choice_spec(my_flags *flags, va_list *args, char **temp_str,
                         char *temp_part_str, char *c, int *res, int *res_n,
                         int *out_c);
void my_del_cont_chr_parse_input_str(char **str, int *res_n);

//---help with my_scan_choice_spec---
int my_parse_input_str(char **str, char *str_part, char *c, int len,
                       int *res_n);
void my_check_type_of_num_spec_i(char *str, char *c);
int my_check_nan_inf_feg(char **str, char *str_part, int *len);
void my_cp_part_shif_inp(char **str, char *str_part, char *c, int *len);
int check_chr_for_parse_dig(char str, char *c);
void my_check_parse_e(char **str, char *str_part, char *temp_c, int *temp_len);
void my_sspec_c(my_flags *flags, va_list *args, char *str, int *res,
                int *res_n);
void my_sspec_s(my_flags *flags, va_list *args, char *str, int *res,
                int *res_n);
void my_sspec_p(va_list *args, char *str, int *res, int *res_n);
void my_sspec_d_i(my_flags *flags, va_list *args, char *c, char *str, int *res,
                  int *res_n);
void my_sspec_ouxX(my_flags *flags, va_list *args, char *c, char *str, int *res,
                   int *res_n);
void my_sspec_efg(my_flags *flags, va_list *args, char *str, int *res,
                  int *res_n);

//---help with my_sspec_d_i---
long long my_str_to_ll(char *str, unsigned int base, int sign);

//---help with my_sspec_ouxX, my_sspec_p---
unsigned long long my_str_to_ull(char *str, unsigned int base);
int my_def_chr_str_to_ull(char str, int *temp);

//---help with my_sspec_efg---
long double my_str_to_ld(char *str);
int my_cal_mant_str_to_db(char **ptr_str, int *cou_before_dot);
int my_cal_frac_exp_str_to_db(int *mant_size, int cou_before_dot);
long double my_res_cal_str_to_db(char **ptr_str, int mant_size);
long long my_calc_part_str_to_db(int count, int *mant_size, char **ptr_str);
int my_cal_exp_str_to_db(char *ptr_str, int *exp_sign, int frac_exp);
long double my_cal_res_exp_str_to_db(int exp, int exp_sign, long double result);

#endif  // SRC_MY_STRING_H