dnl $Id$
dnl config.m4 for extension bitset

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(bitset, for bitset support,
dnl Make sure that the comment is aligned:
dnl [  --with-bitset             Include bitset support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(bitset, whether to enable bitset support,
dnl Make sure that the comment is aligned:
[  --enable-bitset           Enable bitset support])

if test "$PHP_BITSET" != "no"; then
  PHP_REQUIRE_CXX() dnl 通知make 使用g++
  PHP_ADD_LIBRARY(stdc++,1,EXTRAL_LAFLAGS) dnl c++标准(应该是98吧)

  dnl # --with-bitset -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/bitset.h"  # you most likely want to change this
  dnl if test -r $PHP_BITSET/$SEARCH_FOR; then # path given as parameter
  dnl   BITSET_DIR=$PHP_BITSET
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for bitset files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BITSET_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BITSET_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the bitset distribution])
  dnl fi

  dnl # --with-bitset -> add include path
  dnl PHP_ADD_INCLUDE($BITSET_DIR/include)
  PHP_ADD_INCLUDE(./src)
  dnl # --with-bitset -> check for lib and symbol presence
  dnl LIBNAME=bitset # you may want to change this
  dnl LIBSYMBOL=bitset # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BITSET_DIR/lib, BITSET_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BITSETLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong bitset lib version or lib not found])
  dnl ],[
  dnl   -L$BITSET_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BITSET_SHARED_LIBADD)

  PHP_NEW_EXTENSION(bitset, bitset.cpp src/BitSet.cpp, $ext_shared)
fi
