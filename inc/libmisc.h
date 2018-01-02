/**
 * \file libmisc.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Some usefule types and functions definitions.
 *
 * This file contains several definitions of types and functions
 * not related to a particular type and used throughout the whole project.
*/

#ifndef LIBMISC_H
#define LIBMISC_H



/**
 * \brief A redefinition for constant strings
*/
typedef const char *str;

/**
 * \brief A convenience macro for structure needing to be padded
 */
#define padding(size) unsigned char _padding[size]


/**
 * \brief Duplicates a string.
 *
 * \note This is a personal implementation of GNU's \a strdup() function, which
 *       is (alas) not standard.
 *
 * \param[in] orig The original string to copy
 *
 * \return a \a malloc'd copy of the string
 */
str strcopy(str orig);


#endif // LIBMISC_H
