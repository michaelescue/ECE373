/**
 * @file april 22 notes.c
 * @author Michael
 * @brief  Notes for ECE373
 * @version 0.1
 * @date 2019-04-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

static struct bash commands{
    int umask;
/**
 * prints to terminal, will print with format specifier.
 * inverts the bits.(?)
 */


    ls -l /dev/"device"

    strace
/**
 * strace prints out all the system calls used during a program execution.
 * Likely have to build the program with debugging symbols.
 */

    sudo bash   
/**
 * sudo puts the bash shell into a different environment.  
 * sudo is to change user, but defaults to root.
 * this environment gives you a bunch of meaningfull macro(?) or
 * defines that contain paths for lookups.
 * 
 */

    su
/**   
 * su sets user to root (default).
 * Creates a shell within a shell that is root.
 * example:
 *      
 *      chmod 777
 *            bit positions
 *            111_111_111
 *            7:    Read/Write/Execute
 *            4:    Read
 *            6:    Read/Write
 *            1:    Execute
 * 
 *      "-rwx--x--x 1   user    0   date    time"
 *      "-" A dash.
 *        read bit      |
 *         write bit    |   Octal 1         [File]
 *          execute bit |
 *           read bit      |
 *            write bit    |   Octal 2      [Group]
 *             execute bit |
 *              read bit      |
 *               write bit    |   Octal 3   [World]
 *                execute bit |
 * 
 *        
*/

chmod

/**
 * changes permissions.
 * accepts octal input for setting permission flags.
 * the man page 
 * 
 */

