#ifndef __CFUNC_H
#define __CFUNC_H

#include <assert.h>
#include <stdarg.h>
#include <memory.h>
#include <sstream>
#include <string>
#include <iostream>
#include "macro.h"

namespace cfunc {


/********************************************************************************
 *	func_name:		va_list2String
 *	return:			std::string
 *	parameters:		str: const char*; ap: va_list
 *	description:	a function may accept a varying number of additional 
 *					arguments without corresponding parameter declarations
 *					, and will change all these arguments to string.
 *					"%d, %f, %s" will be used to define the type of the
 *					argument.
 *******************************************************************************/
std::string va_list2String(const char *str, va_list ap) {
	assert(str);

	int tmp[MAX_LENGTH];
	memset(tmp, 0, sizeof(char)*MAX_LENGTH);
	tmp[0] = -2;

	std::stringstream strstr;

	int step = 0;
	int count = 1;		// The count of the "%" which also means the number of the argument in va_list

	const char *start = str;
	char buf[MAX_LENGTH];
	memset(buf, 0, sizeof(char)*MAX_LENGTH);

	const char *ss = NULL;
	for (ss = str; *ss != '\0'; ++ss) {
		if (*ss == '%') {

#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif
			++ss;
			tmp[count++] = step++;
			strncpy(buf,start,step-tmp[count-2]-3);
			buf[step-tmp[count-2]-3] = '\0';
			start = ss + 1;
			strstr << buf;

			int valueInt = 0;
			const char * valueStr = NULL;
			double valueDouble = 0.0;

			switch (*ss) {
				case 'd':
				case 'i':
				case 'u':
					valueInt = va_arg(ap, int);
					strstr << valueInt;
					break;

				case 's':
					valueStr = va_arg(ap, char *); 
					strstr << valueStr;
					break;

				case 'f':
					valueDouble = va_arg(ap, double);
					strstr << valueDouble;
					break;

				default :
					// For now, just support int, char* and double. For the other type will print warning
					std::cout << "WARNING: The type of argunent is not support" << std::endl;	

			}
		}
		step++;
	}
	if (*start != '\0') {
		strncpy(buf, start, step-tmp[count-1]-2);
		buf[step-tmp[count-1]-2] = '\0';
		strstr << buf;
	}

	va_end(ap);

//	std::cout << strstr.str() << " in va_list2String\n";
	return strstr.str();
}

};	// end of namespace cfunc
#endif

