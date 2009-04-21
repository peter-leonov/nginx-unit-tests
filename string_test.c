#include "testing.h"
#include "assert.h"
#include "ngx_core.h"


int fields ()
{
	ngx_str_t str;
	str.len = 0;
	str.data = NULL;
	
	return str.len == 0 && str.data == NULL;
}



// u_char *
// ngx_cpystrn(u_char *dst, u_char *src, size_t n)
// 
// If n == 0 leaves dst unchanged (desn't even set the trailing '\0') and returns dst value (the same pointer).
// If n > 0 copies u_chars from src to dst, stops copying when n u_chars are copied
// or if '\0' character is met in src; then adds trailing '\0' to the end of dst; afterwards
// returns a pointer to the last copied u_char (it will always be the trailing '\0' of dst).
// Usage: *res = ngx_cpystrn(dst, src, sizeof(src)-1); size_t copied = res - dst;


int ngx_cpystrn_with_normal_string ()
{
	u_char *dst = (u_char*)"XXXXXXXXX";
	u_char *src = (u_char*)"test";
	
	u_char *res = ngx_cpystrn(dst, src, sizeof("test")-1);
	
	assert(res - dst == sizeof("test"));
	
	return 1;
}

// int length_of_empty_with_non_null_data ()
// {
// 		ngx_str_t str = ngx_string("test");
// 		str.len = sizeof("test");
// 		str.data = "test";
// 		
// 		return str.len == 1;
// }


