# Check for a module in pkg-config
#	1 variable base
# 	2 library name
# 	3 minimal version
# 	4 To do when found
# 	5 To do when not found
AC_DEFUN([ELM_CHECK_PKG_CONFIG], [
	HAS_$1=no
	AS_IF(test -z "$PKG_CONFIG",
		[
			AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
			PKG_CONFIG_MIN_VERSION=0.9.0
			AS_IF($PKG_CONFIG --atleast-pkgconfig-version $PKG_CONFIG_MIN_VERSION,
				,
				PKG_CONFIG=no)
		])
	AS_IF(test "$PKG_CONFIG" != "no",
		[
			AC_MSG_CHECKING(for $2-$3)
			AS_IF($PKG_CONFIG --exists "$2-$3",
				[
					AC_MSG_RESULT(yes)
					HAS_$1=yes
					AC_MSG_CHECKING($1_CFLAGS)
					$1_CFLAGS=`$PKG_CONFIG --cflags "$2-$3"`
					AC_MSG_RESULT($$1_CFLAGS)
					AC_MSG_CHECKING($1_LIBS)
					$1_LIBS=`$PKG_CONFIG --libs "$2-$3"`
					AC_MSG_RESULT($$1_LIBS)
				],
				[	AC_MSG_RESULT([no]) ])
		])
	AS_IF(test "$HAS_$1" = "yes", [$4], [$5])	
])


# Check for a existence of xxx-config
#	1 variable base
#	2 library name
#	3 minimal version
#	4 To do when found
#	5 To do when not found
AC_DEFUN([ELM_CHECK_CONFIG], [
	HAS_$1=no
	AC_MSG_CHECKING([for $2-config])
	[AC_PATH_PROG([$1_CONFIG], [$2-config], [no])]
	AS_IF(test "$1_CONFIG" = "no",
		[ AC_MSG_RESULT(no) ],
		[
			AC_MSG_RESULT([$1_CONFIG])
			AC_MSG_CHECKING(for $2-$3)
			curver=`$2-config --version`
			AS_IF(
				test "$curver" < "$3",
				[AC_MSG_RESULT([bad version : $curver at least required !])],
				[
					AC_MSG_RESULT(yes)
					HAS_$1=yes
					AC_MSG_CHECKING($1_CFLAGS)
					$1_CFLAGS=`$1-config --cflags`
					AC_MSG_RESULT($$1_CFLAGS)
					AC_MSG_CHECKING($1_LIBS)
					$1_LIBS=`$1-config --libs`
					AC_MSG_RESULT($$1_LIBS)
				])
		])
	AS_IF(test "$HAS_$1" = "yes", $4, $5)	
])
