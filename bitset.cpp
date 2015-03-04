/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_bitset.h"
#include "BitSet.hpp"

/* For PHP < 5.3.7 */
#ifndef PHP_FE_END
#define PHP_FE_END { NULL, NULL, NULL }
#endif
#ifndef ZEND_MOD_END
#define ZEND_MOD_END { NULL, NULL, NULL }
#endif

/* If you declare any globals in php_bitset.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(bitset)
*/

/* True global resources - no need for thread safety here */
static int le_bitset;

BitSet* bitSetObj = NULL;

/* {{{ bitset_functions[]
 *
 * Every user visible function must have an entry in bitset_functions[].
 */
const zend_function_entry bitset_functions[] = {
	PHP_FE(bitset_init,	NULL)
	PHP_FE(bit_set,	NULL)
	PHP_FE(bit_unset, NULL)
	PHP_FE(bit_isset, NULL)
	PHP_FE_END	/* Must be the last line in bitset_functions[] */
};
/* }}} */

/* {{{ bitset_module_entry
 */
zend_module_entry bitset_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"bitset",
	bitset_functions,
	PHP_MINIT(bitset),
	PHP_MSHUTDOWN(bitset),
	PHP_RINIT(bitset),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(bitset),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(bitset),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_BITSET_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BITSET
ZEND_GET_MODULE(bitset)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("bitset.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_bitset_globals, bitset_globals)
    STD_PHP_INI_ENTRY("bitset.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_bitset_globals, bitset_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_bitset_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_bitset_init_globals(zend_bitset_globals *bitset_globals)
{
	bitset_globals->global_value = 0;
	bitset_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(bitset)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(bitset)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(bitset)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(bitset)
{
    delete bitSetObj;
    bitSetObj = NULL;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(bitset)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "bitset support", "enabled");
	php_info_print_table_row(2, "bitset version", PHP_BITSET_VERSION);
	php_info_print_table_row(2, "64-bit Interger support", sizeof(unsigned long long)==8?"yes":"no");
	php_info_print_table_row(2, "author", "wuyong");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ bool bitset(int bit_size)
 * @decs: 设置bitset的位数大小,分配内存空间.
 * @author: wuyong
*/
PHP_FUNCTION(bitset_init)
{
    unsigned int bit_size;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &bit_size) == FAILURE) {
		return;
	}
    if (bit_size<0) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument bit_size is unsigned interger~!");
        return;
    }
    
    bitSetObj = new BitSet(bit_size);
    if(bitSetObj != NULL){
        RETURN_STRINGL((char *)bitSetObj->getBits(), bitSetObj->getBytes(), 0);
    }
    RETURN_BOOL(false);
}
/* }}} */

/* {{{ bool bit_set(int pos)
 * @decs: 将pos位设置位1
 * @author: wuyong
*/
PHP_FUNCTION(bit_set)
{
    unsigned int pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &pos) == FAILURE) {
		return;
	}
    if (pos<0) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument pos is unsigned interger~!");
        return;
    }
    
    bool res = bitSetObj->set(pos);

    RETURN_BOOL(res);
}
/* }}} */

/* {{{ bool bit_unset(int pos)
 * @decs: 将pos位设置位0
 * @author: wuyong
*/
PHP_FUNCTION(bit_unset)
{
    unsigned int pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &pos) == FAILURE) {
		return;
	}
    if (pos<0) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument pos is unsigned interger~!");
        return;
    }
    
    bool res = bitSetObj->unSet(pos);

    RETURN_BOOL(res);
}
/* }}} */

/* {{{ bool bit_isset(int pos)
 * @decs: pos位是否设置位1
 * @author: wuyong
*/
PHP_FUNCTION(bit_isset)
{
    unsigned int pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &pos) == FAILURE) {
		return;
	}
    if (pos<0) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Argument pos is unsigned interger~!");
        return;
    }
    
    bool res = bitSetObj->isSet(pos);

    RETURN_BOOL(res);

}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
