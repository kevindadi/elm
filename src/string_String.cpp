/*
 * $Id$
 * Copyright (c) 2003, Alfheim Corporation.
 *
 * string.cc -- string classes implementation.
 */

 #include <elm/string.h>
 
 namespace elm {
 
 /* Empty buffer */
 String::buffer_t String::empty_buf = { 1, 0 };
 
 /* String::copy() */
 void String::copy(const char *str, int _len) {
 	
 	// empty string?
 	if(!_len) {
 		buf = (char *)&empty_buf;
 		off =zero_off;
 		len = 0;
 		lock();
 	}
 	
 	// Create the buffer
 	else {
		buf = new char[sizeof(buffer_t) + _len]; 
		buffer_t *desc = (buffer_t *)buf;
		desc->use = 1;
		memcpy(desc->buf, str, _len);
		desc->buf[_len] = '\0';
		off = zero_off;
		len = _len; 
 	}
 }

/* String::concat(string 1, string 1 length, string 2, string 2 length)
 */
String String::concat(const char *s1, int l1, const char *s2, int l2) {
	buffer_t *sbuf = (buffer_t *)new char[sizeof(String::buffer_t) + l1 + l2];
	sbuf->use = 0;
	memcpy(sbuf->buf, s1, l1);
	memcpy(sbuf->buf + l1, s2, l2);
	sbuf->buf[l1 + l2] = '\0';
	return String((char *)sbuf, zero_off, l1 + l2);
}


/**
 * Transform the buffer such that a '\0' character is found at end of the current string.
 * If the buffer is only owned by the current string, the '\0' is simply added. Else a new buffer is created.
 */
void String::toc(void) {
	
	// Only one owner
	buffer_t *sbuf = (buffer_t *)buf;
	if(sbuf->use <= 1)
		sbuf->buf[len] = '\0';
	
	// Build a new buffer
	else {
		char *nbuf = new char[sizeof(buffer_t) + len]; 
		buffer_t *nsbuf = (buffer_t *)nbuf;
		nsbuf->use = 1;
		memcpy(nsbuf->buf, sbuf->buf, len);
		unlock();
		nsbuf->buf[len] = '\0';
		off = zero_off;
	}
}

}	// elm
