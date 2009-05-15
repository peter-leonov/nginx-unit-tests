#include "testing.h"
#include <assert.h>


// emulating nginx
#define _NGX_CORE_H_INCLUDED_

#include <ngx_errno.h>

// typedef unsigned char u_char;
typedef struct ngx_module_s      ngx_module_t;
typedef struct ngx_conf_s        ngx_conf_t;
typedef struct ngx_cycle_s       ngx_cycle_t;
typedef struct ngx_pool_s        ngx_pool_t;
typedef struct ngx_chain_s       ngx_chain_t;
typedef struct ngx_log_s         ngx_log_t;
typedef struct ngx_array_s       ngx_array_t;
typedef struct ngx_open_file_s   ngx_open_file_t;
typedef struct ngx_command_s     ngx_command_t;
typedef struct ngx_file_s        ngx_file_t;
typedef struct ngx_event_s       ngx_event_t;
typedef struct ngx_connection_s  ngx_connection_t;

typedef int                      ngx_fd_t;

void
ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,	const char *fmt, ...)
{ abort(); }

struct ngx_cycle_t
{
	ngx_log_t *log;
} ngx_cycle;


#include <ngx_palloc.h>
#include <ngx_string.h>


ngx_uint_t  ngx_pagesize;
ngx_uint_t  ngx_pagesize_shift;
ngx_uint_t  ngx_cacheline_size;

static int __testing_no_memory = 0;

void *
ngx_alloc(size_t size, ngx_log_t *log)
{
	// printf("%s %d\n", "ngx_alloc hook", __testing_no_memory);
	return __testing_no_memory ? NULL : malloc(size);
}









#define STRING_OF_100_CHARS "---------0---------1---------2---------3---------4---------5---------6---------7---------8---------9"


void fields_t ()
{
	ngx_str_t str;
	str.len = 0;
	str.data = NULL;
	
	assert(str.len == 0 && str.data == NULL);
}



// u_char *
// ngx_cpystrn(u_char *dst, u_char *src, size_t n)
// 
// If n == 0 leaves dst unchanged (desn't even set the trailing '\0') and returns dst value (the same pointer).
// If n > 0 copies u_chars from src to dst, stops copying when n u_chars are copied
// or if '\0' character is met in src; then adds trailing '\0' to the end of dst; afterwards
// returns a pointer to the last copied u_char (it will always be the trailing '\0' of dst).
// Usage: *res = ngx_cpystrn(dst, src, bytes_number_of_dst); size_t copied = res - dst;


void ngx_cpystrn_with_small_string_t ()
{
	u_char *dst = malloc(20);
	u_char *src = (u_char*)"test";
	
	u_char *res = ngx_cpystrn(dst, src, 20);
	
	// check copy
	assert(dst[0] == 't' && dst[1] == 'e' && dst[2] == 's' && dst[3] == 't' && dst[4] == '\0');
	
	// result must be a not null pointer
	assert(res != NULL);
	
	// res must point to the trailing null
	assert(res - dst == sizeof("test")-1);
	assert(*res == '\0');
}

void ngx_cpystrn_with_bigger_string_t ()
{
	u_char *dst = malloc(3);
	u_char *src = (u_char*)"test";
	
	u_char *res = ngx_cpystrn(dst, src, 3);
	
	// check copy
	assert(dst[0] == 't' && dst[1] == 'e' && dst[2] == '\0');
	
	// res must point to the trailing null (the last byte of dst)
	assert(res - dst == 2);
	assert(*res == '\0');
}


void ngx_cpystrn_with_exact_string_t ()
{
	u_char *dst = malloc(5);
	u_char *src = (u_char*)"test";
	
	u_char *res = ngx_cpystrn(dst, src, 5);
	
	// check copy
	assert(dst[0] == 't' && dst[1] == 'e' && dst[2] == 's' && dst[3] == 't' && dst[4] == '\0');
	
	// res must point to the trailing null
	assert(res - dst == sizeof("test")-1);
	assert(*res == '\0');
}


void ngx_cpystrn_with_dst_length_eq_0_t ()
{
	u_char *dst = malloc(5);
	u_char *src = (u_char*)"test";
	
	// fill the dst
	dst[0] = 'A'; dst[1] = 'B'; dst[2] = 'C'; dst[3] = 'D'; dst[4] = '\0';
	
	u_char *res = ngx_cpystrn(dst, src, 0);
	
	// check dst (must be unchanged)
	assert(dst[0] == 'A' && dst[1] == 'B' && dst[2] == 'C' && dst[3] == 'D' && dst[4] == '\0');
	
	// res must point to the dst
	assert(res == dst);
}


// void ngx_cpystrn_with_dst_length_less_0_t ()
// {
// 	u_char *dst = malloc(5);
// 	u_char *src = (u_char*)"test";
// 	
// 	// fill the dst
// 	dst[0] = 'A'; dst[1] = 'B'; dst[2] = 'C'; dst[3] = 'D'; dst[4] = '\0';
// 	
// 	u_char *res = ngx_cpystrn(dst, src, -1);
// 	
// 	// check dst (must be unchanged)
// 	assert(dst[0] == 'A' && dst[1] == 'B' && dst[2] == 'C' && dst[3] == 'D' && dst[4] == '\0');
// 	
// 	// res must point to the dst
// 	assert(res == dst);
// }

void ngx_cpystrn_with_dst_length_less_0_t ()
{
	u_char *dst = malloc(5);
	u_char *src = (u_char*)"test";
	
	// will copy very many chars, depends on what the -1 will be translated in (likeley 4294967295 on a leopard mac)
	// printf("%uz\n", (size_t) -1);
	u_char *res = ngx_cpystrn(dst, src, -1);
	
	// check copy
	assert(dst[0] == 't' && dst[1] == 'e' && dst[2] == 's' && dst[3] == 't' && dst[4] == '\0');
	
	// res must point to the last char
	assert(res == &dst[4]);
}



// void
// ngx_strlow(u_char *dst, u_char *src, size_t n)
// Copies all n chars from src to dst without matter the '\0' char.
// Every char is converted to lowercase. The dst and src may be the same string pointer.
// This function is muth useful when called to lowercase the string in place.


void ngx_strlow_with_dst_match_src_length_t ()
{
	u_char *src = malloc(5);
	u_char *dst = malloc(5);
	
	// fill the src
	src[0] = 'A'; src[1] = 'B'; src[2] = 'C'; src[3] = 'D'; src[4] = '\0';
	
	ngx_strlow(dst, src, 5);
	
	// check dst (must be lowercased src)
	assert(dst[0] == 'a' && dst[1] == 'b' && dst[2] == 'c' && dst[3] == 'd' && dst[4] == '\0');
}

void ngx_strlow_with_dst_less_src_length_t ()
{
	u_char *src = malloc(5);
	u_char *dst = malloc(3);
	
	// fill the src
	src[0] = 'A'; src[1] = 'B'; src[2] = 'C'; src[3] = 'D'; src[4] = '\0';
	
	ngx_strlow(dst, src, 3);
	
	// check dst (must be of first tree lowercased bytes from src)
	assert(dst[0] == 'a' && dst[1] == 'b' && dst[2] == 'c');
}

void ngx_tolower_alphabet_t ()
{
	u_char *src = (u_char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	u_char *low = (u_char*)"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	
	size_t i;
	for(i = 0; i < sizeof("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"); ++i)
		assert(ngx_tolower(src[i]) == low[i]);
}

void ngx_toupper_alphabet_t ()
{
	u_char *src = (u_char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	u_char *up = (u_char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	size_t i;
	for(i = 0; i < sizeof("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"); ++i)
		assert(ngx_toupper(src[i]) == up[i]);
}




// u_char *
// ngx_pstrdup(ngx_pool_t *pool, ngx_str_t *src)
// Duplicates src useing pool to allocate memory for new dup.
// It doesn't set the trailing zero character,
// so it's only usefull for duplicating an ngx_str_t entities.

// Example:
// static void ngx_pstrdup_example ()
// {
// 	ngx_pool_t  *pool = ngx_create_pool(32, NULL);
// 	ngx_str_t dst, src = ngx_string("test");
// 	
// 	// copying src to dst
// 	dst.len = src.len;
// 	dst.data = ngx_pstrdup(pool, &src);
// 	if (dst.data == NULL)
// 		return; //NGX_ERROR;
// 	
// }


void ngx_pstrdup_with_pool_big_enough_t ()
{
	ngx_pool_t  *pool = ngx_create_pool(32, NULL);
	ngx_str_t src = ngx_string("test");
	
	u_char *dst = ngx_pstrdup(pool, &src);
	
	// check copy
	assert(dst[0] == 't' && dst[1] == 'e' && dst[2] == 's' && dst[3] == 't' && dst[4] == '\0');
}

void ngx_pstrdup_with_null_pool_t ()
{
	ngx_pool_t  *pool = ngx_create_pool(50, NULL);
	ngx_str_t src = ngx_string(STRING_OF_100_CHARS);
	
	__testing_no_memory = 555;
	u_char *dst = ngx_pstrdup(pool, &src);
	__testing_no_memory = 0;
	
	// dst must be NULL
	assert(dst == NULL);
}


