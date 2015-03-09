#ifndef __MACRO_H 
#define __MACRO_H

// debug info, print the runing file and line of the code
#define CURRENT_FILE_LINE \
std::cout << "# DEBUG_INFO:\n# \tcurrent file: " << __FILE__ << ",\n#\tcurrent func: " \
		  << __FUNCTION__<< ",\n#\tcurrent line: " << __LINE__ << std::endl

#define ZEROPAD	1        /* pad with zero */
#define SIGN	2        /* unsigned/signed long */
#define PLUS	4        /* show plus */
#define SPACE   8        /* space if plus */
#define LEFT    16       /* left justified */
#define SMALL   32       /* Must be 32 == 0x20 */
#define SPECIAL 64       /* 0x */

#define MAX_LENGTH	10240
#define BIG_LENGTH	1024
#define MID_LENGTH	512
#define SMA_LENGTH	128
#define MIN_LENGTH	64

#endif
